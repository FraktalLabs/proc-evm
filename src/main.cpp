#include <iostream>
#include <memory>

#include "call_context.h"

using bytes = std::basic_string<uint8_t>;

int main()
{
    // Create the contract
    bytes bytecode = {Opcode::PUSH1, 0x05, Opcode::PUSH1, 0x12, Opcode::ADD, Opcode::PUSH1, 0x02, Opcode::MUL, Opcode::PUSH1, 0x0a, Opcode::SUB, Opcode::STOP};
    std::shared_ptr<Contract> contract = std::make_shared<Contract>(bytecode);

    // Create a call context
    CallContext context(contract, 0);

    std::cout << "Contract Bytecode :: " << "size : " <<  context.getContract()->getBytecode().size() << " code : " << context.getContract()->getBytecodeString(true) << std::endl;

    // Run the contract
    context.run();

    // Quit the game
    return 0;
}
