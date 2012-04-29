#include "memory.h"

//------------------------------------------------------------------------------------------
bool isMemory(std::string &str)
{
    if (str[0]=='%')
    {
        str.erase(0,1);
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------------------
void putByte(const unsigned char byte,unsigned char *addr,int &cur)
{
    *(addr+cur)=byte;
    cur++;
}

//------------------------------------------------------------------------------------------
void putNum(std::string num,unsigned char *addr,int &cur)
{
    *((short*)(addr+cur))=atoi(num);
    cur+=2;
}

//------------------------------------------------------------------------------------------
void putFloat(std::string num,unsigned char *addr,int &cur)
{
    *((float*)(addr+cur))=atoi(num);
    cur+=4;
}

//------------------------------------------------------------------------------------------
void putReg(std::string reg,Regs &regs,unsigned char *addr,int &cur)
{
    *(addr+cur)=regs[reg];
    cur++;
}

//------------------------------------------------------------------------------------------
void printBcode(unsigned char *bcode, size_t len)
{
	for (int i=0;i<len;i++)
    {
        int j=(*(char*)(bcode+i));
        std::cout << j << " ";
    }
	std::cout << "\n";
}