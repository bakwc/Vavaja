#pragma once

#include <map>
#include <string>
#include <iostream>
#include "memory.h"

class Label
{
public:
	Label(Memory *memory):memory_(memory) {}
	bool isLabel(const std::string & str);
	void addLabel(const std::string & str, unsigned char addr);
	void addAddr(unsigned char addr, std::string & lbl);
	void setLabels();
private:
	std::map<std::string,unsigned char> labels1_;
	std::map<unsigned char, std::string> labels2_; 
	Memory *memory_;
};
