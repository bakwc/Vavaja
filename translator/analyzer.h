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
	Analyzer(Memory *memory, Registers *regs):memory_(memory),regs_(regs)
	{
		curLine_=0;
	}
	void load(const std::string fname);
	void process();
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

void cmdMov(Args &args,Regs &regs,Regs &regsFloat,int &cur,unsigned char *bcode,int &cline);
				// Обработка команды mov
void cmdTwoRegs(Args &args,Regs &regs,Regs &regsFloat,int &cur,unsigned char *bcode,int &cline,OpType startCode);
				// Обработка команд с двумя аргументами (add, sub, cmp)
void cmdOneRegs(Args &args,Regs &regs,Regs &regsFloat,int &cur,unsigned char *bcode,int &cline,OpType startCode);
				// Обработка команд с одним аргументом (mul, div)
void cmdJmp(Args &args,Regs &regs,Regs &regsFloat,int &cur,unsigned char *bcode,int &cline,OpType startCode);
				// Обработка команд прыжка (jmp, je, jg, jl, jne)
