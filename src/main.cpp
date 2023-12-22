#include <iostream>
#include <memory>
#include <string>
#include <fstream>

#include "call_context.h"
#include "state/state.h"
#include "utils.h"
#include "cmds/cmds.h"
#include "rlp.h"

void create(const std::string& caller, bytes contractCode, std::shared_ptr<State> state) {
  std::cout << "Creating contract" << std::endl;

  // Create contract address
  bytes callerBytes;
  for (int i = 0; i < caller.size(); i++) {
    callerBytes.push_back(caller[i]);
  }
  uint64_t nonce = state->getAccount(caller)->getNonce();
  bytes encodedData = encode_tuple<bytes, uint64_t>(callerBytes, nonce);
  uint8_t* encodedDataPtr = encodedData.data();
  uint8_t* encodedHash = ethash_keccak256(encodedDataPtr, encodedData.size()).bytes;
  // contract address is last 20 bytes of hash
  bytes contractAddressBytes(encodedHash + 12, encodedHash + 32);
  address contractAddress;
  std::string contractAddressStr;
  for (int i = 0; i < 20; i++) {
    contractAddress[i] = contractAddressBytes[i];
    contractAddressStr += byteToHex(contractAddressBytes[i]);
  }

  // TODO
  // contractHash = statedb.getcodehash(contractAddress)
  // Check if contractHash == empty

  std::cout << "Inserting contract into state :: " << contractAddressStr << std::endl;

  // Create account & add to state
  Account contractAccount;
  contractAccount.initAccount(contractCode);
  state->insert(contractAddress, contractAccount);
  // TODO: transfer value from caller to contractAddress
  // TODO : missed things

  std::cout << "Deploying Contract Address :: " << contractAddressStr << "  & code : " << contractCode.size() << std::endl;

  std::shared_ptr<Contract> contract = std::make_shared<Contract>(contractCode);
  std::shared_ptr<CallContext> context = std::make_shared<CallContext>(contract, 0, state, contractAddressStr);
  bytes ret = context->run();

  // if no err : set code to ret
  state->getAccount(contractAddress)->setCode(ret);

  // delete encodedHash; // TODO
}

int deployAtContract(int argc, char *argv[]) {
  std::cout << "Deploying contract at address" << std::endl;

    std::string snapshotFile;
    std::shared_ptr<State> state;
    std::string deployAddress;
    std::string code;
    bytes bytecode;
    std::shared_ptr<Contract> contract;

    // Parse the command line arguments
    // Options : --code <bytecode> --state <state> --address <address>
    //           --file <code file> --state <state> --address <address>

    if (argc < 3) {
      snapshotFile = "/home/brandon/workspace/blockchain/FraktalLabs/proc-evm/snapshot.txt";
      state = std::make_shared<State>(snapshotFile);
      deployAddress = "4200000000000000000000000000000000000000";
      bytecode = { Opcode::PUSH1, 0x04, Opcode::JUMP, Opcode::STOP, Opcode::JUMPDEST,
                   Opcode::PUSH1, 0x05, Opcode::PUSH1, 0x12, Opcode::ADD, Opcode::PUSH1, 0x02, Opcode::MUL, Opcode::PUSH1, 0x0a, Opcode::SUB,
                   Opcode::PUSH1, 0x00, Opcode::MSTORE, Opcode::PUSH1, 0x00, Opcode::MLOAD, Opcode::PUSH2, 0x12, 0x34, Opcode::DUP1, Opcode::DUP3,
                   Opcode::SSTORE, Opcode::DUP2, Opcode::SLOAD, Opcode::STOP };
      for (int i = 0; i < bytecode.size(); i++) {
        code += byteToHex(bytecode[i]);
      }
    } else {
      bool codeProvided = false;
      bool stateProvided = false;
      bool addressProvided = false;
      for (int i = 2; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--code") {
          // Get the bytecode from the command line
          i++;
          code = argv[i];
          for (int j = 0; j < code.size(); j += 2)
          {
            std::string byteString = code.substr(j, 2);
            uint8_t byte = std::stoi(byteString, nullptr, 16);
            bytecode.push_back(byte);
          }
          codeProvided = true;
        } else if (arg == "--file") {
          // Get the bytecode from a file
          i++;
          std::string filename = argv[i];
          std::ifstream file(filename);
          std::getline(file, code);
          for (int j = 0; j < code.size(); j += 2)
          {
            std::string byteString = code.substr(j, 2);
            uint8_t byte = std::stoi(byteString, nullptr, 16);
            bytecode.push_back(byte);
          }
          codeProvided = true;
        } else if (arg == "--state") {
          // Get the state from a file
          i++;
          snapshotFile = argv[i];
          state = std::make_shared<State>(snapshotFile);
          stateProvided = true;
        } else if (arg == "--address") {
          // Get the address from the command line
          i++;
          deployAddress = argv[i];
          addressProvided = true;
        } else if (arg == "-h") {
          std::cout << "Usage: " << argv[0] << " [options]" << std::endl;
          std::cout << "Options:" << std::endl;
          std::cout << "  --code <bytecode>    : The contract bytecode to run" << std::endl;
          std::cout << "  --file <code file>   : The contract bytecode to run from a file" << std::endl;
          std::cout << "  --state <state file> : The state to run the contract in" << std::endl;
          std::cout << "  --address <address>  : The address to call the contract with" << std::endl;
          std::cout << "  -h                   : Print this help message" << std::endl;
          return 0;
        } else {
          std::cout << "Unknown option: " << arg << std::endl;
          return 1;
        }
      }
      if (!codeProvided) {
        bytecode = { Opcode::PUSH1, 0x04, Opcode::JUMP, Opcode::STOP, Opcode::JUMPDEST,
                     Opcode::PUSH1, 0x05, Opcode::PUSH1, 0x12, Opcode::ADD, Opcode::PUSH1, 0x02, Opcode::MUL, Opcode::PUSH1, 0x0a, Opcode::SUB,
                     Opcode::PUSH1, 0x00, Opcode::MSTORE, Opcode::PUSH1, 0x00, Opcode::MLOAD, Opcode::PUSH2, 0x12, 0x34, Opcode::DUP1, Opcode::DUP3,
                     Opcode::SSTORE, Opcode::DUP2, Opcode::SLOAD, Opcode::STOP };
        for (int i = 0; i < bytecode.size(); i++) {
          code += byteToHex(bytecode[i]);
        }
      }
      if (!stateProvided) {
        state = std::make_shared<State>();
      }
      if (!addressProvided) {
        deployAddress = "4200000000000000000000000000000000000000";
      }
    } 

    // Create the contract
    contract = std::make_shared<Contract>(bytecode, deployAddress);
    // Create the Account
    Account account = Account();
    account.initAccount(code);

    // Insert the contract into the state
    state->insert(deployAddress, account);

    //TODO: Input variables / values?

    // Snapshot the state
    state->snapshot(snapshotFile);

    return 0;
}

int callContract(int argc, char *argv[]) {
  std::string snapshotFile;
  std::shared_ptr<State> state;
  std::string address;
  bytes input;
  bool inputProvided = false;
  //std::string data;
  //std::string value;
  //std::string gas;
  //std::string gasPrice;
  //std::string sender;

  if (argc < 3) {
    snapshotFile = "/home/brandon/workspace/blockchain/FraktalLabs/proc-evm/snapshot.txt";
    state = std::make_shared<State>(snapshotFile);
    address = "4200000000000000000000000000000000000000";
  } else {
    bool stateProvided = false;
    bool addressProvided = false;

    for (int i = 2; i < argc; i++) {
      std::string arg = argv[i];
      if (arg == "--state") {
        // Get the state from a file
        i++;
        snapshotFile = argv[i];
        state = std::make_shared<State>(snapshotFile);
        stateProvided = true;
      } else if (arg == "--address") {
        // Get the address from the command line
        i++;
        address = argv[i];
        addressProvided = true;
      } else if (arg == "--input") {
        // Get the input from the command line
        i++;
        std::string inputString = argv[i];
        for (int j = 0; j < inputString.size(); j += 2)
        {
          std::string byteString = inputString.substr(j, 2);
          uint8_t byte = std::stoi(byteString, nullptr, 16);
          input.push_back(byte);
        }
        inputProvided = true;
      } else if (arg == "-h") {
        std::cout << "Usage: " << argv[0] << " [options]" << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "  --state <state file> : The state to run the contract in" << std::endl;
        std::cout << "  --address <address>  : The address to call the contract with" << std::endl;
        std::cout << "  -h                   : Print this help message" << std::endl;
        return 0;
      } else {
        std::cout << "Unknown option: " << arg << std::endl;
        return 1;
      }
    }

    if (!stateProvided) {
      snapshotFile = "/home/brandon/workspace/blockchain/FraktalLabs/proc-evm/snapshot.txt";
      state = std::make_shared<State>(snapshotFile);
    }
    if (!addressProvided) {
      address = "4200000000000000000000000000000000000000";
    }
  }

  // Get the contract from the state
  Account* account = state->getAccount(address);
  bytes bytecode = account->getCode();
  std::shared_ptr<Contract> contract = std::make_shared<Contract>(bytecode, address);

  // Create call context
  std::shared_ptr<CallContext> context = std::make_shared<CallContext>(contract, 0, state);
  if (inputProvided) {
    context->setInput(input);
  }

  // Run the contract
  context->run();

  // Snapshot the state
  state->snapshot(snapshotFile);

  return 0;
}

int main(int argc, char *argv[]) {
  const std::string helpMessage = "Usage: " + std::string(argv[0]) + " <subcommand> [options]\n"
                                  "Subcommands:\n"
                                  "  run       : Run EVM code\n"
                                  "  deploy    : Deploy a contract\n"
                                  "  deploy-at : Deploy a contract at location\n"
                                  "  call      : Call a contract\n";

  if (argc < 2)
  {
    std::cout << helpMessage << std::endl;
    return 0;
  }

  std::string subcommand = argv[1];
  if (subcommand == "run") {
    return runCode(argc, argv);
  } else if (subcommand == "deploy") {
    return deployContract(argc, argv);
  } else if (subcommand == "deploy-at") {
    return deployAtContract(argc, argv);
  } else if (subcommand == "call") {
    return callContract(argc, argv);
  } else {
    std::cout << "Unknown subcommand: " << subcommand << std::endl << std::endl;
    std::cout << helpMessage << std::endl;
    return 1;
  }
}
