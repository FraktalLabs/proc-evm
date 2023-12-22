#include <string>
#include <iostream>

#include "cmds/cmds.h"

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
    return runCodeCmdline(argc, argv);
  } else if (subcommand == "deploy") {
    return deployContractCmdline(argc, argv);
  } else if (subcommand == "deployAt") {
    return deployAtContractCmdline(argc, argv);
  } else if (subcommand == "call") {
    return callContractCmdline(argc, argv);
  } else {
    std::cout << "Unknown subcommand: " << subcommand << std::endl << std::endl;
    std::cout << helpMessage << std::endl;
    return 1;
  }
}
