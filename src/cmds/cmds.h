#pragma once

struct RunCodeData;
struct DeployContractData;
struct DeployAtContractData;
struct CallCodeData;

void runCode(const RunCodeData& data);
void deployContract(const DeployContractData& data);
void deployAtContract(const DeployAtContractData& data);
void callContract(const CallCodeData& data);

int runCodeCmdline(int argc, char *argv[]);
int deployContractCmdline(int argc, char *argv[]);
int deployAtContractCmdline(int argc, char *argv[]);
int callContractCmdline(int argc, char *argv[]);
