main: main.o
	g++ main.o -o vavaja
main.o: main.cpp defines.h
	g++ -std=c++0x main.cpp -c -o main.o
clean:
	rm -rf main.o
	rm -rf vavaja
	rm -rf vavaja.exe
	rm -rf debug.txt
