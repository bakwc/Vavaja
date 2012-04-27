main: main.o
	g++ main.o -o translator.exe
main.o: main.cpp
	g++ -std=c++0x main.cpp -c -o main.o
clear:
	rm -rf main.o
	rm -rf translator.exe
