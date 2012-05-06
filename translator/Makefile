main: main.o misc.o regs.o memory.o analyzer.o labels.o
	g++ main.o misc.o regs.o memory.o analyzer.o labels.o -o vavajatr
tests: unit-tests.o misc.o regs.o analyzer.o labels.o memory.o
	g++ unit-tests.o misc.o regs.o memory.o analyzer.o labels.o -o unit-tests
main.o: main.cpp misc.h memory.h regs.h labels.h regs.h
	g++ -std=c++0x main.cpp -c -o main.o
unit-tests.o: unit-tests.cpp misc.h
	g++ -std=c++0x unit-tests.cpp -c -o unit-tests.o
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
	rm -rf vavajatr.exe
	rm -rf vavajatr
	rm -rf misc.o
	rm -rf regs.o
	rm -rf memory.o
	rm -rf analyzer.o
	rm -rf labels.o
	rm -rf unit-tests.o
	rm -rf unit-tests
	rm -rf unit-tests.exe
	rm -rf memory.tst
