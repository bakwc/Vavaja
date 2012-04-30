#pragma once

#include <vector>
#include <string>
#include <fstream>
#include "misc.h"
#include "regs.h"
#include "memory.h"
#include "labels.h"

typedef std::vector<std::string> Lines;

struct SyntaxRecord
{
	unsigned char code;
	std::string cmd;
	Lines args;
};

class Analyzer
{
public:
	Analyzer(Memory *memory, Registers *regs, Label * label):memory_(memory),regs_(regs),labels_(label){curLine_=0;}
						// Класс зависит от Memory и Registers
	void load(const std::string fname);
						// Загрузка листинга программы
	void loadSyntax(const std::string fname);
	void process();
						// Обработка программы, результат будет в памяти
private:
	Memory *memory_;
	Registers *regs_;
	Label *labels_;
	Lines listing_;
	std::vector<SyntaxRecord> syntax_;
	int curLine_;
};
