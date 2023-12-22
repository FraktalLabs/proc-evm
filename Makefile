INTX_LIB_PATH?=/home/brandon/workspace/blockchain/FraktalLabs/intx/include
ETHASH_LIB_PATH?=/home/brandon/workspace/blockchain/FraktalLabs/ethash/include
ETHASH_LINK_PATH?=/home/brandon/workspace/blockchain/FraktalLabs/ethash/build/lib/keccak/CMakeFiles/keccak.dir/keccak.c.o
ETHASH_LINK_PATH2?=/home/brandon/workspace/blockchain/FraktalLabs/ethash/build/lib/ethash/CMakeFiles/ethash.dir/ethash.cpp.o
ETHASH_LINK_PATH3?=/home/brandon/workspace/blockchain/FraktalLabs/ethash/build/lib/ethash/CMakeFiles/ethash.dir/primes.c.o
ETHASH_LINK_PATH4?=/home/brandon/workspace/blockchain/FraktalLabs/ethash/build/lib/global_context/CMakeFiles/global-context.dir/global_context.cpp.o

all: main

clean:
	rm -rf bin/ builds/

main:
	mkdir -p bin/ builds/
	clang++ -std=c++20 -c src/opcodes.cpp -o builds/opcodes.o
	clang++ -std=c++20 -I ${INTX_LIB_PATH} -I ${ETHASH_LIB_PATH} -c src/stack.cpp -o builds/stack.o
	clang++ -std=c++20 -I ${INTX_LIB_PATH} -I ${ETHASH_LIB_PATH} -c src/memory.cpp -o builds/memory.o
	clang++ -std=c++20 -I ${INTX_LIB_PATH} -I ${ETHASH_LIB_PATH} -c src/call_context.cpp -o builds/call_context.o
	clang++ -std=c++20 -I ${INTX_LIB_PATH} -I ${ETHASH_LIB_PATH} -c src/utils.cpp -o builds/utils.o
	clang++ -std=c++20 -I ${INTX_LIB_PATH} -I ${ETHASH_LIB_PATH} -c src/rlp.cpp -o builds/rlp.o
	mkdir -p builds/state/
	clang++ -std=c++20 -I ${INTX_LIB_PATH} -I ${ETHASH_LIB_PATH} -c src/state/state.cpp -o builds/state/state.o
	mkdir -p builds/cmds/
	clang++ -std=c++20 -I ${INTX_LIB_PATH} -I ${ETHASH_LIB_PATH} -c src/cmds/deployContract.cpp -o builds/cmds/deployContract.o
	clang++ -std=c++20 -I ${INTX_LIB_PATH} -I ${ETHASH_LIB_PATH} -c src/cmds/runCode.cpp -o builds/cmds/runCode.o
	clang++ -std=c++20 -I ${INTX_LIB_PATH} -I ${ETHASH_LIB_PATH} ${ETHASH_LINK_PATH} ${ETHASH_LINK_PATH2} ${ETHASH_LINK_PATH3} ${ETHASH_LINK_PATH4} builds/opcodes.o builds/stack.o builds/memory.o builds/call_context.o builds/state/state.o builds/cmds/deployContract.o builds/cmds/runCode.o builds/utils.o builds/rlp.o src/main.cpp -o bin/proc-evm

run-test:
	./bin/proc-evm run --snapshotFile snapshot.txt --blockContextFile blkContext.txt --txContextFile txContext.txt --contractCode 600260040160005260206000f3

deploy-test:
	./bin/proc-evm deploy --snapshotFile snapshot.txt --blockContextFile blkContext.txt --txContextFile txContext.txt --contractCode 6001600201600a55600D6014600039600D6000F3600260040160005260206000F3
