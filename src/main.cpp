#include <iostream>
#include <memory>
#include <string>
#include <fstream>

#include "call_context.h"
#include "state/state.h"

using bytes = std::basic_string<uint8_t>;

std::string byteToHex(uint8_t byte) {
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(byte);
  return ss.str();
}


int runCode(int argc, char *argv[]) {

    std::string snapshotFile;
    std::shared_ptr<State> state;
    std::string callAddress;
    bytes bytecode;
    std::shared_ptr<Contract> contract;
    std::shared_ptr<CallContext> context;

    // Parse the command line arguments
    // Options : --code <bytecode> --state <state>
    //           --file <code file> --state <state>
    //           --address <address> --state <state>

    if (argc < 3)
    {
      // Use default setup for now
      snapshotFile = "/home/brandon/workspace/blockchain/FraktalLabs/proc-evm/snapshot.txt";
      state = std::make_shared<State>(snapshotFile);
      callAddress = "4200000000000000000000000000000000000000";
      bytecode = { Opcode::PUSH1, 0x04, Opcode::JUMP, Opcode::STOP, Opcode::JUMPDEST,
                   Opcode::PUSH1, 0x05, Opcode::PUSH1, 0x12, Opcode::ADD, Opcode::PUSH1, 0x02, Opcode::MUL, Opcode::PUSH1, 0x0a, Opcode::SUB,
                   Opcode::PUSH1, 0x00, Opcode::MSTORE, Opcode::PUSH1, 0x00, Opcode::MLOAD, Opcode::PUSH2, 0x12, 0x34, Opcode::DUP1, Opcode::DUP3,
                   Opcode::SSTORE, Opcode::DUP2, Opcode::SLOAD, Opcode::STOP };
      contract = std::make_shared<Contract>(bytecode);
      context = std::make_shared<CallContext>(contract, 0, state, callAddress);
    } else {
      // TODO: Remove these flags and setup defaults where possible
      bool stateProvided = false;
      bool addressProvided = false;
      bool codeProvided = false;

      // Parse the command line arguments
      for (int i = 1; i < argc; i++)
      {
        std::string arg = argv[i];
        if (arg == "--code")
        {
          // Get the bytecode
          i++;
          std::string code = argv[i];
          for (int j = 0; j < code.size(); j += 2)
          {
            std::string byteString = code.substr(j, 2);
            uint8_t byte = std::stoi(byteString, nullptr, 16);
            bytecode.push_back(byte);
          }
          contract = std::make_shared<Contract>(bytecode);
          codeProvided = true;
        } else if (arg == "--file") {
          // Get the bytecode from a file
          i++;
          std::string filename = argv[i];
          std::ifstream file(filename);
          std::string code;
          std::getline(file, code);
          // TODO: multi-line?
          for (int j = 0; j < code.size(); j += 2)
          {
            std::string byteString = code.substr(j, 2);
            uint8_t byte = std::stoi(byteString, nullptr, 16);
            bytecode.push_back(byte);
          }
          contract = std::make_shared<Contract>(bytecode);
          codeProvided = true;
        } else if (arg == "--state") {
          // Get the state
          i++;
          snapshotFile = argv[i];
          state = std::make_shared<State>(snapshotFile);
          stateProvided = true;
        } else if (arg == "--address") {
          // Get the call address
          i++;
          callAddress = argv[i];
          addressProvided = true;
        } else if (arg == "-h") {
          // Print help
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
      if (!stateProvided)
      {
        snapshotFile = "/home/brandon/workspace/blockchain/FraktalLabs/proc-evm/snapshot.txt";
        state = std::make_shared<State>(snapshotFile);
        //TODO: default to empty state
      }
      if (!addressProvided)
      {
        callAddress = "4200000000000000000000000000000000000000";
      }
      if (!codeProvided)
      {
        bytecode = { Opcode::PUSH1, 0x04, Opcode::JUMP, Opcode::STOP, Opcode::JUMPDEST,
                     Opcode::PUSH1, 0x05, Opcode::PUSH1, 0x12, Opcode::ADD, Opcode::PUSH1, 0x02, Opcode::MUL, Opcode::PUSH1, 0x0a, Opcode::SUB,
                     Opcode::PUSH1, 0x00, Opcode::MSTORE, Opcode::PUSH1, 0x00, Opcode::MLOAD, Opcode::PUSH2, 0x12, 0x34, Opcode::DUP1, Opcode::DUP3,
                     Opcode::SSTORE, Opcode::DUP2, Opcode::SLOAD, Opcode::STOP };
        contract = std::make_shared<Contract>(bytecode);
      }
      context = std::make_shared<CallContext>(contract, 0, state, callAddress);
    }
    
    std::cout << "Contract Bytecode :: " << "size : " <<  context->getContract()->getBytecode().size()
                                         << " code : " << context->getContract()->getBytecodeString(true) << std::endl;

    // Run the contract
    context->run();

    // Snapshot the state
    std::cout << "------ Snapshotting State ------" << std::endl;
    context->getState()->snapshot(snapshotFile);

    // Quit the game
    return 0;
}

int deployContract(int argc, char *argv[]) {
  std::cout << "Deploying contract" << std::endl;

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

    // Snapshot the state
    state->snapshot(snapshotFile);

    return 0;
}

int callContract(int argc, char *argv[]) {
  std::string snapshotFile;
  std::shared_ptr<State> state;
  std::string address;
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

  // Run the contract
  context->run();

  // Snapshot the state
  state->snapshot(snapshotFile);

  return 0;
}

int main(int argc, char *argv[]) {

  // Parse subcommand : run, deploy, call
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " <subcommand> [options]" << std::endl;
    std::cout << "Subcommands:" << std::endl;
    std::cout << "  run    : Run EVM code" << std::endl;
    std::cout << "  deploy : Deploy a contract" << std::endl;
    std::cout << "  call   : Call a contract" << std::endl;
    return 0;
  }

  std::string subcommand = argv[1];
  if (subcommand == "run") {
    return runCode(argc, argv);
  } else if (subcommand == "deploy") {
    return deployContract(argc, argv);
  } else if (subcommand == "call") {
    return callContract(argc, argv);
  } else {
    std::cout << "Unknown subcommand: " << subcommand << std::endl;
    return 1;
  }
}
