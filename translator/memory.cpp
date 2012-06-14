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
#include "memory.h"

//------------------------------------------------------------------------------------------
Memory::Memory(Registers *regs)
{
	regs_=regs;
	memory_=new unsigned char [5000];
	cur_=0;
}

//------------------------------------------------------------------------------------------
Memory::~Memory()
{
	delete [] memory_;
}

//------------------------------------------------------------------------------------------
bool Memory::isMemory(std::string &str)
{
	if (str.length()==1) return false;
    if (str[0]=='%')
    {
        str.erase(0,1);
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------------------
void Memory::putByte(const unsigned char byte)
{
    *(memory_+cur_)=byte;
    cur_++;
}

//------------------------------------------------------------------------------------------
void Memory::putNum(const std::string num)
{
    *((short*)(memory_+cur_))=atoi(num);
    cur_+=2;
}

void Memory::putTwoBytes(unsigned char addr, short num)
{
	*((short*)(memory_+addr))=num;
}

//------------------------------------------------------------------------------------------
void Memory::putFloat(const std::string num)
{
    *((float*)(memory_+cur_))=atof(num);
    cur_+=4;
}

//------------------------------------------------------------------------------------------
void Memory::putReg(const std::string reg)
{
    *(memory_+cur_)=regs_->getReg(reg);
    cur_++;
}

//------------------------------------------------------------------------------------------
void Memory::putRegFloat(const std::string reg)
{
    *(memory_+cur_)=regs_->getRegFloat(reg);
    cur_++;
}

//------------------------------------------------------------------------------------------
void Memory::print() const
{
	for (int i=0;i<cur_;i++)
    {
        const int j=(*(char*)(memory_+i));
        std::cout << j << " ";
    }
	std::cout << "\n";
}

//------------------------------------------------------------------------------------------
void Memory::save(const std::string fname) const
{
	std::ofstream out(fname,std::ofstream::binary);
    out.write((char*)memory_,cur_);
    out.close();
}

//-------------------------------------------------------------------
unsigned char Memory::getCurrent() const
{
	return cur_;
}