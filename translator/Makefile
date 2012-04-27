main: main.o
	g++ main.o -o translator.exe
main.o: main.cpp ../params/defines.h
	g++ -std=c++0x main.cpp -c -o main.o
clean:
	rm -rf main.o
	rm -rf translator.exe
