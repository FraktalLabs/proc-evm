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

ExecStatus StopOperation::execute(CallContext&) {
  return STOPEXEC;
}

ExecStatus AddOperation::execute(CallContext& context) {
  uint256 x = context.getStack()->pop();
  uint256& y = context.getStack()->peek();
  y += x;

  return CONTINUE;
}

ExecStatus MulOperation::execute(CallContext& context) {
  uint256 x = context.getStack()->pop();
  uint256& y = context.getStack()->peek();
  y *= x;

  return CONTINUE;
}

ExecStatus SubOperation::execute(CallContext& context) {
  uint256 x = context.getStack()->pop();
  uint256& y = context.getStack()->peek();
  y -= x;

  return CONTINUE;
}

ExecStatus DivOperation::execute(CallContext& context) {
  uint256 x = context.getStack()->pop();
  uint256& y = context.getStack()->peek();
  y = y == 0 ? 0 : x / y;

  return CONTINUE;
}

ExecStatus SdivOperation::execute(CallContext& context) {
  uint256 x = context.getStack()->pop();
  uint256& y = context.getStack()->peek();
  y = y == 0 ? 0 : intx::sdivrem(x, y).quot;

  return CONTINUE;
}

ExecStatus ModOperation::execute(CallContext& context) {
  uint256 x = context.getStack()->pop();
  uint256& y = context.getStack()->peek();
  y = y == 0 ? 0 : x % y;

  return CONTINUE;
}

ExecStatus SmodOperation::execute(CallContext& context) {
  uint256 x = context.getStack()->pop();
  uint256& y = context.getStack()->peek();
  y = y == 0 ? 0 : intx::sdivrem(x, y).rem;

  return CONTINUE;
}

ExecStatus AddmodOperation::execute(CallContext& context) {
  uint256 x = context.getStack()->pop();
  uint256 y = context.getStack()->pop();
  uint256 z = context.getStack()->peek();
  z = z == 0 ? 0 : intx::addmod(x, y, z);

  return CONTINUE;
}

ExecStatus MulmodOperation::execute(CallContext& context) {
  uint256 x = context.getStack()->pop();
  uint256 y = context.getStack()->pop();
  uint256 z = context.getStack()->peek();
  z = z == 0 ? 0 : intx::mulmod(x, y, z);

  return CONTINUE;
}

ExecStatus ExpOperation::execute(CallContext& context) {
  uint256 x = context.getStack()->pop();
  uint256& y = context.getStack()->peek();
  y = intx::exp(x, y);

  return CONTINUE;
}

ExecStatus SignextendOperation::execute(CallContext& context) {
  uint256 x = context.getStack()->pop();
  uint256& y = context.getStack()->peek();

  if (x < 31) {
    // TODO: check this in detail
    uint8_t byte = static_cast<uint8_t>(y >> 8 * x);
    uint256 sign = byte & 0x80 ? uint256(-1) : 0;
    y = (y & (uint256(1) << 8 * x) - 1) | sign;
  }

  return CONTINUE;
}

ExecStatus LtOperation::execute(CallContext& context) {
  uint256 x = context.getStack()->pop();
  uint256& y = context.getStack()->peek();
  y = x < y ? 1 : 0;

  return CONTINUE;
}

ExecStatus GtOperation::execute(CallContext& context) {
  uint256 x = context.getStack()->pop();
  uint256& y = context.getStack()->peek();
  y = x > y ? 1 : 0;

  return CONTINUE;
}

ExecStatus SltOperation::execute(CallContext& context) {
  uint256 x = context.getStack()->pop();
  uint256& y = context.getStack()->peek();
  y = slt(x, y) ? 1 : 0;

  return CONTINUE;
}

ExecStatus SgtOperation::execute(CallContext& context) {
  uint256 x = context.getStack()->pop();
  uint256& y = context.getStack()->peek();
  y = slt(y, x) ? 1 : 0;

  return CONTINUE;
}

ExecStatus EqOperation::execute(CallContext& context) {
  uint256 x = context.getStack()->pop();
  uint256& y = context.getStack()->peek();
  y = x == y ? 1 : 0;

  return CONTINUE;
}

ExecStatus IszeroOperation::execute(CallContext& context) {
  uint256& x = context.getStack()->peek();
  x = x == 0 ? 1 : 0;

  return CONTINUE;
}

ExecStatus AndOperation::execute(CallContext& context) {
  uint256 x = context.getStack()->pop();
  uint256& y = context.getStack()->peek();
  y &= x;

  return CONTINUE;
}

ExecStatus OrOperation::execute(CallContext& context) {
  uint256 x = context.getStack()->pop();
  uint256& y = context.getStack()->peek();
  y |= x;

  return CONTINUE;
}

ExecStatus XorOperation::execute(CallContext& context) {
  uint256 x = context.getStack()->pop();
  uint256& y = context.getStack()->peek();
  y ^= x;

  return CONTINUE;
}

ExecStatus NotOperation::execute(CallContext& context) {
  uint256& x = context.getStack()->peek();
  x = ~x;

  return CONTINUE;
}

ExecStatus ByteOperation::execute(CallContext& context) {
  uint256 pos = context.getStack()->pop();
  uint256& x = context.getStack()->peek();

  if (pos < 32) {
    x = (x >> (8 * (31 - pos))) & 0xff;
  } else {
    x = 0;
  }

  return CONTINUE;
}

ExecStatus ShlOperation::execute(CallContext& context) {
  uint256 shift = context.getStack()->pop();
  uint256& x = context.getStack()->peek();
  x <<= shift;

  return CONTINUE;
}

ExecStatus ShrOperation::execute(CallContext& context) {
  uint256 shift = context.getStack()->pop();
  uint256& x = context.getStack()->peek();
  x >>= shift;

  return CONTINUE;
}

ExecStatus SarOperation::execute(CallContext& context) {
  uint256 shift = context.getStack()->pop();
  uint256& x = context.getStack()->peek();

  const bool isNegative = static_cast<int64_t>(x[3]) < 0;
  const auto mask = isNegative ? ~uint256(0) : uint256(0);
  const auto maskShift = shift < 256 ? (256 - shift[0]) : 0;
  x = (x >> shift) | (mask << maskShift);

  return CONTINUE;
}

constexpr auto wordSize = 32;
inline constexpr int64_t numWords(uint64_t numBytes) noexcept {
  return static_cast<int64_t>((numBytes + wordSize - 1) / wordSize);
}

ExecStatus Keccak256Operation::execute(CallContext& context) {
  uint256 offset = context.getStack()->pop();
  uint256 length = context.getStack()->peek();

  // TODO const auto numWords = ::numWords(static_cast<size_t>(length));
  const auto data = length == 0 ? nullptr : context.getMemory()->getPointer(static_cast<size_t>(offset));

  length = intx::be::load<uint256>(ethash_keccak256(data, static_cast<size_t>(length)));

  return CONTINUE;
}

ExecStatus AddressOperation::execute(CallContext& context) {
  std::string addrStr = context.getContract()->getAddressString();
  uint256 addr = intx::from_string<uint256>(addrStr);
  context.getStack()->push(addr);

  return CONTINUE;
}

ExecStatus BalanceOperation::execute(CallContext& context) {
  std::string addrStr = context.getContract()->getAddressString();
  std::shared_ptr<Account> account = context.getState()->get(addrStr);
  uint256 balance = account->getBalance();
  context.getStack()->push(balance);

  return CONTINUE;
}

ExecStatus OriginOperation::execute(CallContext& context) {
  std::string addrStr = context.getTxContext()->getOriginString();
  uint256 addr = intx::from_string<uint256>(addrStr);
  context.getStack()->push(addr);

  return CONTINUE;
}

ExecStatus CallerOperation::execute(CallContext& context) {
  std::string addrStr = context.getCallerString();
  uint256 addr = intx::from_string<uint256>(addrStr);
  context.getStack()->push(addr);

  return CONTINUE;
}

ExecStatus CallvalueOperation::execute(CallContext& context) {
  uint256 callValue = context.getValue();
  context.getStack()->push(callValue);

  return CONTINUE;
}

ExecStatus CalldataloadOperation::execute(CallContext& context) {
  uint256 offset = context.getStack()->peek();

  // TODO: Check offset range
  offset = context.getInputAt(static_cast<size_t>(offset));

  return CONTINUE;
}

ExecStatus CalldatasizeOperation::execute(CallContext& context) {
  uint256 size = context.getInputSize();
  context.getStack()->push(size);

  return CONTINUE;
}

ExecStatus CalldatacopyOperation::execute(CallContext& context) {
  uint256 memOffset = context.getStack()->pop();
  uint256 dataOffset = context.getStack()->pop();
  uint256 length = context.getStack()->pop();

  // TODO: check range / overflow
  context.getMemory()->store(static_cast<size_t>(memOffset), static_cast<size_t>(length), context.getInputPtrAt(static_cast<size_t>(dataOffset)));

  return CONTINUE;
}

ExecStatus CodesizeOperation::execute(CallContext& context) {
  uint256 size = context.getContract()->getCodeSize();
  context.getStack()->push(size);

  return CONTINUE;
}

ExecStatus CodecopyOperation::execute(CallContext& context) {
  uint256 memOffset = context.getStack()->pop();
  uint256 codeOffset = context.getStack()->pop();
  uint256 length = context.getStack()->pop();

  context.getMemory()->store(static_cast<size_t>(memOffset), static_cast<size_t>(length), context.getContract()->getBytecodePtrAt(static_cast<size_t>(codeOffset)));

  return CONTINUE;
}

ExecStatus GaspriceOperation::execute(CallContext& context) {
  uint256 gasPrice = context.getTxContext()->getGasPrice();
  context.getStack()->push(gasPrice);

  return CONTINUE;
}

ExecStatus ExtcodesizeOperation::execute(CallContext& context) {
  uint256 addr = context.getStack()->pop();
  std::string addrStr = intx::to_string(addr);
  std::shared_ptr<Account> account = context.getState()->get(addrStr);
  uint256 size = account->getCodeSize();
  context.getStack()->push(size);

  return CONTINUE;
}

ExecStatus ExtcodecopyOperation::execute(CallContext& context) {
  uint256 addr = context.getStack()->pop();
  uint256 memOffset = context.getStack()->pop();
  uint256 codeOffset = context.getStack()->pop();
  uint256 length = context.getStack()->pop();

  std::string addrStr = intx::to_string(addr);
  std::shared_ptr<Account> account = context.getState()->get(addrStr);
  context.getMemory()->store(static_cast<size_t>(memOffset), static_cast<size_t>(length), account->getCodePtrAt(static_cast<size_t>(codeOffset)));

  return CONTINUE;
}

ExecStatus ReturndatasizeOperation::execute(CallContext& context) {
  uint256 size = context.getReturnDataSize();
  context.getStack()->push(size);

  return CONTINUE;
}

ExecStatus ReturndatacopyOperation::execute(CallContext& context) {
  uint256 memOffset = context.getStack()->pop();
  uint256 dataOffset = context.getStack()->pop();
  uint256 length = context.getStack()->pop();

  context.getMemory()->store(static_cast<size_t>(memOffset), static_cast<size_t>(length), context.getReturnDataPtrAt(static_cast<size_t>(dataOffset)));

  return CONTINUE;
}

ExecStatus ExtcodehashOperation::execute(CallContext& context) {
  uint256 addr = context.getStack()->pop();
  std::string addrStr = intx::to_string(addr);
  std::shared_ptr<Account> account = context.getState()->get(addrStr);
  uint256 codeHash = account->getCodeHash();
  context.getStack()->push(codeHash);

  return CONTINUE;
}

ExecStatus BlockhashOperation::execute(CallContext& context) {
  uint256 block = context.getStack()->peek();
  // TODO: Get block data & check range / ...
  //       For now using current block hash
  uint256 blockHash = context.getBlockContext()->getBlockHash();
  block = blockHash;

  return CONTINUE;
}

ExecStatus CoinbaseOperation::execute(CallContext& context) {
  std::string coinbase = context.getBlockContext()->getCoinbaseString();
  uint256 addr = intx::from_string<uint256>(coinbase);
  context.getStack()->push(addr);

  return CONTINUE;
}

ExecStatus TimestampOperation::execute(CallContext& context) {
  uint256 timestamp = context.getBlockContext()->getTimestamp();
  context.getStack()->push(timestamp);

  return CONTINUE;
}

ExecStatus NumberOperation::execute(CallContext& context) {
  uint256 number = context.getBlockContext()->getNumber();
  context.getStack()->push(number);

  return CONTINUE;
}

ExecStatus DifficultyOperation::execute(CallContext& context) {
  uint256 difficulty = context.getBlockContext()->getDifficulty();
  context.getStack()->push(difficulty);

  return CONTINUE;
}

ExecStatus GaslimitOperation::execute(CallContext& context) {
  uint256 gasLimit = context.getBlockContext()->getGasLimit();
  context.getStack()->push(gasLimit);

  return CONTINUE;
}

ExecStatus ChainidOperation::execute(CallContext& context) {
  uint256 chainId = context.getBlockContext()->getChainId();
  context.getStack()->push(chainId);

  return CONTINUE;
}

ExecStatus SelfbalanceOperation::execute(CallContext& context) {
  std::string address = context.getContract()->getAddressString();
  std::shared_ptr<Account> account = context.getState()->get(address);
  uint256 balance = account->getBalance();
  context.getStack()->push(balance);

  return CONTINUE;
}

ExecStatus BasefeeOperation::execute(CallContext& context) {
  uint256 baseFee = context.getBaseFee();
  context.getStack()->push(baseFee);

  return CONTINUE;
}

ExecStatus BlobhashOperation::execute(CallContext& context) {
  uint256 idx = context.getStack()->peek();

  // TODO: check ranges / overflow
  std::string blobHash = context.getTxContext()->getBlobHashString(static_cast<size_t>(idx));
  uint256 hash = intx::from_string<uint256>(blobHash);
  context.getStack()->push(hash);

  return CONTINUE;
}

ExecStatus BlobbasefeeOperation::execute(CallContext& context) {
  // TODO
  
  return CONTINUE;
}

ExecStatus PopOperation::execute(CallContext& context) {
  context.getStack()->pop();

  return CONTINUE;
}

ExecStatus MloadOperation::execute(CallContext& context) {
  uint256& value = context.getStack()->peek();
  uint64_t offset = static_cast<uint64_t>(value);
  uint256 memValue = context.getMemory()->load32(offset);
  value = memValue;

  return CONTINUE;
}

ExecStatus MstoreOperation::execute(CallContext& context) {
  uint256 memStart = context.getStack()->pop();
  uint256 value = context.getStack()->pop();
  context.getMemory()->store32(static_cast<uint64_t>(memStart), static_cast<uint32_t>(value));

  return CONTINUE;
}

ExecStatus Mstore8Operation::execute(CallContext& context) {
  uint256 memStart = context.getStack()->pop();
  uint256 value = context.getStack()->pop();
  context.getMemory()->getPointer(static_cast<uint64_t>(memStart))[0] = static_cast<uint8_t>(value);

  return CONTINUE;
}

ExecStatus SloadOperation::execute(CallContext& context) {
  uint256& value = context.getStack()->peek();
  std::string callAddress = context.getContract()->getAddressString();
  uint256 sValue = context.getState()->get(callAddress)->getStorage(value);
  value = sValue;

  return CONTINUE;
}

ExecStatus SstoreOperation::execute(CallContext& context) {
  uint256 key = context.getStack()->pop();
  uint256 value = context.getStack()->pop();
  std::string callAddress = context.getContract()->getAddressString();
  std::shared_ptr<Account> account = context.getState()->get(callAddress);
  account->setStorage(key, value);

  return CONTINUE;
}

ExecStatus JumpOperation::execute(CallContext& context) {
  uint256 jumpDest = context.getStack()->pop();
  // TODO: jump to 0?
  if(!(context.getContract()->getBytecodeAt(static_cast<uint64_t>(jumpDest)) == Opcode::JUMPDEST)) {
    return STOPEXEC;
  }
  context.setPc(static_cast<uint64_t>(jumpDest) - 1); // -1 because pc is incremented after each instruction

  return CONTINUE;
}

ExecStatus JumpiOperation::execute(CallContext& context) {
  uint256 jumpDest = context.getStack()->pop();
  uint256 condition = context.getStack()->pop();
  if (condition != 0) {
    if(!(context.getContract()->getBytecodeAt(static_cast<uint64_t>(jumpDest)) == Opcode::JUMPDEST)) {
      return STOPEXEC;
    }
    context.setPc(static_cast<uint64_t>(jumpDest) - 1); // -1 because pc is incremented after each instruction
  }

  return CONTINUE;
}

ExecStatus PcOperation::execute(CallContext& context) {
  uint64_t pc = context.getPc();
  context.getStack()->push(pc);

  return CONTINUE;
}

ExecStatus MsizeOperation::execute(CallContext& context) {
  uint64_t memSize = context.getMemory()->getSize();
  context.getStack()->push(memSize);

  return CONTINUE;
}

ExecStatus GasOperation::execute(CallContext& context) {
  uint256 gas = 0; // TODO: context.getGas();
  context.getStack()->push(gas);

  return CONTINUE;
}

ExecStatus JumpdestOperation::execute(CallContext& context) {
  return CONTINUE;
}

ExecStatus TloadOperation::execute(CallContext& context) {
  // TODO
  return CONTINUE;
}

ExecStatus TstoreOperation::execute(CallContext& context) {
  // TODO
  return CONTINUE;
}

ExecStatus McopyOperation::execute(CallContext& context) {
  uint256 dest = context.getStack()->pop();
  uint256 src = context.getStack()->pop();
  uint256 len = context.getStack()->pop();

  context.getMemory()->copy(static_cast<uint64_t>(dest), static_cast<uint64_t>(src), static_cast<uint64_t>(len));
  return CONTINUE;
}

ExecStatus Push0Operation::execute(CallContext& context) {
  context.getStack()->push(0);

  return CONTINUE;
}

ExecStatus Push1Operation::execute(CallContext& context) {
  uint64_t codeLen = context.getContract()->getBytecodeSize();
  context.incPc();

  if (context.getPc() < codeLen) {
    context.getStack()->push(context.getContract()->getBytecodeAt(context.getPc()));
  } else {
    context.getStack()->push(0);
  }

  return CONTINUE;
}

template <uint8_t N>
ExecStatus PushNOperation<N>::execute(CallContext& context) {
  uint64_t codeLen = context.getContract()->getBytecodeSize();

  uint64_t start = codeLen;
  if (context.getPc() + 1 < codeLen) {
    start = context.getPc() + 1;
  }

  // TODO: wouldn't this cause a bug at end of code?
  uint64_t end = codeLen;
  if (start + N < codeLen) {
    end = start + N;
  }

  uint256 value = 0;
  for (uint64_t i = start; i < end; i++) {
    value = (value << 8) + context.getContract()->getBytecodeAt(i);
  }

  context.setPc(context.getPc() + N);
  context.getStack()->push(value);

  return CONTINUE;
}

template <uint8_t N>
ExecStatus DupNOperation<N>::execute(CallContext& context) {
  context.getStack()->dup(N);

  return CONTINUE;
}

template <uint8_t N>
ExecStatus SwapNOperation<N>::execute(CallContext& context) {
  context.getStack()->swap(N+1);

  return CONTINUE;
}

template <uint8_t N>
ExecStatus LogNOperation<N>::execute(CallContext& context) {
  // TODO
  return CONTINUE;
}

ExecStatus CreateOperation::execute(CallContext& context) {
  uint256 value = context.getStack()->pop();
  uint256 inOffset = context.getStack()->pop();
  uint256 inSize = context.getStack()->pop();

  // TODO

  return CONTINUE;
}

ExecStatus CallOperation::execute(CallContext& context) {

  uint256 gas = context.getStack()->pop();
  uint256 to = context.getStack()->pop();
  uint256 value = context.getStack()->pop();
  uint256 inOffset = context.getStack()->pop();
  uint256 inSize = context.getStack()->pop();
  uint256 outOffset = context.getStack()->pop();
  uint256 outSize = context.getStack()->pop();

  // TODO

  std::shared_ptr<State> state = context.getState();
  std::string addressStr = intx::to_string(to, 16);
  std::shared_ptr<Account> account = state->get(addressStr);
  bytes bytecode = account->getCode();
  std::shared_ptr<Contract> contract = std::make_shared<Contract>(bytecode, addressStr);

  std::shared_ptr<CallContext> callContext = std::make_shared<CallContext>(contract, 0, state);
  //TODO: Inherit parts of context

  callContext->run();

  context.getStack()->push(1);

  return CONTINUE;
}

ExecStatus CallcodeOperation::execute(CallContext& context) {
  uint256 gas = context.getStack()->pop();
  uint256 to = context.getStack()->pop();
  uint256 value = context.getStack()->pop();
  uint256 inOffset = context.getStack()->pop();
  uint256 inSize = context.getStack()->pop();
  uint256 outOffset = context.getStack()->pop();
  uint256 outSize = context.getStack()->pop();

  // TODO
  
  std::shared_ptr<State> state = context.getState();
  std::string addressStr = intx::to_string(to, 16);
  std::shared_ptr<Account> account = state->get(addressStr);
  bytes bytecode = account->getCode();
  std::shared_ptr<Contract> contract = std::make_shared<Contract>(bytecode, addressStr);

  std::shared_ptr<CallContext> callContext = std::make_shared<CallContext>(contract, 0, state);
  uint8_t* inputPtr = context.getMemory()->getPointer(static_cast<uint64_t>(inOffset));
  bytes callArgs(inputPtr, inputPtr + static_cast<uint64_t>(inSize));
  callContext->setInput(callArgs);

  callContext->run();

  context.getStack()->push(1);
  return CONTINUE;
}

ExecStatus ReturnOperation::execute(CallContext& context) {
  uint256 offset = context.getStack()->pop();
  uint256 size = context.getStack()->pop();

  // TODO
  uint8_t* dataStart = context.getMemory()->getPointer(static_cast<uint64_t>(offset));
  bytes data(dataStart, dataStart + static_cast<uint64_t>(size));
  context.setRet(data);

  return RETURNEXEC;
}

ExecStatus DelegatecallOperation::execute(CallContext& context) {
  uint256 gas = context.getStack()->pop();
  uint256 to = context.getStack()->pop();
  uint256 inOffset = context.getStack()->pop();
  uint256 inSize = context.getStack()->pop();
  uint256 outOffset = context.getStack()->pop();
  uint256 outSize = context.getStack()->pop();

  // TODO

  return CONTINUE;
}

ExecStatus Create2Operation::execute(CallContext& context) {
  uint256 value = context.getStack()->pop();
  uint256 salt = context.getStack()->pop();
  uint256 inOffset = context.getStack()->pop();
  uint256 inSize = context.getStack()->pop();

  // TODO

  return CONTINUE;
}

ExecStatus StaticcallOperation::execute(CallContext& context) {
  uint256 gas = context.getStack()->pop();
  uint256 to = context.getStack()->pop();
  uint256 inOffset = context.getStack()->pop();
  uint256 inSize = context.getStack()->pop();
  uint256 outOffset = context.getStack()->pop();
  uint256 outSize = context.getStack()->pop();

  // TODO

  return CONTINUE;
}

ExecStatus RevertOperation::execute(CallContext& context) {
  uint256 offset = context.getStack()->pop();
  uint256 size = context.getStack()->pop();

  // TODO

  return REVERTEXEC;
}

ExecStatus InvalidOperation::execute(CallContext& context) {
  //TODO
  return STOPEXEC;
}

ExecStatus SelfdestructOperation::execute(CallContext& context) {
  uint256 beneficiary = context.getStack()->pop();

  std::shared_ptr<State> state = context.getState();
  std::string addressStr = intx::to_string(beneficiary, 16);
  std::shared_ptr<Account> beneficiaryAccount = state->get(addressStr);

  std::string addressStr2 = context.getContract()->getAddressString();
  std::shared_ptr<Account> contractAccount = state->get(addressStr2);

  beneficiaryAccount->setBalance(beneficiaryAccount->getBalance() + contractAccount->getBalance());
  // TODO
  state->remove(addressStr2);

  return STOPEXEC;
}

JumpTable jumpTable = {
  {Opcode::STOP, new StopOperation()},
  {Opcode::ADD, new AddOperation()},
  {Opcode::MUL, new MulOperation()},
  {Opcode::SUB, new SubOperation()},
  {Opcode::DIV, new DivOperation()},
  {Opcode::SDIV, new SdivOperation()},
  {Opcode::MOD, new ModOperation()},
  {Opcode::SMOD, new SmodOperation()},
  {Opcode::ADDMOD, new AddmodOperation()},
  {Opcode::MULMOD, new MulmodOperation()},
  {Opcode::EXP, new ExpOperation()},
  {Opcode::SIGNEXTEND, new SignextendOperation()},

  {Opcode::LT, new LtOperation()},
  {Opcode::GT, new GtOperation()},
  {Opcode::SLT, new SltOperation()},
  {Opcode::SGT, new SgtOperation()},
  {Opcode::EQ, new EqOperation()},
  {Opcode::ISZERO, new IszeroOperation()},
  {Opcode::AND, new AndOperation()},
  {Opcode::OR, new OrOperation()},
  {Opcode::XOR, new XorOperation()},
  {Opcode::NOT, new NotOperation()},
  {Opcode::BYTE, new ByteOperation()},
  {Opcode::SHL, new ShlOperation()},
  {Opcode::SHR, new ShrOperation()},
  {Opcode::SAR, new SarOperation()},

  {Opcode::KECCAK256, new Keccak256Operation()},

  {Opcode::ADDRESS, new AddressOperation()},
  {Opcode::BALANCE, new BalanceOperation()},
  {Opcode::ORIGIN, new OriginOperation()},
  {Opcode::CALLER, new CallerOperation()},
  {Opcode::CALLVALUE, new CallvalueOperation()},
  {Opcode::CALLDATALOAD, new CalldataloadOperation()},
  {Opcode::CALLDATASIZE, new CalldatasizeOperation()},
  {Opcode::CALLDATACOPY, new CalldatacopyOperation()},
  {Opcode::CODESIZE, new CodesizeOperation()},
  {Opcode::CODECOPY, new CodecopyOperation()},
  {Opcode::GASPRICE, new GaspriceOperation()},
  {Opcode::EXTCODESIZE, new ExtcodesizeOperation()},
  {Opcode::EXTCODECOPY, new ExtcodecopyOperation()},
  {Opcode::RETURNDATASIZE, new ReturndatasizeOperation()},
  {Opcode::RETURNDATACOPY, new ReturndatacopyOperation()},
  {Opcode::EXTCODEHASH, new ExtcodehashOperation()},

  {Opcode::BLOCKHASH, new BlockhashOperation()},
  {Opcode::COINBASE, new CoinbaseOperation()},
  {Opcode::TIMESTAMP, new TimestampOperation()},
  {Opcode::NUMBER, new NumberOperation()},
  {Opcode::DIFFICULTY, new DifficultyOperation()},
  {Opcode::GASLIMIT, new GaslimitOperation()},
  {Opcode::CHAINID, new ChainidOperation()},
  {Opcode::SELFBALANCE, new SelfbalanceOperation()},
  {Opcode::BASEFEE, new BasefeeOperation()},
  {Opcode::BLOBHASH, new BlobhashOperation()},
  {Opcode::BLOBBASEFEE, new BlobbasefeeOperation()},

  {Opcode::POP, new PopOperation()},
  {Opcode::MLOAD, new MloadOperation()},
  {Opcode::MSTORE, new MstoreOperation()},
  {Opcode::MSTORE8, new Mstore8Operation()},
  {Opcode::SLOAD, new SloadOperation()},
  {Opcode::SSTORE, new SstoreOperation()},
  {Opcode::JUMP, new JumpOperation()},
  {Opcode::JUMPI, new JumpiOperation()},
  {Opcode::PC, new PcOperation()},
  {Opcode::MSIZE, new MsizeOperation()},
  {Opcode::GAS, new GasOperation()},
  {Opcode::JUMPDEST, new JumpdestOperation()},
  {Opcode::TLOAD, new TloadOperation()},
  {Opcode::TSTORE, new TstoreOperation()},
  {Opcode::MCOPY, new McopyOperation()},
  {Opcode::PUSH0, new Push0Operation()},

  {Opcode::PUSH1, new Push1Operation()},
  {Opcode::PUSH2, new PushNOperation<2>()},
  {Opcode::PUSH3, new PushNOperation<3>()},
  {Opcode::PUSH4, new PushNOperation<4>()},
  {Opcode::PUSH5, new PushNOperation<5>()},
  {Opcode::PUSH6, new PushNOperation<6>()},
  {Opcode::PUSH7, new PushNOperation<7>()},
  {Opcode::PUSH8, new PushNOperation<8>()},
  {Opcode::PUSH9, new PushNOperation<9>()},
  {Opcode::PUSH10, new PushNOperation<10>()},
  {Opcode::PUSH11, new PushNOperation<11>()},
  {Opcode::PUSH12, new PushNOperation<12>()},
  {Opcode::PUSH13, new PushNOperation<13>()},
  {Opcode::PUSH14, new PushNOperation<14>()},
  {Opcode::PUSH15, new PushNOperation<15>()},
  {Opcode::PUSH16, new PushNOperation<16>()},
  {Opcode::PUSH17, new PushNOperation<17>()},
  {Opcode::PUSH18, new PushNOperation<18>()},
  {Opcode::PUSH19, new PushNOperation<19>()},
  {Opcode::PUSH20, new PushNOperation<20>()},
  {Opcode::PUSH21, new PushNOperation<21>()},
  {Opcode::PUSH22, new PushNOperation<22>()},
  {Opcode::PUSH23, new PushNOperation<23>()},
  {Opcode::PUSH24, new PushNOperation<24>()},
  {Opcode::PUSH25, new PushNOperation<25>()},
  {Opcode::PUSH26, new PushNOperation<26>()},
  {Opcode::PUSH27, new PushNOperation<27>()},
  {Opcode::PUSH28, new PushNOperation<28>()},
  {Opcode::PUSH29, new PushNOperation<29>()},
  {Opcode::PUSH30, new PushNOperation<30>()},
  {Opcode::PUSH31, new PushNOperation<31>()},
  {Opcode::PUSH32, new PushNOperation<32>()},

  {Opcode::DUP1, new DupNOperation<1>()},
  {Opcode::DUP2, new DupNOperation<2>()},
  {Opcode::DUP3, new DupNOperation<3>()},
  {Opcode::DUP4, new DupNOperation<4>()},
  {Opcode::DUP5, new DupNOperation<5>()},
  {Opcode::DUP6, new DupNOperation<6>()},
  {Opcode::DUP7, new DupNOperation<7>()},
  {Opcode::DUP8, new DupNOperation<8>()},
  {Opcode::DUP9, new DupNOperation<9>()},
  {Opcode::DUP10, new DupNOperation<10>()},
  {Opcode::DUP11, new DupNOperation<11>()},
  {Opcode::DUP12, new DupNOperation<12>()},
  {Opcode::DUP13, new DupNOperation<13>()},
  {Opcode::DUP14, new DupNOperation<14>()},
  {Opcode::DUP15, new DupNOperation<15>()},
  {Opcode::DUP16, new DupNOperation<16>()},

  {Opcode::SWAP1, new SwapNOperation<1>()},
  {Opcode::SWAP2, new SwapNOperation<2>()},
  {Opcode::SWAP3, new SwapNOperation<3>()},
  {Opcode::SWAP4, new SwapNOperation<4>()},
  {Opcode::SWAP5, new SwapNOperation<5>()},
  {Opcode::SWAP6, new SwapNOperation<6>()},
  {Opcode::SWAP7, new SwapNOperation<7>()},
  {Opcode::SWAP8, new SwapNOperation<8>()},
  {Opcode::SWAP9, new SwapNOperation<9>()},
  {Opcode::SWAP10, new SwapNOperation<10>()},
  {Opcode::SWAP11, new SwapNOperation<11>()},
  {Opcode::SWAP12, new SwapNOperation<12>()},
  {Opcode::SWAP13, new SwapNOperation<13>()},
  {Opcode::SWAP14, new SwapNOperation<14>()},
  {Opcode::SWAP15, new SwapNOperation<15>()},
  {Opcode::SWAP16, new SwapNOperation<16>()},

  {Opcode::LOG0, new LogNOperation<0>()},
  {Opcode::LOG1, new LogNOperation<1>()},
  {Opcode::LOG2, new LogNOperation<2>()},
  {Opcode::LOG3, new LogNOperation<3>()},
  {Opcode::LOG4, new LogNOperation<4>()},

  {Opcode::CREATE, new CreateOperation()},
  {Opcode::CALL, new CallOperation()},
  {Opcode::CALLCODE, new CallcodeOperation()},
  {Opcode::RETURN, new ReturnOperation()},
  {Opcode::DELEGATECALL, new DelegatecallOperation()},
  {Opcode::CREATE2, new Create2Operation()},
  {Opcode::STATICCALL, new StaticcallOperation()},
  {Opcode::REVERT, new RevertOperation()},
  {Opcode::INVALID, new InvalidOperation()},
  {Opcode::SELFDESTRUCT, new SelfdestructOperation()},
};

Operation* getOperation(Opcode opcode) {
  return jumpTable[opcode];
}
