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
#include <map>

typedef std::map<std::string,unsigned> Regs;

class Registers
{
public:
	Registers();
	bool isReg(const std::string &str);				// Проверка, является ли целым регистром
	bool isRegFloat(const std::string &str);		// Проверка, является ли дробным регистром
	unsigned getReg(const std::string &str);		// Возвращает номер целого регистра
	unsigned getRegFloat(const std::string &str);	// Возвращает номер дробного регистра
private:
	Regs regs,regsFloat;
	void initRegs();
	void initRegsFloat();
};
