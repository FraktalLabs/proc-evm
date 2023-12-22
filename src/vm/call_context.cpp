#include "call_context.h"

#include "operations.h"
#include "../utils/utils.h"
#include "../utils/rlp.h"

bytes CallContext::run() {
  while(pc < contract->getBytecodeSize()) {
    // Get the opcode
    Opcode opcode = contract->getOpcodeAt(pc);
    Operation* operation = getOperation(opcode);

    // Execute the operation
    ExecStatus status = operation->execute(*this);

    //TODO : Handle the status & revert?
    if(status == ExecStatus::STOPEXEC || status == ExecStatus::RETURNEXEC) {
      break;
    }

    pc++;
  }

  return ret;
}

bytes CallContext::deploy() {
  Account* callerAccount = state->getAccount(this->caller);
  // TODO: Create a new account if it doesn't exist. Is this the best spot?
  // TODO: Inc nonce in all places needed
  if(callerAccount == nullptr) {
    Account newAccount;
    state->insert(this->caller, newAccount);
    callerAccount = state->getAccount(this->caller);
  }
  uint64_t nonce = callerAccount->getNonce(); // TODO: Is this the correct address?
  bytes callerBytes;
  for(int i = 0; i < 20; i++) {
    callerBytes.push_back(this->caller[i]);
  }
  bytes encodedData = encode_tuple(callerBytes, nonce);
  uint8_t* encodedDataPtr = encodedData.data();
  uint8_t* encodedHash = ethash_keccak256(encodedDataPtr, encodedData.size()).bytes;

  // contract address is last 20 bytes of hash
  bytes contractAddressBytes(encodedHash + 12, encodedHash + 32);
  address contractAddress;
  std::string contractAddressStr;
  for (int i = 0; i < 20; i++) {
    contractAddress[i] = contractAddressBytes[i];
    contractAddressStr += byteToHex(contractAddressBytes[i]);
  }
  // TODO: functions for bytes to address, ...

  // TODO
  // contractHash = statedb.getcodehash(contractAddress)
  // Check if contractHash == empty
  
  // Create account & add to state
  Account contractAccount;
  contractAccount.initAccount(this->contract->getBytecode());
  state->insert(contractAddress, contractAccount);
  // TODO: transfer value from caller to contractAddress
  // TODO : missed things
  
  std::shared_ptr<CallContext> context = std::make_shared<CallContext>(contract, 0, state, contractAddressStr);
  bytes ret = context->run();

  // if no err : set code to ret
  state->getAccount(contractAddress)->setCode(ret);

  // delete encodedHash; // TODO
  // TODO: check ret data?
  return contractAddressBytes;
}

// TODO: pass as reference?
// TODO: Only allow certain authorized addresses to call this or allow during init
bytes CallContext::deployAt(address contractAddress) {
  std::string contractAddressStr;
  bytes contractAddressBytes;
  for (int i = 0; i < 20; i++) {
    contractAddressBytes.push_back(contractAddress[i]);
    contractAddressStr += byteToHex(contractAddressBytes[i]);
  }

  Account contractAccount;
  contractAccount.initAccount(this->contract->getBytecode());
  state->insert(contractAddress, contractAccount);

  std::shared_ptr<CallContext> context = std::make_shared<CallContext>(contract, 0, state, contractAddressStr);
  bytes ret = run();

  // if no err : set code to ret
  state->getAccount(contractAddress)->setCode(ret);

  // delete encodedHash; // TODO
  // TODO: check ret data?
  return contractAddressBytes;
}
