#include "misc.h"
#include "regs.h"
#include "memory.h"
#include "analyzer.h"
#include "labels.h"

//------------------------------------------------------------------------------------------
int main(int argc, char **argv)
{
	Registers registers;
	Memory memory(&registers);
	Label label(&memory);
	Analyzer analyzer(&memory,&registers,&label);
	analyzer.loadSyntax("../params/opcodes.cfg");
	analyzer.load("../demo/program.asm");
	analyzer.process();
	memory.print();
	memory.save("../demo/program.ve");
    return 0;
}
