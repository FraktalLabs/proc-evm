#include <iostream>
#include <memory>

#include "call_context.h"

using bytes = std::basic_string<uint8_t>;

int main()
{
    // Create the contract
    bytes bytecode = {0x00, 0x01, 0x02, 0x03};
    std::shared_ptr<Contract> contract = std::make_shared<Contract>(bytecode);

    // Create a call context
    CallContext context(contract, 0);

    std::cout << "Contract Bytecode :: " << "size : " <<  context.getContract()->getBytecode().size() << " code : " << context.getContract()->getBytecodeString(true) << std::endl;

    // Run the contract
    context.run();

    // Quit the game
    return 0;
}
