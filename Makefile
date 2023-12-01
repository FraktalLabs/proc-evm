INTX_LIB_PATH?=/home/brandon/workspace/blockchain/FraktalLabs/intx/include

all: main

clean:
	rm -rf bin/ builds/

main:
	mkdir -p bin/ builds/
	clang++ --std=c++20 -c src/opcodes.cpp -o builds/opcodes.o
	clang++ --std=c++20 -I ${INTX_LIB_PATH} -c src/stack.cpp -o builds/stack.o
	clang++ --std=c++20 -I ${INTX_LIB_PATH} -c src/memory.cpp -o builds/memory.o
	clang++ --std=c++20 -I ${INTX_LIB_PATH} -c src/call_context.cpp -o builds/call_context.o
	mkdir -p builds/state/
	clang++ --std=c++20 -I ${INTX_LIB_PATH} -c src/state/state.cpp -o builds/state/state.o
	clang++ --std=c++20 -I ${INTX_LIB_PATH} builds/opcodes.o builds/stack.o builds/memory.o builds/call_context.o builds/state/state.o src/main.cpp -o bin/main
