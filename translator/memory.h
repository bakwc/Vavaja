/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
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
	unsigned char getCurrent() const;			// Возвращает текущий размер памяти
	void putTwoBytes(unsigned char addr, short num); // Кладёт память двухбайтное целое число
private:
	int cur_;
	Registers *regs_;
	unsigned char *memory_;
};
