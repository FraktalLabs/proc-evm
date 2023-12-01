#include <iostream>
#include <memory>

#include "call_context.h"
#include "state/state.h"

using bytes = std::basic_string<uint8_t>;

int main()
{
    std::shared_ptr<State> state = std::make_shared<State>("/home/brandon/workspace/blockchain/FraktalLabs/proc-evm/snapshot.txt");

    std::string callAddress = "4200000000000000000000000000000000000000";

    // Create the contract
    bytes bytecode = {Opcode::PUSH1, 0x04, Opcode::JUMP, Opcode::STOP, Opcode::JUMPDEST, Opcode::PUSH1, 0x05, Opcode::PUSH1, 0x12, Opcode::ADD, Opcode::PUSH1, 0x02, Opcode::MUL, Opcode::PUSH1, 0x0a, Opcode::SUB,
                      Opcode::PUSH1, 0x00, Opcode::MSTORE, Opcode::PUSH1, 0x00, Opcode::MLOAD, Opcode::PUSH2, 0x12, 0x34, Opcode::DUP1, Opcode::DUP3, Opcode::SSTORE, Opcode::DUP2, Opcode::SLOAD, Opcode::STOP};
    std::shared_ptr<Contract> contract = std::make_shared<Contract>(bytecode);

    // Create a call context
    CallContext context(contract, 0, state, callAddress);

    std::cout << "Contract Bytecode :: " << "size : " <<  context.getContract()->getBytecode().size() << " code : " << context.getContract()->getBytecodeString(true) << std::endl;

    // Run the contract
    context.run();

    // Snapshot the state
    std::cout << "------ Snapshotting State ------" << std::endl;
    context.getState()->snapshot("/home/brandon/workspace/blockchain/FraktalLabs/proc-evm/snapshot.txt");

    // Quit the game
    return 0;
}
