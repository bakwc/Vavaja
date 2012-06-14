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
