#include <iostream>

#include "call_context.h"
#include "operations.h"

void CallContext::run() {
  while(pc < contract->getBytecodeSize()) {
    // Print the current state
    std::cout << "\nState at pc: " << pc << std::endl;
    std::cout << "  opcode: " << contract->getBytecodeStringAt(pc) << " - " << opcodeToString(contract->getOpcodeAt(pc)) << std::endl;
    std::cout << "  stack:\n" << stack->toString() << std::endl;

    // Get the opcode
    Opcode opcode = contract->getOpcodeAt(pc);
    Operation* operation = getOperation(opcode);

    // Execute the operation
    ExecStatus status = operation->execute(*this);

    std::cout << "  new stack:\n" << stack->toString() << std::endl;

    if(status == ExecStatus::STOPEXEC) {
      std::cout << "Received STOP" << std::endl;
      break;
    }

    pc++;
  }
}
