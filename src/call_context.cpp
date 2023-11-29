#include <iostream>

#include "call_context.h"
#include "operations.h"

void CallContext::run() {
  while(pc < contract->getBytecodeSize()) {
    std::cout << "pc: " << pc << " opcode: " << contract->getBytecodeStringAt(pc) << " - " << opcodeToString(contract->getOpcodeAt(pc)) << std::endl;

    // Get the opcode
    Opcode opcode = contract->getOpcodeAt(pc);
    Operation* operation = getOperation(opcode);

    // Execute the operation
    operation->execute(*this);

    pc++;
  }
}
