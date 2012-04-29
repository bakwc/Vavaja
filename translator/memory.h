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
	bool isMemory(std::string &str);			// Проверка, является ли аргумент памятью
	void putByte(const unsigned char byte);		// Кладёт в память байт
	void putNum(const std::string num);			// Кладёт в память целое число
	void putFloat(const std::string num);		// Кладёт в память дробное число
	void putReg(const std::string reg);			// Кладёт в память целый регистр
	void putRegFloat(const std::string reg);	// Кладёт в память дробный регистр
	void print() const;							// Выводит содержимое памяти на экран
	void save(const std::string fname) const;	// Сохраняет память в двоичный файл
private:
	int cur_;
	Registers *regs_;
	unsigned char *memory_;
};
