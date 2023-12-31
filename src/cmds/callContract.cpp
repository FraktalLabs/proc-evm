#include "cmds.h"

#include <iostream>

#include "../vm/call_context.h"
#include "../vm/contract.h"

#include <evm-cpp-utils/types.h>
#include <evm-cpp-utils/utils.h>

struct CallCodeData {
  std::string snapshotFile;
  std::shared_ptr<State> state;
  std::shared_ptr<BlockContext> blockContext;
  std::shared_ptr<TxContext> txContext;
  std::shared_ptr<Contract> contract;
  bytes inputData;
  intx::uint256 value;
};

std::unique_ptr<CallCodeData> parseCallCmdlineArgs(int argc, char *argv[]) {
  // Cmdline Args
  std::string snapshotFile;
  std::string blockContextFile;
  std::string txContextFile;
  std::string inputData;
  std::string value;
  std::string contractAddressStr;
  // TODO: fee stuff
  // TODO: signature
  // TODO: from & to??

  const std::string helpText = "Usage: " + std::string(argv[0]) + " call [options]\n"
                               "  Call contract as a transaction (acts like a normal contract call)\n\n"
                               "Options:\n"
                               "  --contractAddress <addr>   Contract address (required)\n"
                               "  --snapshotFile <file>      Snapshot file (required)\n"
                               "  --blockContextFile <file>  Block context file (required)\n"
                               "  --txContextFile <file>     Transaction context file (required)\n"
                               "  --inputData <data>         Input data (default: \"\")\n"
                               "  --value <value>            Value (default: 0)\n";

  if(argc < 3) {
    std::cerr << helpText;
    exit(1);
  }

  // Parse cmdline args
  for(int i = 2; i < argc; i++) {
    std::string arg = argv[i];
    if(arg == "--contractAddress") {
      if(i + 1 >= argc) {
        std::cerr << "Missing argument for --contractAddress\n";
        exit(1);
      }
      contractAddressStr = argv[++i];
    } else if(arg == "--snapshotFile") {
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
  if(contractAddressStr.empty()) {
    std::cerr << "Missing required argument --contractAddress\n";
    std::cerr << helpText;
    exit(1);
  }

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

  // Parse optional args
  if(inputData.empty()) {
    inputData = "";
  }

  if(value.empty()) {
    value = "0";
  }

  bytes contractAddressBytes = parseBytecode(contractAddressStr);
  address contractAddress;
  for(int i = 0; i < 20; i++) {
    contractAddress[i] = contractAddressBytes[i];
  }

  auto state = std::make_shared<State>(snapshotFile);
  auto blockContext = std::make_shared<BlockContext>(blockContextFile);
  auto txContext = std::make_shared<TxContext>(txContextFile);

  std::shared_ptr<Account> account = state->get(contractAddressStr);
  if(account == nullptr) {
    std::cerr << "Contract does not exist: " << contractAddressStr << "\n";
    exit(1);
  }
  bytes contractCode = account->getCode();
  auto contract = std::make_shared<Contract>(contractCode, contractAddressStr);

  bytes inputDataBytes = parseBytecode(inputData);

  intx::uint256 valueInt = intx::from_string<intx::uint256>(value);

  return std::make_unique<CallCodeData>(CallCodeData{snapshotFile, state, blockContext, txContext, contract, inputDataBytes, valueInt});
}

void callContract(const CallCodeData& data) {
  address caller = data.txContext->getOrigin(); // TODO: Is this correct?
  std::shared_ptr<CallContext> callContext =
      std::make_shared<CallContext>(data.contract, data.value, data.inputData, caller,
                                    data.state, data.blockContext, data.txContext);

  auto result = callContext->run();
}

int callContractCmdline(int argc, char *argv[]) {
  auto data = parseCallCmdlineArgs(argc, argv);

  callContract(*data);

  // TODO: Allow outputing to a different file?
  data->state->snapshot(data->snapshotFile);

  // TODO: logs? callinfo / routines?
  // TODO: dump mutex data from state?
  return 0;
}
