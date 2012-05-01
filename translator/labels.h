#pragma once

#include <map>
#include <string>
#include <iostream>
#include "memory.h"

class Label
{
public:
	Label(Memory *memory):memory_(memory) {}
	bool isLabel(const std::string & str);		// проверка, является ли команда меткой
	void addLabel(const std::string & str, unsigned char addr);	// добавление метки и адреса на котором она стоит
	void addAddr(unsigned char addr, const std::string & lbl);	// добавление адреса, на который надо подставить адрес метки
	void setLabels();										// расстановка меток по нужным адресам
private:
	std::map<std::string,unsigned char> labels1_;
	std::map<unsigned char, std::string> labels2_;
	Memory *memory_;
};
