#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <stdlib.h>
#include "defines.h"

using namespace std;

//------------------------------------------------------------------------------------------
int atoi(std::string const &str)  // строку в число
{
	std::istringstream stream(str);
	int number = 0;
	stream >> number;
	if (stream.fail()) throw 1;
	return number;
}

void interrupt(short intId,unsigned char *memory,short *regs, float *regsFloat)
{
    //cout << "INT " << intId << "\n";
    switch (intId)
    {
        case INT_EXIT:
        exit(0);
        break;
        case INT_OUTPUT_INT:
        cout << regs[0];
        break;
        case INT_OUTPUT_FLOAT:
        cout << regsFloat[0];
        break;
        case  INT_INPUT_INT:
        cin >> regs[0];
        break;
        case INT_INPUT_FLOAT:
        cin >> regsFloat[0];
        break;
		case INT_OUTPUT_STR_N:
		{
			char *str;
			str=(char*)(memory+(size_t)regs[0]);
			std::cout << str << "\n";
		}
        break;
		case INT_OUTPUT_STR:
		{
			char *str;
			str=(char*)(memory+(size_t)regs[0]);
			std::cout << str;
		}
        break;
		case INT_DEBUG:
		{
			std::ofstream out("debug.txt");
			out << "AH: " << regs[0] << std::endl;
			out << "BH: " << regs[1] << std::endl;
			out << "CH: " << regs[2] << std::endl;
			out << "DH: " << regs[3] << std::endl;
			out << "EH: " << regs[4] << std::endl;
			out << "SP: " << regs[5] << std::endl;
			out << "PC: " << regs[6] << std::endl;
			out << "\nMemory:\n";
			for (int i=0;i<300;i++)
			{
				if ((i%16)==0)
					out << "\n" << i << ": ";
				out << (int)memory[i] << "\t";
			}
			out << std::endl;
			out.close();
		}
        break;
    }
}


int main()
{
    unsigned char memory[15000]; // общая память
    short regs[8];
    float regsFloat[8];
    short &pc=regs[6];
    short &sp=regs[5];
	
	std::map<std::string,unsigned char> syntax;
	
	std::ifstream source("../params/opcodes.cfg");
	while (!source.eof())
	{
		std::string tmp,key,value;
		int pos;
		getline(source,tmp);
		if (tmp.length()>0)
		{
			for (auto j=0;j<tmp.length();j++)
				if (tmp[j]==':')
					pos=j;
			key=tmp.substr(0,pos);
			value=tmp.substr(pos+1,999);
			syntax[key]=atoi(value);
		}
	}
	source.close();
	
	/*
	for (auto i=syntax.begin();i!=syntax.end();i++)
	{
		cout << i->first << ":" << (int)i->second << "\n";
	}
	*/
    ifstream in("../demo/program.ve",ios::binary);
    in.seekg (0, ios::end);
    int length = in.tellg();
    in.seekg (0, ios::beg);
    in.read((char*)memory,length);
    in.close();
    sp=length+1;    // стек начинается сразу после кода
    pc=0;           // - текущая команда

	/*
    for (int i=0;i<length;i++)
        cout << (int)memory[i] << " ";
	cout << std::endl;
	*/
	
    while (true)
    {
		//cout << "\n\nPC: " << pc << "\n";
        //cout << "Cmd: " << (int)memory[pc] << "\n\n";
		if (memory[pc]==syntax["pass"])
		{
			//cout << "PASS\n";
		} else
		if (memory[pc]==syntax["int:num"])
		{
			short intId=*((short*)(memory+pc+1));
			interrupt(intId,memory,regs,regsFloat);
			pc+=2;
		} else
		if (memory[pc]==syntax["mov:num:reg"])
		{
			short num=*((short*)(memory+pc+1));
			size_t reg=*(memory+pc+3);
			regs[reg]=num;
			pc+=3;
		} else
		if (memory[pc]==syntax["mov:num:mem"])
		{
			short num=*((short*)(memory+pc+1));
			short mem=*((short*)(memory+pc+3));
			*((short*)(memory+mem))=num;
			pc+=4;
		} else
		if (memory[pc]==syntax["mov:num:regmem"])
		{
			short num=*((short*)(memory+pc+1));
			size_t reg=*(memory+pc+3);
			short mem=regs[reg];
			*((short*)(memory+mem))=num;
			pc+=3;			
		} else
		if (memory[pc]==syntax["mov:reg:reg"])
		{
			size_t reg1=*(memory+pc+1);
			size_t reg2=*(memory+pc+2);
			regs[reg2]=regs[reg1];
			pc+=2;
		} else
		if (memory[pc]==syntax["mov:reg:mem"])
		{
			size_t reg=*(memory+pc+1);
			short mem=*((short*)(memory+pc+2));
			*((short*)(memory+mem))=regs[reg];
			pc+=3;
		} else
		if (memory[pc]==syntax["mov:reg:regmem"])
		{
			size_t reg1=*(memory+pc+1);
			size_t reg2=*(memory+pc+2);
			//std::cout << "reg: " << reg2 << "\n";
			short mem=regs[reg2];
			//std::cout << "addr: " << mem << "\n";
			*((short*)(memory+mem))=regs[reg1];
			pc+=2;
		} else
		if (memory[pc]==syntax["mov:mem:reg"])
		{
			short mem=*((short*)(memory+pc+1));
			size_t reg=*(memory+pc+3);
			regs[reg]=*((short*)(memory+mem));
			pc+=3;
		} else
		if (memory[pc]==syntax["mov:regmem:reg"])
		{
			size_t memreg=*(memory+pc+1);
			size_t reg=*(memory+pc+2);
			short mem=regs[memreg];
			regs[reg]=*((short*)(memory+mem));
			pc+=2;
		} else
		if (memory[pc]==syntax["add:num:reg"])
		{
			short num=*((short*)(memory+pc+1));
			size_t reg=*(memory+pc+3);
			regs[reg]+=num;
			pc+=3;
		} else
		if (memory[pc]==syntax["add:reg:reg"])
		{
			size_t reg1=*(memory+pc+1);
			size_t reg2=*(memory+pc+2);
			regs[reg2]+=regs[reg1];
			pc+=2;
		} else
		if (memory[pc]==syntax["sub:num:reg"])
		{
			short num=*((short*)(memory+pc+1));
			size_t reg=*(memory+pc+3);
			regs[reg]-=num;
			pc+=3;
		} else
		if (memory[pc]==syntax["sub:reg:reg"])
		{
			size_t reg1=*(memory+pc+1);
			size_t reg2=*(memory+pc+2);
			regs[reg2]-=regs[reg1];
			pc+=2;
		} else
		if (memory[pc]==syntax["mul:num"])
		{
			short num=*((short*)(memory+pc+1));
			regs[0]*=num;
			pc+=2;
		} else
		if (memory[pc]==syntax["mul:reg"])
		{
			size_t reg1=*(memory+pc+1);
			regs[0]*=regs[reg1];
			pc+=1;
		} else
		if (memory[pc]==syntax["div:num"])
		{
			short num=*((short*)(memory+pc+1));
			regs[4]=regs[0]%num;
			regs[0]/=num;
			pc+=2;
		} else
		if (memory[pc]==syntax["div:reg"])
		{
			size_t reg1=*(memory+pc+1);
			regs[4]=regs[0]%regs[reg1];
			regs[0]/=regs[reg1];
			pc+=1;
		} else
		if (memory[pc]==syntax["push:num"])
		{
			short num=*((short*)(memory+pc+1));
			*((short*)(memory+sp))=num;
			sp+=2;
			pc+=2;
		} else
		if (memory[pc]==syntax["push:reg"])
		{
			size_t reg1=*(memory+pc+1);
			short num=regs[reg1];
			*((short*)(memory+sp))=num;
			sp+=2;
			pc+=1;
		} else
		if (memory[pc]==syntax["pop:reg"])
		{
			sp-=2;
			size_t reg1=*(memory+pc+1);
			short num=*((short*)(memory+sp));
			regs[reg1]=num;
			pc+=1;
		} else
		if (memory[pc]==syntax["cmp:num:reg"])
		{
			short num=*((short*)(memory+pc+1));
			size_t reg=*(memory+pc+3);
			if (num==regs[reg]) regs[4]=0;
			else if (num>regs[reg]) regs[4]=1;
			else regs[4]=-1;
			pc+=3;
		} else
		if (memory[pc]==syntax["cmp:reg:reg"])
		{
			size_t reg1=*(memory+pc+1);
			size_t reg2=*(memory+pc+2);
			if (regs[reg1]==regs[reg2]) regs[4]=0;
			else if (regs[reg1]>regs[reg2]) regs[4]=1;
			else regs[4]=-1;
			pc+=2;
		} else
		if (memory[pc]==syntax["jmp:num"])
		{
			short adr=*((short*)(memory+pc+1));
            pc=adr-1;
        } else
		if (memory[pc]==syntax["call:num"])
		{
			short adr=*((short*)(memory+pc+1));
			short num=pc+3;
			//std::cout << "Return addr: " << num << "\n";
			*((short*)(memory+sp))=num;
			sp+=2;
            pc=adr-1;
        	} else
		if (memory[pc]==syntax["ret"])
		{
			sp-=2;
			short num=*((short*)(memory+sp));
			//std::cout << "Jmp to: " << num << "\n";
			pc=num-1;
		} else
		if (memory[pc]==syntax["je:num"])
		{
			short adr=*((short*)(memory+pc+1));
			if (regs[4]==0) pc=adr-1;
			else pc+=2;
		} else
		if (memory[pc]==syntax["jl:num"])
		{
			short adr=*((short*)(memory+pc+1));
			if (regs[4]==-1) pc=adr-1;
			else pc+=2;
		} else
		if (memory[pc]==syntax["jh:num"])
		{
			short adr=*((short*)(memory+pc+1));
			if (regs[4]==1) pc=adr-1;
			else pc+=2;
		} else
		if (memory[pc]==syntax["jne:num"])
		{
			short adr=*((short*)(memory+pc+1));
			if (regs[4]!=0) pc=adr-1;
			else pc+=2;
		} else
		if (memory[pc]==syntax["and:num:reg"])
		{
			short num=*((short*)(memory+pc+1));
			size_t reg=*(memory+pc+3);
			regs[reg]&=num;
			pc+=3;
		} else
		if (memory[pc]==syntax["and:reg:reg"])
		{
			size_t reg1=*(memory+pc+1);
			size_t reg2=*(memory+pc+2);
			regs[reg2]&=regs[reg1];
			pc+=2;
		} else
		if (memory[pc]==syntax["or:num:reg"])
		{
			short num=*((short*)(memory+pc+1));
			size_t reg=*(memory+pc+3);
			regs[reg]|=num;
			pc+=3;
		} else
		if (memory[pc]==syntax["or:reg:reg"])
		{
			size_t reg1=*(memory+pc+1);
			size_t reg2=*(memory+pc+2);
			regs[reg2]|=regs[reg1];
			pc+=2;
		} else
		if (memory[pc]==syntax["xor:num:reg"])
		{
			short num=*((short*)(memory+pc+1));
			size_t reg=*(memory+pc+3);
			regs[reg]^=num;
			pc+=3;
		} else
		if (memory[pc]==syntax["xor:reg:reg"])
		{
			size_t reg1=*(memory+pc+1);
			size_t reg2=*(memory+pc+2);
			regs[reg2]^=regs[reg1];
			pc+=2;
		} else
		if (memory[pc]==syntax["not:reg"])
		{
			size_t reg=*(memory+pc+1);
			regs[reg]= ~regs[reg];
			pc+=1;
		}		
		else
		{
			cout << "unknown cmd:\nPC=" << pc << "\n CODE=" << (int)*(memory+pc);
			exit(0);
		}		
        pc++;
    }
    return 0;
}
