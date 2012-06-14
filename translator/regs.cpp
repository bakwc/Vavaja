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
#include "regs.h"

Registers::Registers()
{
	initRegs();
	initRegsFloat();
}

//------------------------------------------------------------------------------------------
void Registers::initRegs()
{
    regs["ah"]=0;
    regs["bh"]=1;
    regs["ch"]=2;
    regs["dh"]=3;
    regs["eh"]=4;
    regs["sp"]=5;
    regs["pc"]=6;
    regs["rh"]=7;
}

//------------------------------------------------------------------------------------------
void Registers::initRegsFloat()
{
    regsFloat["eax"]=0;
    regsFloat["ebx"]=1;
    regsFloat["ecx"]=2;
    regsFloat["edx"]=3;
    regsFloat["eex"]=4;
    regsFloat["esp"]=5;
}

//------------------------------------------------------------------------------------------
bool Registers::isReg(const std::string &str)
{
	return regs.find(str)!=regs.end();
}

//------------------------------------------------------------------------------------------
bool Registers::isRegFloat(const std::string &str)
{
	return regsFloat.find(str)!=regsFloat.end();
}

//------------------------------------------------------------------------------------------
unsigned Registers::getReg(const std::string &str)
{
	return regs[str];
}

//------------------------------------------------------------------------------------------
unsigned Registers::getRegFloat(const std::string &str)
{
	return regsFloat[str];
}
