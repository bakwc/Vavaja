#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "regs.h"
#include "misc.h"

class Memory
{
public:
	Memory(Registers *regs);
	~Memory();
	bool isMemory(std::string &str);
	void putByte(const unsigned char byte);
	void putNum(const std::string num);
	void putFloat(const std::string num);
	void putReg(const std::string reg);
	void putRegFloat(const std::string reg);
	void print() const;
	void save(const std::string fname) const;
private:
	int cur_;
	Registers *regs_;
	unsigned char *memory_;
};
