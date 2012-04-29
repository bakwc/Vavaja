main: main.o misc.o regs.o memory.o parsecmd.o
	g++ main.o misc.o regs.o memory.o parsecmd.o -o translator.exe
main.o: main.cpp ../params/defines.h misc.h
	g++ -std=c++0x main.cpp -c -o main.o
misc.o: misc.cpp misc.h
	g++ -std=c++0x misc.cpp -c -o misc.o
regs.o: regs.cpp misc.h
	g++ -std=c++0x regs.cpp -c -o regs.o
memory.o: memory.cpp memory.h regs.h misc.h
	g++ -std=c++0x memory.cpp -c -o memory.o
parsecmd.o: parsecmd.cpp parsecmd.h misc.h regs.h ../params/defines.h memory.h
	g++ -std=c++0x parsecmd.cpp -c -o parsecmd.o
clean:
	rm -rf main.o
	rm -rf translator.exe
	rm -rf misc.o
	rm -rf regs.o
	rm -rf memory.o
	rm -rf parsecmd.o