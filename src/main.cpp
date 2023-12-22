#include <iostream>
#include <memory>
#include <string>
#include <fstream>

#include "call_context.h"
#include "state/state.h"
#include "utils.h"
#include "cmds/cmds.h"
#include "rlp.h"

int main(int argc, char *argv[]) {
  const std::string helpMessage = "Usage: " + std::string(argv[0]) + " <subcommand> [options]\n"
                                  "Subcommands:\n"
                                  "  run       : Run EVM code\n"
                                  "  deploy    : Deploy a contract\n"
                                  "  deployAt  : Deploy a contract at location\n"
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
  } else if (subcommand == "deployAt") {
    return deployAtContract(argc, argv);
  } else if (subcommand == "call") {
    return callContract(argc, argv);
  } else {
    std::cout << "Unknown subcommand: " << subcommand << std::endl << std::endl;
    std::cout << helpMessage << std::endl;
    return 1;
  }
}
