#pragma once

#include <string>
#include <map>

typedef std::map<std::string,unsigned> Regs;

class Registers
{
public:
	Registers();
	bool isReg(const std::string &str);
	bool isRegFloat(const std::string &str);
	unsigned getReg(const std::string &str);
	unsigned getRegFloat(const std::string &str);
private:
	Regs regs,regsFloat;
	void initRegs();
	void initRegsFloat();
};
