#pragma once

#include <vector>
#include <string>
#include <fstream>
#include "misc.h"
#include "regs.h"
#include "memory.h"
#include "../params/defines.h"

typedef std::vector<std::string> Lines;

class Analyzer
{
public:
	Analyzer(Memory *memory, Registers *regs):memory_(memory),regs_(regs){curLine_=0;}
						// Класс зависит от Memory и Registers
	void load(const std::string fname);
						// Загрузка листинга программы
	void process();
						// Обработка программы, результат будет в памяти
private:
	Memory *memory_;
	Registers *regs_;
	Lines listing_;
	int curLine_;
	void parseMov(Args &args);
	void parseTwo(Args &args,const OpType startCode);
	void parseOne(Args &args,const OpType startCode);
	void parseJmp(Args &args,const OpType startCode);
};
