#include "parsecmd.h"

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
