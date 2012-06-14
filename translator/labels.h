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
