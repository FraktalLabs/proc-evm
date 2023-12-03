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
	mkdir -p builds/state/
	clang++ -std=c++20 -I ${INTX_LIB_PATH} -I ${ETHASH_LIB_PATH} -c src/state/state.cpp -o builds/state/state.o
	clang++ -std=c++20 -I ${INTX_LIB_PATH} -I ${ETHASH_LIB_PATH} ${ETHASH_LINK_PATH} ${ETHASH_LINK_PATH2} ${ETHASH_LINK_PATH3} ${ETHASH_LINK_PATH4} builds/opcodes.o builds/stack.o builds/memory.o builds/call_context.o builds/state/state.o src/main.cpp -o bin/main
