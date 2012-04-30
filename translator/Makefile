main: main.o misc.o regs.o memory.o analyzer.o labels.o
	g++ main.o misc.o regs.o memory.o analyzer.o labels.o -o translator
main.o: main.cpp misc.h
	g++ -std=c++0x main.cpp -c -o main.o
misc.o: misc.cpp misc.h
	g++ -std=c++0x misc.cpp -c -o misc.o
regs.o: regs.cpp misc.h
	g++ -std=c++0x regs.cpp -c -o regs.o
memory.o: memory.cpp memory.h regs.h misc.h
	g++ -std=c++0x memory.cpp -c -o memory.o
analyzer.o: analyzer.cpp analyzer.h misc.h regs.h memory.h labels.h
	g++ -std=c++0x analyzer.cpp -c -o analyzer.o
labels.o: labels.h labels.cpp
	g++ -std=c++0x labels.cpp -c -o labels.o
clean:
	rm -rf main.o
	rm -rf translator.exe
	rm -rf translator
	rm -rf misc.o
	rm -rf regs.o
	rm -rf memory.o
	rm -rf analyzer.o
	rm -rf labels.o