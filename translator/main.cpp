#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>
#include "../params/defines.h"
#include "misc.h"
#include "regs.h"
#include "memory.h"
#include "parsecmd.h"

using namespace std;

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
        split(tmp,args);
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
