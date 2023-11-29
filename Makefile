all: main

clean:
	rm -rf bin/ builds/

main:
	mkdir -p bin/ builds/
	clang++ -std=c++20 -c src/opcodes.cpp -o builds/opcodes.o
	clang++ -std=c++20 -c src/call_context.cpp -o builds/call_context.o
	clang++ -std=c++20 src/main.cpp builds/call_context.o builds/opcodes.o -o bin/main
