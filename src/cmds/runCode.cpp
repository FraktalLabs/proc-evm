#include "cmds.h"

#include <iostream>

#include "../external/state/state.h"
#include "../external/block_context.h"
#include "../external/tx_context.h"
#include "../vm/call_context.h"
#include "../contract.h"
#include "../utils/utils.h"

struct RunCodeData {
  std::string snapshotFile;
  std::shared_ptr<State> state;
  std::shared_ptr<BlockContext> blockContext;
  std::shared_ptr<TxContext> txContext;
  std::shared_ptr<Contract> contract;
  bytes inputData;
  intx::uint256 value;
};

std::unique_ptr<RunCodeData> parseRunCmdlineArgs(int argc, char *argv[]) {
  // Cmdline Args
  std::string snapshotFile;
  std::string blockContextFile;
  std::string txContextFile;
  std::string codeFile;
  std::string contractCode;
  std::string inputData;
  std::string value;
  // TODO: fee stuff
  // TODO: signature
  // TODO: from & to??

  const std::string helpText = "Usage: " + std::string(argv[0]) + " run [options]\n"
                               "  Run bytecode as a transaction (acts like a script w/ no contract deployment)\n\n"
                               "Options:\n"
                               "  --snapshotFile <file>      Snapshot file (required)\n"
                               "  --blockContextFile <file>  Block context file (required)\n"
                               "  --txContextFile <file>     Transaction context file (required)\n"
                               "  --codeFile <file>          Contract code file (must use either --codeFile or --contractCode)\n"
                               "  --contractCode <code>      Contract code (must use either --codeFile or --contractCode)\n"
                               "  --inputData <data>         Input data (default: \"\")\n"
                               "  --value <value>            Value (default: 0)\n";

  if(argc < 3) {
    std::cerr << helpText;
    exit(1);
  }

  // Parse cmdline args
  for(int i = 2; i < argc; i++) {
    std::string arg = argv[i];
    if(arg == "--snapshotFile") {
      if(i + 1 >= argc) {
        std::cerr << "Missing argument for --snapshotFile\n";
        exit(1);
      }
      snapshotFile = argv[++i];
    } else if(arg == "--blockContextFile") {
      if(i + 1 >= argc) {
        std::cerr << "Missing argument for --blockContextFile\n";
        exit(1);
      }
      blockContextFile = argv[++i];
    } else if(arg == "--txContextFile") {
      if(i + 1 >= argc) {
        std::cerr << "Missing argument for --txContextFile\n";
        exit(1);
      }
      txContextFile = argv[++i];
    } else if(arg == "--codeFile") {
      if(i + 1 >= argc) {
        std::cerr << "Missing argument for --codeFile\n";
        exit(1);
      }
      codeFile = argv[++i];
    } else if(arg == "--contractCode") {
      if(i + 1 >= argc) {
        std::cerr << "Missing argument for --contractCode\n";
        exit(1);
      }
      contractCode = argv[++i];
    } else if(arg == "--inputData") {
      if(i + 1 >= argc) {
        std::cerr << "Missing argument for --inputData\n";
        exit(1);
      }
      inputData = argv[++i];
    } else if(arg == "--value") {
      if(i + 1 >= argc) {
        std::cerr << "Missing argument for --value\n";
        exit(1);
      }
      value = argv[++i];
    } else if(arg == "--help") {
      std::cerr << helpText;
      exit(0);
    } else {
      std::cerr << "Unknown argument: " << arg << "\n";
      std::cerr << helpText;
      exit(1);
    }
  }

  // Check required args
  if(snapshotFile.empty()) {
    std::cerr << "Missing required argument --snapshotFile\n";
    std::cerr << helpText;
    exit(1);
  }

  if(blockContextFile.empty()) {
    std::cerr << "Missing required argument --blockContextFile\n";
    std::cerr << helpText;
    exit(1);
  }

  if(txContextFile.empty()) {
    std::cerr << "Missing required argument --txContextFile\n";
    std::cerr << helpText;
    exit(1);
  }

  if(codeFile.empty() && contractCode.empty()) {
    std::cerr << "Missing required argument --codeFile or --contractCode\n";
    std::cerr << helpText;
    exit(1);
  }

  // Parse optional args
  if(inputData.empty()) {
    inputData = "";
  }

  if(value.empty()) {
    value = "0";
  }

  auto state = std::make_shared<State>(snapshotFile);
  auto blockContext = std::make_shared<BlockContext>(blockContextFile);
  auto txContext = std::make_shared<TxContext>(txContextFile);

  bytes contractBytecode;
  if(!codeFile.empty()) {
    // Check file ending ( .yul or .sol )
    std::string fileEnding = codeFile.substr(codeFile.find_last_of(".") + 1);
    if(fileEnding == "yul" || fileEnding == "sol") {
      contractBytecode = compileContract(codeFile);
    } else {
      // Read bytecode from file
      contractBytecode = parseBytecodeFile(codeFile);
    }
  } else {
    contractBytecode = parseBytecode(contractCode);
  }
  auto contract = std::make_shared<Contract>(contractBytecode);

  bytes inputDataBytes = parseBytecode(inputData);

  intx::uint256 valueInt = intx::from_string<intx::uint256>(value);

  return std::make_unique<RunCodeData>(RunCodeData{snapshotFile, state, blockContext, txContext, contract, inputDataBytes, valueInt});
}

void runCode(const RunCodeData& data) {
  address caller = data.txContext->getOrigin(); // TODO: Is this correct?
  std::shared_ptr<CallContext> callContext =
      std::make_shared<CallContext>(data.contract, data.value, data.inputData, caller,
                                    data.state, data.blockContext, data.txContext);

  auto result = callContext->run();
}

int runCodeCmdline(int argc, char *argv[]) {
  auto data = parseRunCmdlineArgs(argc, argv);

  runCode(*data);

  // TODO: Allow outputing to a different file?
  data->state->snapshot(data->snapshotFile);

  // TODO: logs? callinfo / routines?
  // TODO: dump mutex data from state?
  return 0;
}
