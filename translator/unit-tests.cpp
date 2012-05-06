#include <iostream>
#include <string>
#include <fstream>
#include "misc.h"
#include "regs.h"
#include "memory.h"
#include "labels.h"
#include "analyzer.h"

//-------------------------------------------------------------------------
int cmpStrs(const std::string &str1,const std::string &str2)
{
	if (str1==str2)
	{
		std::cout << "OK\n";
		return 1;
	} else
	{
		std::cout << "FAIL\n";
		return 0;
	}
}

//-------------------------------------------------------------------------
int cmpInt(const int &num1,const int &num2)
{
	if (num1==num2)
	{
		std::cout << "OK\n";
		return 1;
	} else
	{
		std::cout << "FAIL\n";
		return 0;
	}
}

//-------------------------------------------------------------------------
int cmpFloat(const float &num1,const float &num2)
{
	if (num1==num2)
	{
		std::cout << "OK\n";
		return 1;
	} else
	{
		std::cout << "FAIL\n";
		return 0;
	}
}

//-------------------------------------------------------------------------
int cmpBool(const bool &arg1,const bool &arg2)
{
	if (arg1==arg2)
	{
		std::cout << "OK\n";
		return 1;
	} else
	{
		std::cout << "FAIL\n";
		return 0;
	}
}

//-------------------------------------------------------------------------
int testItoa()
{
	int count=0;
	std::cout << "Testing itoa: \n";
	std::cout << " Test 1:\t";
	count+=cmpStrs(itoa(10),"10");
	std::cout << " Test 2:\t";
	count+=cmpStrs(itoa(991726),"991726");
	std::cout << " Test 3:\t";
	count+=cmpStrs(itoa(-87314),"-87314");	
	std::cout << " Test 4:\t";
	count+=cmpStrs(itoa(0),"0");
	std::cout << " Test 5:\t";
	count+=cmpStrs(itoa(-0),"0");	
	std::cout << "\n";
	return (count==5);
}

//-------------------------------------------------------------------------
int testAtoi()
{
	int count=0;
	std::cout << "Testing atoi: \n";
	std::cout << " Test 1:\t";
	count+=cmpInt(atoi("10"),10);
	std::cout << " Test 2:\t";
	count+=cmpInt(atoi("31266"),31266);
	std::cout << " Test 3:\t";
	count+=cmpInt(atoi("0"),0);
	std::cout << " Test 4:\t";
	count+=cmpInt(atoi("-0"),0);
	std::cout << " Test 5:\t";
	count+=cmpInt(atoi("-9166732"),-9166732);
	std::cout << "\n";
	return (count==5);
}

//-------------------------------------------------------------------------
int testAtof()
{
	int count=0;
	std::cout << "Testing atof: \n";
	std::cout << " Test 1:\t";
	count+=cmpFloat(atof("10.5"),10.5);
	std::cout << " Test 2:\t";
	count+=cmpFloat(atof("31266.0"),31266.0);
	std::cout << " Test 3:\t";
	count+=cmpFloat(atof("0.3"),0.3);
	std::cout << " Test 4:\t";
	count+=cmpFloat(atof("-0.0"),0.0);
	std::cout << " Test 5:\t";
	count+=cmpFloat(atof("-9166732.3"),-9166732.3);
	std::cout << "\n";
	return (count==5);
}

//-------------------------------------------------------------------------
int testIsNumber()
{
	int count=0;
	std::cout << "Testing isNumber: \n";
	std::cout << " Test 1:\t";
	count+=cmpBool(isNumber("211"),true);
	std::cout << " Test 2:\t";
	count+=cmpBool(isNumber("-962"),true);
	std::cout << " Test 3:\t";
	count+=cmpBool(isNumber("0"),true);
	std::cout << " Test 4:\t";
	count+=cmpBool(isNumber("-0"),true);
	std::cout << " Test 5:\t";
	count+=cmpBool(isNumber("hello"),false);
	std::cout << " Test 6:\t";
	count+=cmpBool(isNumber("0 3 1"),false);
	std::cout << " Test 7:\t";
	count+=cmpBool(isNumber("12.5"),false);
	std::cout << " Test 8:\t";
	count+=cmpBool(isNumber("h0"),false);
	std::cout << " Test 9:\t";
	count+=cmpBool(isNumber("k4"),false);
	std::cout << "Test 10:\t";
	count+=cmpBool(isNumber("-32,4"),false);
	std::cout << "\n";
	return (count==10);
}

//-------------------------------------------------------------------------
int testIsFloat()
{
	int count=0;
	std::cout << "Testing isFloat: \n";
	std::cout << " Test 1:\t";
	count+=cmpBool(isFloat("211.0"),true);
	std::cout << " Test 2:\t";
	count+=cmpBool(isFloat("-962"),false);
	std::cout << " Test 3:\t";
	count+=cmpBool(isFloat("0"),false);
	std::cout << " Test 4:\t";
	count+=cmpBool(isFloat("-0.0"),true);
	std::cout << " Test 5:\t";
	count+=cmpBool(isFloat("hello"),false);
	std::cout << " Test 6:\t";
	count+=cmpBool(isFloat("0 3 1"),false);
	std::cout << " Test 7:\t";
	count+=cmpBool(isFloat("12.5"),true);
	std::cout << " Test 8:\t";
	count+=cmpBool(isFloat("-0.13"),true);
	std::cout << " Test 9:\t";
	count+=cmpBool(isFloat("k4"),false);
	std::cout << "Test 10:\t";
	count+=cmpBool(isFloat("-32,4"),false);
	std::cout << "\n";
	return (count==10);
}

//-------------------------------------------------------------------------
int testSplit()
{
	int count=0;
	Args args;
	std::cout << "Testing split: \n";
	
	std::cout << " Test 1:\t";
	args.clear();
	split("str1 str2 str3",args);
	count+=cmpInt(args.size(),3);
	
	std::cout << " Test 2:\t";
	args.clear();
	split("hello:world",args,':');
	count+=cmpInt(args.size(),2);
	
	std::cout << " Test 3:\t";
	args.clear();
	split("asd!wowo!err op!kva!doich",args,'!');
	count+=cmpBool(args[3]=="kva",true);
	
	std::cout << " Test 4:\t";
	args.clear();
	split("asd!wowo!err op!kva!doich",args,'!');
	count+=cmpBool(args[4]=="doich",true);
	
	std::cout << " Test 5:\t";
	args.clear();
	split("asd!wowo!err op!kva!doich",args,'!');
	count+=cmpBool(args[2]=="doich",false);

	return (count==5);
}

//-------------------------------------------------------------------------
int testMisc()
{
	int count=0;
	count+=testItoa();
	count+=testAtoi();
	count+=testAtof();
	count+=testIsNumber();
	count+=testIsFloat();
	count+=testSplit();
	std::cout << "\n misc tested:\t";
	cmpBool((count==6),true);
	std::cout << "\n";
	return (count==6);
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
int testIsReg()
{
	int count=0;
	std::cout << "Testing isReg: \n";
	Registers regs;
	std::cout << " Test 1:\t";
	count+=cmpBool(regs.isReg("ah"),true);
	std::cout << " Test 2:\t";
	count+=cmpBool(regs.isReg("sp"),true);
	std::cout << " Test 3:\t";
	count+=cmpBool(regs.isReg("gw"),false);
	std::cout << " Test 4:\t";
	count+=cmpBool(regs.isReg("eax"),false);
	std::cout << " Test 5:\t";
	count+=cmpBool(regs.isReg("eax"),false);
	std::cout << " Test 6:\t";
	count+=cmpBool(regs.isReg("ahe"),false);
	std::cout << "\n";
	return (count==6);
}

//-------------------------------------------------------------------------
int testIsRegFloat()
{
	int count=0;
	std::cout << "Testing IsRegFloat: \n";
	Registers regs;
	std::cout << " Test 1:\t";
	count+=cmpBool(regs.isRegFloat("ah"),false);
	std::cout << " Test 2:\t";
	count+=cmpBool(regs.isRegFloat("sp"),false);
	std::cout << " Test 3:\t";
	count+=cmpBool(regs.isRegFloat("esp"),true);
	std::cout << " Test 4:\t";
	count+=cmpBool(regs.isRegFloat("eax"),true);
	std::cout << " Test 5:\t";
	count+=cmpBool(regs.isRegFloat("edx"),true);
	std::cout << " Test 6:\t";
	count+=cmpBool(regs.isRegFloat("ahe"),false);
	std::cout << "\n";
	return (count==6);
}

//-------------------------------------------------------------------------
int testGetReg()
{
	int count=0;
	std::cout << "Testing GetReg: \n";
	Registers regs;
	std::cout << " Test 1:\t";
	count+=cmpInt(regs.getReg("ah"),0);
	std::cout << " Test 2:\t";
	count+=cmpInt(regs.getReg("eh"),4);
	std::cout << " Test 3:\t";
	count+=cmpInt(regs.getReg("pc"),6);
	std::cout << "\n";
	return (count==3);
}

//-------------------------------------------------------------------------
int testGetRegFloat()
{
	int count=0;
	std::cout << "Testing GetRegFloat: \n";
	Registers regs;
	std::cout << " Test 1:\t";
	count+=cmpInt(regs.getRegFloat("eax"),0);
	std::cout << " Test 2:\t";
	count+=cmpInt(regs.getRegFloat("eex"),4);
	std::cout << " Test 3:\t";
	count+=cmpInt(regs.getRegFloat("esp"),5);
	std::cout << "\n";
	return (count==3);
}

//-------------------------------------------------------------------------
int testRegs()
{
	int count=0;
	count+=testIsReg();
	count+=testIsRegFloat();
	count+=testGetReg();
	count+=testGetRegFloat();
	std::cout << "\n regs tested:\t";
	cmpBool((count==4),true);
	std::cout << "\n";
	return (count==4);
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
int testIsMemory()
{
	int count=0;
	std::cout << "Testing isMemory: \n";
	Registers regs;
	Memory mem(&regs);
	std::string tmp;
	tmp="%235";
	std::cout << " Test 1:\t";
	count+=cmpBool(mem.isMemory(tmp),true);
	std::cout << " Test 2:\t";
	count+=cmpBool(tmp=="235",true);
	tmp="%label";
	std::cout << " Test 3:\t";
	count+=cmpBool(mem.isMemory(tmp),true);
	std::cout << " Test 4:\t";
	count+=cmpBool(tmp=="label",true);
	tmp="some%text";
	std::cout << " Test 5:\t";
	count+=cmpBool(mem.isMemory(tmp),false);
	tmp="%";
	std::cout << " Test 6:\t";
	count+=cmpBool(mem.isMemory(tmp),false);
	std::cout << "\n";
	return (count==6);
}

//-------------------------------------------------------------------------
int testMemoryComplex()
{
	int count=0;
	std::cout << "Overall memory tests: \n";
	{
		int count2=0;
		Registers regs;
		Memory mem(&regs);
		unsigned char memory[50];
		std::cout << " Test 1:\t";
		mem.putByte(3);
		mem.putByte(50);
		mem.putByte(138);
		mem.putByte(8);
		mem.save("memory.tst");
		std::ifstream in("memory.tst",std::ios::binary);
		in.seekg (0, std::ios::end);
		int length = in.tellg();
		in.seekg (0, std::ios::beg);
		in.read((char*)memory,length);
		in.close();
		if (length==4) count2++;
		if (memory[0]==3) count2++;
		if (memory[1]==50) count2++;
		if (memory[2]==138) count2++;
		if (memory[3]==8) count2++;
		count+=cmpInt(count2,5);
	}
	
	{
		int count2=0;
		Registers regs;
		Memory mem(&regs);
		unsigned char memory[50];
		std::cout << " Test 2:\t";
		mem.putNum("25");
		mem.putNum("-115");
		mem.save("memory.tst");
		std::ifstream in("memory.tst",std::ios::binary);
		in.seekg (0, std::ios::end);
		int length = in.tellg();
		in.seekg (0, std::ios::beg);
		in.read((char*)memory,length);
		in.close();
		if (length==4) count2++;
		if (*((short*)memory)==25) count2++;
		if (*((short*)(memory+2))==-115) count2++;
		count+=cmpInt(count2,3);
	}
	
	{
		int count2=0;
		Registers regs;
		Memory mem(&regs);
		unsigned char memory[50];
		std::cout << " Test 3:\t";
		mem.putFloat("25.5");
		mem.putFloat("-161.5");
		mem.putFloat("-0.0");
		mem.save("memory.tst");
		std::ifstream in("memory.tst",std::ios::binary);
		in.seekg (0, std::ios::end);
		int length = in.tellg();
		in.seekg (0, std::ios::beg);
		in.read((char*)memory,length);
		in.close();
		if (length==12) count2++;
		if ((*((float*)memory))==25.5) count2++;
		if ((*((float*)(memory+4)))==(-161.5)) count2++;
		if ((*((float*)(memory+8)))==0.0) count2++;
		count+=cmpInt(count2,4);
	}

	{
		int count2=0;
		Registers regs;
		Memory mem(&regs);
		unsigned char memory[50];
		std::cout << " Test 4:\t";
		mem.putReg("ah");
		mem.putRegFloat("eax");
		mem.putReg("ch");
		mem.putRegFloat("esp");
		mem.save("memory.tst");
		std::ifstream in("memory.tst",std::ios::binary);
		in.seekg (0, std::ios::end);
		int length = in.tellg();
		in.seekg (0, std::ios::beg);
		in.read((char*)memory,length);
		in.close();
		if (length==4) count2++;
		if (memory[0]==0) count2++;
		if (memory[1]==0) count2++;
		if (memory[2]==2) count2++;
		if (memory[3]==5) count2++;
		count+=cmpInt(count2,5);
	}
	
	{
		int count2=0;
		Registers regs;
		Memory mem(&regs);
		unsigned char memory[50];
		std::cout << " Test 5:\t";
		mem.putNum("25");
		mem.putNum("-115");
		mem.putTwoBytes(0,21);
		mem.putTwoBytes(2,-34);
		mem.save("memory.tst");
		std::ifstream in("memory.tst",std::ios::binary);
		in.seekg (0, std::ios::end);
		int length = in.tellg();
		in.seekg (0, std::ios::beg);
		in.read((char*)memory,length);
		in.close();
		if (length==4) count2++;
		if (*((short*)memory)==21) count2++;
		if (*((short*)(memory+2))==-34) count2++;
		count+=cmpInt(count2,3);
	}
	
	std::cout << "\n";
	return (count==5);
}

//-------------------------------------------------------------------------
int testMemory()
{
	int count=0;
	count+=testIsMemory();
	count+=testMemoryComplex();
	std::cout << "\n memory tested:\t";
	cmpBool((count==2),true);
	std::cout << "\n";
	return (count==2);
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
int testIsLabel()
{
	int count=0;
	std::cout << "Testing IsLabel: \n";
	Registers regs;
	Memory mem(&regs);
	Label lbl(&mem);
	std::cout << " Test 1:\t";
	count+=cmpBool(lbl.isLabel("somelbl:"),true);
	std::cout << " Test 2:\t";
	count+=cmpBool(lbl.isLabel("label"),false);
	std::cout << " Test 3:\t";
	count+=cmpBool(lbl.isLabel(":"),false);

	std::cout << "\n";
	return (count==3);
}

//-------------------------------------------------------------------------
int testLabelComplex()
{
	int count=0,count2=0;
	std::cout << "Overall label tests: \n";
	Registers regs;
	Memory mem(&regs);
	Label lbl(&mem);
	unsigned char memory[50];
	
	mem.putNum("-1");
	mem.putNum("-1");
	mem.putNum("-1");
	mem.putNum("-1");
	
	std::cout << " Test 1:\t";
	lbl.addLabel("label1:",2);
	lbl.addLabel("smt:",6);
	lbl.addAddr(0,"smt");
	lbl.addAddr(4,"label1");
	lbl.setLabels();
	
	mem.save("memory.tst");
	std::ifstream in("memory.tst",std::ios::binary);
	in.seekg (0, std::ios::end);
	int length = in.tellg();
	in.seekg (0, std::ios::beg);
	in.read((char*)memory,length);
	in.close();

	if (*((short*)memory)==6) count2++;
	if (*((short*)(memory+4))==2) count2++;
	count+=cmpInt(count2,2);

	std::cout << "\n";
	return (count==1);
}

//-------------------------------------------------------------------------
int testLabels()
{
	int count=0;
	count+=testIsLabel();
	count+=testLabelComplex();
	
	std::cout << "\n labels tested:\t";
	cmpBool((count==2),true);
	std::cout << "\n";
	return (count==2);
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
int testAnalyzer()
{
	
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
int main()
{
	int count=0;
	count+=testMisc();
	count+=testRegs();
	count+=testMemory();
	count+=testLabels();
	std::cout << "\n Result:\t";
	cmpBool((count==4),true);
	std::cout << "\n";
	return 0;
}
