#pragma once

#include "misc.h"
#include "regs.h"
#include "memory.h"
#include "../params/defines.h"

void cmdMov(Args &args,Regs &regs,Regs &regsFloat,int &cur,unsigned char *bcode,int &cline);
				// Обработка команды mov
void cmdTwoRegs(Args &args,Regs &regs,Regs &regsFloat,int &cur,unsigned char *bcode,int &cline,OpType startCode);
				// Обработка команд с двумя аргументами (add, sub, cmp)
void cmdOneRegs(Args &args,Regs &regs,Regs &regsFloat,int &cur,unsigned char *bcode,int &cline,OpType startCode);
				// Обработка команд с одним аргументом (mul, div)
void cmdJmp(Args &args,Regs &regs,Regs &regsFloat,int &cur,unsigned char *bcode,int &cline,OpType startCode);
				// Обработка команд прыжка (jmp, je, jg, jl, jne)
