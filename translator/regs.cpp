#include "regs.h"

//------------------------------------------------------------------------------------------
bool isRegister(std::string &str, Regs &regs)
{
    return regs.find(str)!=regs.end();
}

//------------------------------------------------------------------------------------------
void initRegs(Regs &regs)
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
void initRegsFloat(Regs &regs)
{
    regs["eax"]=0;
    regs["ebx"]=1;
    regs["ecx"]=2;
    regs["edx"]=3;
    regs["eex"]=4;
    regs["esp"]=5;
}
