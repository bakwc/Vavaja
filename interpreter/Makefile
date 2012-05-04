main: main.o
	g++ main.o -o interpreter
main.o: main.cpp defines.h
	g++ -std=c++0x main.cpp -c -o main.o
clean:
	rm -rf main.o
	rm -rf interpreter
	rm -rf interpreter.exe
	rm -rf debug.txt
