main: main.o
	g++ main.o -o interpreter.exe
main.o: main.cpp
	g++ -std=c++0x main.cpp -c -o main.o
clean:
	rm -rf main.o
	rm -rf interpreter.exe
