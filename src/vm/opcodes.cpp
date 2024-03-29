#include "opcodes.h"

#include <map>

//TODO: To header?
std::map<Opcode, std::string> opcodeStrings = {
    {Opcode::STOP, "STOP"},
    {Opcode::ADD, "ADD"},
    {Opcode::MUL, "MUL"},
    {Opcode::SUB, "SUB"},
    {Opcode::DIV, "DIV"},
    {Opcode::SDIV, "SDIV"},
    {Opcode::MOD, "MOD"},
    {Opcode::SMOD, "SMOD"},
    {Opcode::ADDMOD, "ADDMOD"},
    {Opcode::MULMOD, "MULMOD"},
    {Opcode::EXP, "EXP"},
    {Opcode::SIGNEXTEND, "SIGNEXTEND"},

    {Opcode::LT, "LT"},
    {Opcode::GT, "GT"},
    {Opcode::SLT, "SLT"},
    {Opcode::SGT, "SGT"},
    {Opcode::EQ, "EQ"},
    {Opcode::ISZERO, "ISZERO"},
    {Opcode::AND, "AND"},
    {Opcode::OR, "OR"},
    {Opcode::XOR, "XOR"},
    {Opcode::NOT, "NOT"},
    {Opcode::BYTE, "BYTE"},
    {Opcode::SHL, "SHL"},
    {Opcode::SHR, "SHR"},
    {Opcode::SAR, "SAR"},

    {Opcode::KECCAK256, "KECCAK256"},

    {Opcode::ADDRESS, "ADDRESS"},
    {Opcode::BALANCE, "BALANCE"},
    {Opcode::ORIGIN, "ORIGIN"},
    {Opcode::CALLER, "CALLER"},
    {Opcode::CALLVALUE, "CALLVALUE"},
    {Opcode::CALLDATALOAD, "CALLDATALOAD"},
    {Opcode::CALLDATASIZE, "CALLDATASIZE"},
    {Opcode::CALLDATACOPY, "CALLDATACOPY"},
    {Opcode::CODESIZE, "CODESIZE"},
    {Opcode::CODECOPY, "CODECOPY"},
    {Opcode::GASPRICE, "GASPRICE"},
    {Opcode::EXTCODESIZE, "EXTCODESIZE"},
    {Opcode::EXTCODECOPY, "EXTCODECOPY"},
    {Opcode::RETURNDATASIZE, "RETURNDATASIZE"},
    {Opcode::RETURNDATACOPY, "RETURNDATACOPY"},
    {Opcode::EXTCODEHASH, "EXTCODEHASH"},

    {Opcode::BLOCKHASH, "BLOCKHASH"},
    {Opcode::COINBASE, "COINBASE"},
    {Opcode::TIMESTAMP, "TIMESTAMP"},
    {Opcode::NUMBER, "NUMBER"},
    {Opcode::DIFFICULTY, "DIFFICULTY"},
    {Opcode::GASLIMIT, "GASLIMIT"},
    {Opcode::CHAINID, "CHAINID"},
    {Opcode::SELFBALANCE, "SELFBALANCE"},
    {Opcode::BASEFEE, "BASEFEE"},
    {Opcode::BLOBHASH, "BLOBHASH"},
    {Opcode::BLOBBASEFEE, "BLOBBASEFEE"},

    {Opcode::POP, "POP"},
    {Opcode::MLOAD, "MLOAD"},
    {Opcode::MSTORE, "MSTORE"},
    {Opcode::MSTORE8, "MSTORE8"},
    {Opcode::SLOAD, "SLOAD"},
    {Opcode::SSTORE, "SSTORE"},
    {Opcode::JUMP, "JUMP"},
    {Opcode::JUMPI, "JUMPI"},
    {Opcode::PC, "PC"},
    {Opcode::MSIZE, "MSIZE"},
    {Opcode::GAS, "GAS"},
    {Opcode::JUMPDEST, "JUMPDEST"},
    {Opcode::TLOAD, "TLOAD"},
    {Opcode::TSTORE, "TSTORE"},
    {Opcode::MCOPY, "MCOPY"},
    {Opcode::PUSH0, "PUSH0"},

    {Opcode::PUSH1, "PUSH1"},
    {Opcode::PUSH2, "PUSH2"},
    {Opcode::PUSH3, "PUSH3"},
    {Opcode::PUSH4, "PUSH4"},
    {Opcode::PUSH5, "PUSH5"},
    {Opcode::PUSH6, "PUSH6"},
    {Opcode::PUSH7, "PUSH7"},
    {Opcode::PUSH8, "PUSH8"},
    {Opcode::PUSH9, "PUSH9"},
    {Opcode::PUSH10, "PUSH10"},
    {Opcode::PUSH11, "PUSH11"},
    {Opcode::PUSH12, "PUSH12"},
    {Opcode::PUSH13, "PUSH13"},
    {Opcode::PUSH14, "PUSH14"},
    {Opcode::PUSH15, "PUSH15"},
    {Opcode::PUSH16, "PUSH16"},
    {Opcode::PUSH17, "PUSH17"},
    {Opcode::PUSH18, "PUSH18"},
    {Opcode::PUSH19, "PUSH19"},
    {Opcode::PUSH20, "PUSH20"},
    {Opcode::PUSH21, "PUSH21"},
    {Opcode::PUSH22, "PUSH22"},
    {Opcode::PUSH23, "PUSH23"},
    {Opcode::PUSH24, "PUSH24"},
    {Opcode::PUSH25, "PUSH25"},
    {Opcode::PUSH26, "PUSH26"},
    {Opcode::PUSH27, "PUSH27"},
    {Opcode::PUSH28, "PUSH28"},
    {Opcode::PUSH29, "PUSH29"},
    {Opcode::PUSH30, "PUSH30"},
    {Opcode::PUSH31, "PUSH31"},
    {Opcode::PUSH32, "PUSH32"},

    {Opcode::DUP1, "DUP1"},
    {Opcode::DUP2, "DUP2"},
    {Opcode::DUP3, "DUP3"},
    {Opcode::DUP4, "DUP4"},
    {Opcode::DUP5, "DUP5"},
    {Opcode::DUP6, "DUP6"},
    {Opcode::DUP7, "DUP7"},
    {Opcode::DUP8, "DUP8"},
    {Opcode::DUP9, "DUP9"},
    {Opcode::DUP10, "DUP10"},
    {Opcode::DUP11, "DUP11"},
    {Opcode::DUP12, "DUP12"},
    {Opcode::DUP13, "DUP13"},
    {Opcode::DUP14, "DUP14"},
    {Opcode::DUP15, "DUP15"},
    {Opcode::DUP16, "DUP16"},

    {Opcode::SWAP1, "SWAP1"},
    {Opcode::SWAP2, "SWAP2"},
    {Opcode::SWAP3, "SWAP3"},
    {Opcode::SWAP4, "SWAP4"},
    {Opcode::SWAP5, "SWAP5"},
    {Opcode::SWAP6, "SWAP6"},
    {Opcode::SWAP7, "SWAP7"},
    {Opcode::SWAP8, "SWAP8"},
    {Opcode::SWAP9, "SWAP9"},
    {Opcode::SWAP10, "SWAP10"},
    {Opcode::SWAP11, "SWAP11"},
    {Opcode::SWAP12, "SWAP12"},
    {Opcode::SWAP13, "SWAP13"},
    {Opcode::SWAP14, "SWAP14"},
    {Opcode::SWAP15, "SWAP15"},
    {Opcode::SWAP16, "SWAP16"},

    {Opcode::LOG0, "LOG0"},
    {Opcode::LOG1, "LOG1"},
    {Opcode::LOG2, "LOG2"},
    {Opcode::LOG3, "LOG3"},
    {Opcode::LOG4, "LOG4"},

    {Opcode::EXTENSION, "EXTENSION"},
    //TODO: Way to use getExtensionOpcodeString() after EXTENSION opcode is parsed when parsing bytecode

    {Opcode::CREATE, "CREATE"},
    {Opcode::CALL, "CALL"},
    {Opcode::CALLCODE, "CALLCODE"},
    {Opcode::RETURN, "RETURN"},
    {Opcode::DELEGATECALL, "DELEGATECALL"},
    {Opcode::CREATE2, "CREATE2"},
    {Opcode::STATICCALL, "STATICCALL"},
    {Opcode::REVERT, "REVERT"},
    {Opcode::INVALID, "INVALID"},
    {Opcode::SELFDESTRUCT, "SELFDESTRUCT"},
};

std::map<ExtensionOpcode, std::string> extensionOpcodeStrings = {};

std::string opcodeToString(Opcode opcode) {
  return opcodeStrings[opcode];
};

std::string extensionOpcodeToString(ExtensionOpcode opcode) {
  return extensionOpcodeStrings[opcode];
};
