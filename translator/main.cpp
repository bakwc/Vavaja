#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>
#include "../params/defines.h"
#include "misc.h"
#include "regs.h"
#include "memory.h"
#include "analyzer.h"

//------------------------------------------------------------------------------------------
int main(int argc, char **argv)
{
	Registers registers;
	Memory memory(&registers);
	Analyzer analyzer(&memory,&registers);
	analyzer.load("../demo/program.asm");
	analyzer.process();
	memory.print();
	memory.save("../demo/program.ve");

    return 0;
}
