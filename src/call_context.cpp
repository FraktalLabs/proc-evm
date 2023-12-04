#include <iostream>

#include "call_context.h"
#include "operations.h"

bytes CallContext::run() {
  while(pc < contract->getBytecodeSize()) {
    // Print the current state
    std::cout << "\nState at contract : " << contract->getAddressString() << "  and pc : " << pc << std::endl;
    std::cout << "  opcode: " << contract->getBytecodeStringAt(pc) << " - " << opcodeToString(contract->getOpcodeAt(pc)) << std::endl;
    std::cout << "  stack: " << stack->toString() << std::endl;
    std::cout << "  memory: " << memory->toString() << std::endl;

    // Get the opcode
    Opcode opcode = contract->getOpcodeAt(pc);
    Operation* operation = getOperation(opcode);

    // Execute the operation
    ExecStatus status = operation->execute(*this);

    std::cout << "  ---- Executed ----" << std::endl;
    std::cout << "  new stack: " << stack->toString() << std::endl;
    std::cout << "  new memory: " << memory->toString() << std::endl;

    //TODO : Handle the status & revert?
    if(status == ExecStatus::STOPEXEC || status == ExecStatus::RETURNEXEC) {
      std::cout << "Received STOP" << std::endl;
      break;
    }

    pc++;
  }

  std::cout << "  returning w/ " << getRetString() << std::endl;

  return ret;
}
