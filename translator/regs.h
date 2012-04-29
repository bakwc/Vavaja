#pragma once

#include <string>
#include <map>

typedef std::map<std::string,unsigned> Regs;

bool isRegister(std::string &str, Regs &regs);	// ѕроверка, €вл€етс€ ли регистром
void initRegs(Regs &regs);						// »нициализирует буквенные имена регистров числами
void initRegsFloat(Regs &regs);					// »нициализирует буквенные имена регистров числами
