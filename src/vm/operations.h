#pragma once

#include <map>

#include <ethash/keccak.h>

#include "opcodes.h"
#include "call_context.h"

enum ExecStatus {
  CONTINUE,
  RETURNEXEC,
  STOPEXEC,
  REVERTEXEC,
};

class Operation {
public:
  virtual ExecStatus execute(CallContext&) = 0;
};

using JumpTable = std::map<Opcode, Operation*>;
using ExtensionJumpTable = std::map<ExtensionOpcode, Operation*>;

class StopOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class AddOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class MulOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class SubOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class DivOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class SdivOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class ModOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class SmodOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class AddmodOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class MulmodOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class ExpOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class SignextendOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class LtOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class GtOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class SltOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class SgtOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class EqOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class IszeroOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class AndOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class OrOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class XorOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class NotOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class ByteOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class ShlOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class ShrOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class SarOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class Keccak256Operation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class AddressOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class BalanceOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class OriginOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class CallerOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class CallvalueOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class CalldataloadOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class CalldatasizeOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class CalldatacopyOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class CodesizeOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class CodecopyOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class GaspriceOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class ExtcodesizeOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class ExtcodecopyOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class ReturndatasizeOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class ReturndatacopyOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class ExtcodehashOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class BlockhashOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class CoinbaseOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class TimestampOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class NumberOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class DifficultyOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class GaslimitOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class ChainidOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class SelfbalanceOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class BasefeeOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class BlobhashOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class BlobbasefeeOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class PopOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class MloadOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class MstoreOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class Mstore8Operation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class SloadOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class SstoreOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class JumpOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class JumpiOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class PcOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class MsizeOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class GasOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class JumpdestOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class TloadOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class TstoreOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class McopyOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class Push0Operation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class Push1Operation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

template <uint8_t N>
class PushNOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

template <uint8_t N>
class DupNOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

template <uint8_t N>
class SwapNOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

template <uint8_t N>
class LogNOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class ExtensionOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class CreateOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class CallOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class CallcodeOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class ReturnOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class DelegatecallOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class Create2Operation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class StaticcallOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class RevertOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class InvalidOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class SelfdestructOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

extern JumpTable jumpTable;

// Add extension opcodes to this table
extern ExtensionJumpTable extensionJumpTable;

Operation* getOperation(Opcode opcode);
Operation* getExtensionOperation(ExtensionOpcode opcode);
