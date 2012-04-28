﻿#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include "../params/defines.h"
#include "misc.h"

using namespace std;

typedef map<string,unsigned> Regs;
typedef vector<string> Args;


//------------------------------------------------------------------------------------------
bool isRegister(string &str, Regs &regs)
{
    return regs.find(str)!=regs.end();
}
//------------------------------------------------------------------------------------------
bool isMemory(string &str)
{
    if (str[0]=='%')
    {
        str.erase(0,1);
        return true;
    }
    return false;
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
//------------------------------------------------------------------------------------------
void parse(string &str,Args &args)
{
    int n=str.find(" ");
    string tmp;
    while (n>=0)
    {
        tmp=str.substr(0,n);
        str.erase(0,n+1);
        args.push_back(tmp);
        n=str.find(" ");
    }
    args.push_back(str);
}
//------------------------------------------------------------------------------------------
void putByte(const unsigned char byte,unsigned char *addr,int &cur)
{
    *(addr+cur)=byte;
    cur++;
}
//------------------------------------------------------------------------------------------
void putNum(string num,unsigned char *addr,int &cur)
{
    *((short*)(addr+cur))=atoi(num);
    cur+=2;
}
//------------------------------------------------------------------------------------------
void putFloat(string num,unsigned char *addr,int &cur)
{
    *((float*)(addr+cur))=atoi(num);
    cur+=4;
}
//------------------------------------------------------------------------------------------
void putReg(string reg,Regs &regs,unsigned char *addr,int &cur)
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
        cout << j << " ";
    }
	cout << "\n";
}
//------------------------------------------------------------------------------------------
void cmdMov(Args &args,Regs &regs,Regs &regsFloat,int &cur,unsigned char *bcode,int &cline)
{
            if (args.size()!=3) error(cline,"Syntax error"); else
            if (isNumber(args[1]) && isRegister(args[2],regs))
            {
                putByte(OP_MOV_1,bcode,cur);
                putNum(args[1],bcode,cur);
                putReg(args[2],regs,bcode,cur);
            } else
            if (isNumber(args[1]) && isMemory(args[2]))
            {
                if (isNumber(args[2]))
                {
                    putByte(OP_MOV_2,bcode,cur);
                    putNum(args[1],bcode,cur);
                    putNum(args[2],bcode,cur);
                } else
                if (isRegister(args[2],regs))
                {
                    putByte(OP_MOV_3,bcode,cur);
                    putNum(args[1],bcode,cur);
                    putReg(args[2],regs,bcode,cur);
                } else
                {
                    error(cline,"Syntax error");
                }
            } else
            if (isFloat(args[1]) && isRegister(args[2],regsFloat))
            {
                putByte(OP_MOV_4,bcode,cur);
                putFloat(args[1],bcode,cur);
                putReg(args[2],regsFloat,bcode,cur);
            }else
            if (isFloat(args[1]) && isMemory(args[2]))
            {
                if (isNumber(args[2]))
                {
                    putByte(OP_MOV_5,bcode,cur);
                    putFloat(args[1],bcode,cur);
                    putNum(args[2],bcode,cur);
                } else
                if (isRegister(args[2],regs))
                {
                    putByte(OP_MOV_6,bcode,cur);
                    putFloat(args[1],bcode,cur);
                    putReg(args[2],regs,bcode,cur);
                } else
                {
                    error(cline,"Syntax error");
                }
            } else
            if (isRegister(args[1],regs) && isRegister(args[2],regs))
            {
                putByte(OP_MOV_7,bcode,cur);
                putReg(args[1],regs,bcode,cur);
                putReg(args[2],regs,bcode,cur);
            } else
            if (isRegister(args[1],regs) && isMemory(args[2]))
            {
                if (isNumber(args[2]))
                {
                    putByte(OP_MOV_8,bcode,cur);
                    putReg(args[1],regs,bcode,cur);
                    putNum(args[2],bcode,cur);
                } else
                if (isRegister(args[2],regs))
                {
                    putByte(OP_MOV_9,bcode,cur);
                    putReg(args[1],regs,bcode,cur);
                    putReg(args[2],regs,bcode,cur);
                } else
                {
                    error(cline,"Syntax error");
                }
            } else
            if (isRegister(args[1],regsFloat) && isRegister(args[2],regsFloat))
            {
                putByte(OP_MOV_10,bcode,cur);
                putReg(args[1],regsFloat,bcode,cur);
                putReg(args[2],regsFloat,bcode,cur);
            } else
            if (isRegister(args[1],regsFloat) && isMemory(args[2]))
            {
                if (isNumber(args[2]))
                {
                    putByte(OP_MOV_11,bcode,cur);
                    putReg(args[1],regsFloat,bcode,cur);
                    putNum(args[2],bcode,cur);
                } else
                if (isRegister(args[2],regs))
                {
                    putByte(OP_MOV_12,bcode,cur);
                    putReg(args[1],regsFloat,bcode,cur);
                    putReg(args[2],regs,bcode,cur);
                } else
                {
                    error(cline,"Syntax error");
                }
            } else
            if (isMemory(args[1]))
            {
                if (isNumber(args[1]))
                {
                    if (isRegister(args[2],regs))
                    {
                        putByte(OP_MOV_13,bcode,cur);
                        putNum(args[1],bcode,cur);
                        putReg(args[2],regs,bcode,cur);
                    } else
                    if (isRegister(args[2],regsFloat))
                    {
                        putByte(OP_MOV_14,bcode,cur);
                        putNum(args[1],bcode,cur);
                        putReg(args[2],regsFloat,bcode,cur);
                    } else
                    {
                    error(cline,"Syntax error");
                    }
                } else
                if (isRegister(args[1],regs))
                {
                    if (isRegister(args[2],regs))
                    {
                        putByte(OP_MOV_15,bcode,cur);
                        putReg(args[1],regs,bcode,cur);
                        putReg(args[2],regs,bcode,cur);
                    } else
                    if (isRegister(args[2],regsFloat))
                    {
                        putByte(OP_MOV_16,bcode,cur);
                        putReg(args[1],regs,bcode,cur);
                        putReg(args[2],regsFloat,bcode,cur);
                    } else
                    {
                    error(cline,"Syntax error");
                    }
                } else
                {
                    error(cline,"Syntax error");
                }
            }
}
//------------------------------------------------------------------------------------------
void cmdTwoRegs(Args &args,Regs &regs,Regs &regsFloat,int &cur,unsigned char *bcode,int &cline,OpType startCode)
{
            if (args.size()!=3) error(cline,"Syntax error"); else
            if (isRegister(args[2],regs))
            {
                if (isRegister(args[1],regs))
                {
                    putByte(startCode+1,bcode,cur);
                    putReg(args[1],regs,bcode,cur);
                    putReg(args[2],regs,bcode,cur);
                } else
                if (isNumber(args[1]))
                {
                    putByte(startCode,bcode,cur);
                    putNum(args[1],bcode,cur);
                    putReg(args[2],regs,bcode,cur);
                }else error(cline,"Syntax error");
            } else
            if (isRegister(args[2],regsFloat))
            {
                if (isRegister(args[1],regsFloat))
                {
                    putByte(startCode+3,bcode,cur);
                    putReg(args[1],regsFloat,bcode,cur);
                    putReg(args[2],regsFloat,bcode,cur);
                } else
                if (isFloat(args[1]))
                {
                    putByte(startCode+2,bcode,cur);
                    putFloat(args[1],bcode,cur);
                    putReg(args[2],regs,bcode,cur);
                }else error(cline,"Syntax error");

            } else error(cline,"Syntax error");
}
//------------------------------------------------------------------------------------------
void cmdOneRegs(Args &args,Regs &regs,Regs &regsFloat,int &cur,unsigned char *bcode,int &cline,OpType startCode)
{
            if (args.size()!=2) error(cline,"Syntax error"); else
			if (isNumber(args[1]))
			{
				putByte(startCode,bcode,cur);
				putNum(args[1],bcode,cur);
			} else
			if (isRegister(args[1],regs))
			{
				putByte(startCode+1,bcode,cur);
				putReg(args[1],regs,bcode,cur);
			} else
			if (isFloat(args[1]))
			{
				putByte(startCode+2,bcode,cur);
				putFloat(args[1],bcode,cur);
			} else
			if (isRegister(args[1],regsFloat))
			{
				putByte(startCode+3,bcode,cur);
				putReg(args[1],regsFloat,bcode,cur);
			} else error(cline,"Syntax error");
}

//------------------------------------------------------------------------------------------
void cmdJmp(Args &args,Regs &regs,Regs &regsFloat,int &cur,unsigned char *bcode,int &cline,OpType startCode)
{
	if (args.size()!=2) error(cline,"Syntax error"); else
		if (isMemory(args[1]))
		{
			if (isNumber(args[1]))
			{
				putByte(startCode,bcode,cur);
				putNum(args[1],bcode,cur);
			} else
			if (isRegister(args[1],regs))
			{
				putByte(startCode+1,bcode,cur);
				putReg(args[1],regs,bcode,cur);
			} else error(cline,"Syntax error");
		} else error(cline,"Syntax error");
}
//------------------------------------------------------------------------------------------
int main(int arc, char **argv)
{
    unsigned char bcode[5000];
    Regs regs,regsFloat; // Список целых и дробных регистров и их номера
    int cur=0,cline=0;
    string infile,outfile;
    infile="../demo/program.asm";
    outfile="../demo/program.ve";
    initRegs(regs);
    initRegsFloat(regsFloat);

    ifstream source(infile);
    while (!source.eof())
    {
        string tmp;
        Args args;
        getline(source,tmp);
        if (tmp.length()==0) continue;
        parse(tmp,args);
        cline++;
        if (args[0]=="pass")
        {
            putByte(OP_PASS,bcode,cur);
        }
        else
        if (args[0]=="mov")
        {
			cmdMov(args,regs,regsFloat,cur,bcode,cline);
        }
        else
        if (args[0]=="int")
        {
            if (args.size()!=2) error(cline,"Syntax error"); else
            if (isNumber(args[1]))
            {
                putByte(OP_INT,bcode,cur);
                putNum(args[1],bcode,cur);
            } else
                error(cline,"Syntax error");
        }
        else
        if (args[0]=="add")
        {
			cmdTwoRegs(args,regs,regsFloat,cur,bcode,cline,OP_ADD_1);
        }
        else
        if (args[0]=="sub")
        {
            cmdTwoRegs(args,regs,regsFloat,cur,bcode,cline,OP_SUB_1);
        } else
		if (args[0]=="mul")
		{
			cmdOneRegs(args,regs,regsFloat,cur,bcode,cline,OP_MUL_1);
		} else
		if (args[0]=="div")
		{
			cmdOneRegs(args,regs,regsFloat,cur,bcode,cline,OP_DIV_1);
		} else
		if (args[0]=="cmp")
		{
			cmdTwoRegs(args,regs,regsFloat,cur,bcode,cline,OP_CMP_1);
		} else
        if (args[0]=="jmp")
        {
			cmdJmp(args,regs,regsFloat,cur,bcode,cline,OP_JMP_1);
        } else
        if (args[0]=="je")
        {
			cmdJmp(args,regs,regsFloat,cur,bcode,cline,OP_JE_1);
        } else
		if (args[0]=="jl")
        {
			cmdJmp(args,regs,regsFloat,cur,bcode,cline,OP_JL_1);
        } else
		if (args[0]=="jg")
        {
			cmdJmp(args,regs,regsFloat,cur,bcode,cline,OP_JG_1);
        } else
		if (args[0]=="jne")
        {
			cmdJmp(args,regs,regsFloat,cur,bcode,cline,OP_JNE_1);
        } else
        {
			//std::cout << args[0] << ":" << std::endl;
            error(cline,"Unknown command");
        }
    }
    source.close();

    ofstream out(outfile,ofstream::binary);
    out.write((char*)bcode,cur);
    out.close();

	printBcode(bcode,cur);

    return 0;
}