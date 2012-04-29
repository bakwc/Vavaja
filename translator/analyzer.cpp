#include "analyzer.h"

//------------------------------------------------------------------------------------------
void Analyzer::load(const std::string fname)
{
	std::ifstream source(fname);
	std::string tmp;
	while (!source.eof())
	{
		getline(source,tmp);
		if (tmp.length()!=0)
			listing_.push_back(tmp);
	}
	source.close();
}

//------------------------------------------------------------------------------------------
void Analyzer::process()
{
	for (auto i=listing_.begin();i<listing_.end();i++)
	{
        Args args;
        split((*i),args);
        curLine_++;
		
		if (labels_->isLabel(args[0]))
		{
			labels_->addLabel(args[0],memory_->getCurrent());
		} else
        if (args[0]=="pass")
        {
			memory_->putByte(OP_PASS);
        }
        else
        if (args[0]=="mov")
        {
			parseMov(args);
        }
        else
        if (args[0]=="int")
        {
            if (args.size()!=2) error(curLine_,"Syntax error"); else
            if (isNumber(args[1]))
            {
				memory_->putByte(OP_INT);
				memory_->putNum(args[1]);
            } else
                error(curLine_,"Syntax error");
        }
        else
        if (args[0]=="add")
        {
			parseTwo(args,OP_ADD_1);
        }
        else
        if (args[0]=="sub")
        {
			parseTwo(args,OP_SUB_1);
        } else
		if (args[0]=="mul")
		{
			parseOne(args,OP_MUL_1);
		} else
		if (args[0]=="div")
		{
			parseOne(args,OP_DIV_1);
		} else
		if (args[0]=="cmp")
		{
			parseTwo(args,OP_CMP_1);
		} else
        if (args[0]=="jmp")
        {
			parseJmp(args,OP_JMP_1);
        } else
        if (args[0]=="je")
        {
			parseJmp(args,OP_JE_1);
        } else
		if (args[0]=="jl")
        {
			parseJmp(args,OP_JL_1);
        } else
		if (args[0]=="jg")
        {
			parseJmp(args,OP_JG_1);
        } else
		if (args[0]=="jne")
        {
			parseJmp(args,OP_JNE_1);
        } else
        {
            error(curLine_,"Unknown command");
        }
	}
	memory_->print();
	labels_->setLabels();
}

//------------------------------------------------------------------------------------------
void Analyzer::parseMov(Args &args)
{
	if (args.size()!=3) error(curLine_,"Syntax error"); else
	if (isNumber(args[1]) && regs_->isReg(args[2]))
	{
		memory_->putByte(OP_MOV_1);
		memory_->putNum(args[1]);
		memory_->putReg(args[2]);
	} else
	if (isNumber(args[1]) && memory_->isMemory(args[2]))
	{
		if (isNumber(args[2]))
		{
			memory_->putByte(OP_MOV_2);
			memory_->putNum(args[1]);
			memory_->putNum(args[2]);
		} else
		if (regs_->isReg(args[2]))
		{
			memory_->putByte(OP_MOV_3);
			memory_->putNum(args[1]);
			memory_->putReg(args[1]);
		} else
		{
			error(curLine_,"Syntax error");
		}
	} else
	if (isFloat(args[1]) && regs_->isRegFloat(args[2]))
	{
		memory_->putByte(OP_MOV_4);
		memory_->putFloat(args[1]);
		memory_->putRegFloat(args[2]);
	}else
	if (isFloat(args[1]) && memory_->isMemory(args[2]))
	{
		if (isNumber(args[2]))
		{
			memory_->putByte(OP_MOV_5);
			memory_->putFloat(args[1]);
			memory_->putNum(args[2]);
		} else
		if (regs_->isReg(args[2]))
		{
			memory_->putByte(OP_MOV_6);
			memory_->putFloat(args[1]);
			memory_->putReg(args[2]);
		} else
		{
			error(curLine_,"Syntax error");
		}
	} else
	if (regs_->isReg(args[2]) && regs_->isReg(args[2]))
	{
		memory_->putByte(OP_MOV_7);
		memory_->putReg(args[1]);
		memory_->putReg(args[2]);
	} else
	if (regs_->isReg(args[1]) && memory_->isMemory(args[2]))
	{
		if (isNumber(args[2]))
		{
			memory_->putByte(OP_MOV_8);
			memory_->putReg(args[1]);
			memory_->putNum(args[2]);
		} else
		if (regs_->isReg(args[2]))
		{
			memory_->putByte(OP_MOV_9);
			memory_->putReg(args[1]);
			memory_->putReg(args[2]);
		} else
		{
			error(curLine_,"Syntax error");
		}
	} else
	if (regs_->isRegFloat(args[1]) && regs_->isRegFloat(args[2]))
	{
		memory_->putByte(OP_MOV_10);
		memory_->putRegFloat(args[1]);
		memory_->putRegFloat(args[2]);
	} else
	if (regs_->isRegFloat(args[1]) && memory_->isMemory(args[2]))
	{
		if (isNumber(args[2]))
		{
			memory_->putByte(OP_MOV_11);
			memory_->putReg(args[1]);
			memory_->putNum(args[2]);
		} else
		if (regs_->isReg(args[2]))
		{
			memory_->putByte(OP_MOV_12);
			memory_->putReg(args[1]);
			memory_->putReg(args[2]);
		} else
		{
			error(curLine_,"Syntax error");
		}
	} else
	if (memory_->isMemory(args[1]))
	{
		if (isNumber(args[1]))
		{
			if (regs_->isReg(args[2]))
			{
				memory_->putByte(OP_MOV_13);
				memory_->putNum(args[1]);
				memory_->putReg(args[2]);
			} else
			if (regs_->isRegFloat(args[2]))
			{
				memory_->putByte(OP_MOV_14);
				memory_->putNum(args[1]);
				memory_->putRegFloat(args[2]);
			} else
			{
				error(curLine_,"Syntax error");
			}
		} else
		if (regs_->isReg(args[1]))
		{
			if (regs_->isReg(args[2]))
			{
				memory_->putByte(OP_MOV_15);
				memory_->putReg(args[1]);
				memory_->putReg(args[2]);
			} else
			if (regs_->isRegFloat(args[2]))
			{
				memory_->putByte(OP_MOV_16);
				memory_->putReg(args[1]);
				memory_->putRegFloat(args[2]);
			} else
			{
			error(curLine_,"Syntax error");
			}
		} else
		{
			error(curLine_,"Syntax error");
		}
	}
}

//------------------------------------------------------------------------------------------
void Analyzer::parseTwo(Args &args,const OpType startCode)
{
	if (args.size()!=3) error(curLine_,"Syntax error"); else
	if (regs_->isReg(args[2]))
	{
		if (regs_->isReg(args[1]))
		{
			memory_->putByte(startCode+1);
			memory_->putReg(args[1]);
			memory_->putReg(args[2]);
		} else
		if (isNumber(args[1]))
		{
			memory_->putByte(startCode);
			memory_->putNum(args[1]);
			memory_->putReg(args[2]);
		}else error(curLine_,"Syntax error");
	} else
	if (regs_->isRegFloat(args[2]))
	{
		if (regs_->isRegFloat(args[1]))
		{
			memory_->putByte(startCode+3);
			memory_->putRegFloat(args[1]);
			memory_->putRegFloat(args[2]);
		} else
		if (isFloat(args[1]))
		{
			memory_->putByte(startCode+2);
			memory_->putFloat(args[1]);
			memory_->putRegFloat(args[2]);
		}else error(curLine_,"Syntax error");

	} else error(curLine_,"Syntax error");
}

//------------------------------------------------------------------------------------------
void Analyzer::parseOne(Args &args,const OpType startCode)
{
	if (args.size()!=2) error(curLine_,"Syntax error"); else
	if (isNumber(args[1]))
	{
		memory_->putByte(startCode);
		memory_->putNum(args[1]);
	} else
	if (regs_->isReg(args[1]))
	{
		memory_->putByte(startCode+1);
		memory_->putReg(args[1]);
	} else
	if (isFloat(args[1]))
	{
		memory_->putByte(startCode+2);
		memory_->putFloat(args[1]);
	} else
	if (regs_->isRegFloat(args[1]))
	{
		memory_->putByte(startCode+3);
		memory_->putRegFloat(args[1]);
	} else error(curLine_,"Syntax error");
}

//------------------------------------------------------------------------------------------
void Analyzer::parseJmp(Args &args,const OpType startCode)
{
	if (args.size()!=2) error(curLine_,"Syntax error"); else
		if (memory_->isMemory(args[1]))
		{
			if (isNumber(args[1]))
			{
				memory_->putByte(startCode);
				memory_->putNum(args[1]);
			} else
			if (regs_->isReg(args[1]))
			{
				memory_->putByte(startCode+1);
				memory_->putReg(args[1]);
			} else
			error(curLine_,"Syntax error");
		} else 
		{
			labels_->addAddr(memory_->getCurrent()+1,args[1]);
			memory_->putByte(startCode);
			memory_->putByte(0);
			memory_->putByte(0);
		}
}
