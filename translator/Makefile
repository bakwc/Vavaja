main: main.o
	g++ main.o misc.o -o translator.exe
main.o: main.cpp ../params/defines.h misc.h
	g++ -std=c++0x main.cpp -c -o main.o
misc.o: misc.cpp misc.h
	g++ -std=c++0x misc.cpp -c -o misc.o
clean:
	rm -rf main.o
	rm -rf translator.exe
	rm -rf misc.o
