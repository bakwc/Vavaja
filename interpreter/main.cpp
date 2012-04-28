#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "../params/defines.h"

using namespace std;

void interrupt(short intId,unsigned char *memory,short *regs, float *regsFloat)
{
    //cout << "INT " << intId << "\n";
    switch (intId)
    {
        case INT_EXIT:
        exit(0);
        break;
        case INT_OUTPUT_INT:
        cout << regs[0] << endl;
        break;
        case INT_OUPUT_FLOAT:
        cout << regsFloat[0] << endl;
        break;
        case  INT_INPUT_INT:
        cin >> regs[0];
        break;
        case INT_INTPUT_FLOAT:
        cin >> regsFloat[0];
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
        cout << (int)memory[i] << "\n";
*/
    while (true)
    {
        //cout << "Cmd: " << (int)memory[pc] << "\n";
        switch(memory[pc])
        {
            case OP_PASS:
            cout << "PASS\n";
            break;
            case OP_INT:
            {
                short intId=*((short*)(memory+pc+1));
                interrupt(intId,memory,regs,regsFloat);
                pc+=2;
            } break;

            case OP_MOV_1:
            {
                short num=*((short*)(memory+pc+1));
                size_t reg=*(memory+pc+3);
                regs[reg]=num;
                pc+=3;
            } break;
            case OP_MOV_2:
            {
                short num=*((short*)(memory+pc+1));
                short mem=*((short*)(memory+pc+3));
                *((short*)memory+mem)=num;
                pc+=4;
            } break;
            case OP_MOV_3:
            {
                short num=*((short*)(memory+pc+1));
                size_t reg=*(memory+pc+3);
                short mem=regs[reg];
                *((short*)memory+mem)=num;
                pc+=3;
            } break;

            case OP_MOV_7:
            {
                size_t reg1=*(memory+pc+1);
                size_t reg2=*(memory+pc+2);
                regs[reg2]=regs[reg1];
                pc+=2;
            } break;

            case OP_MOV_8:
            {
                size_t reg=*(memory+pc+1);
                short mem=*((short*)(memory+pc+2));
                *((short*)memory+mem)=regs[reg];
                pc+=3;
            } break;

            case OP_MOV_9:
            {
                size_t reg1=*(memory+pc+1);
                size_t reg2=*(memory+pc+2);
                short mem=regs[reg2];
                *((short*)memory+mem)=regs[reg1];
                pc+=2;
            } break;

            case OP_MOV_13:
            {
                short mem=*((short*)(memory+pc+1));
                size_t reg=*(memory+pc+3);
                regs[reg]=*((short*)memory+mem);
                pc+=3;
            } break;
            case OP_MOV_15:
            {
                size_t memreg=*(memory+pc+1);
                size_t reg=*(memory+pc+2);
                short mem=regs[memreg];
                regs[reg]=*((short*)memory+mem);
                pc+=2;
            } break;

            case OP_ADD_1:
            {
                short num=*((short*)(memory+pc+1));
                size_t reg=*(memory+pc+3);
                regs[reg]+=num;
                pc+=3;
            } break;
            case OP_ADD_2:
            {
                size_t reg1=*(memory+pc+1);
                size_t reg2=*(memory+pc+2);
                regs[reg2]+=regs[reg1];
                pc+=2;
            } break;
            case OP_SUB_1:
            {
                short num=*((short*)(memory+pc+1));
                size_t reg=*(memory+pc+3);
                regs[reg]-=num;
                pc+=3;
            } break;
            case OP_SUB_2:
            {
                size_t reg1=*(memory+pc+1);
                size_t reg2=*(memory+pc+2);
                regs[reg2]-=regs[reg1];
                pc+=2;
            } break;
			case OP_MUL_1:
            {
				short num=*((short*)(memory+pc+1));
                regs[0]*=num;
                pc+=2;
            } break;
			case OP_MUL_2:
            {
				size_t reg1=*(memory+pc+1);
                regs[0]*=regs[reg1];
                pc+=1;
            } break;
			case OP_DIV_1:
            {
				short num=*((short*)(memory+pc+1));
				regs[4]=regs[0]%num;
                regs[0]/=num;
                pc+=2;
            } break;
			case OP_DIV_2:
            {
				size_t reg1=*(memory+pc+1);
				regs[4]=regs[0]%regs[reg1];
                regs[0]/=regs[reg1];
                pc+=1;
            } break;
			case OP_CMP_1:
            {
                short num=*((short*)(memory+pc+1));
                size_t reg=*(memory+pc+3);
				if (num==regs[reg]) regs[4]=0;
				else if (num>regs[reg]) regs[4]=1;
				else regs[4]=-1;
                pc+=3;
            } break;
            case OP_CMP_2:
            {
                size_t reg1=*(memory+pc+1);
                size_t reg2=*(memory+pc+2);
				if (regs[reg1]==regs[reg2]) regs[4]=0;
				else if (regs[reg1]>regs[reg2]) regs[4]=1;
				else regs[4]=-1;
                pc+=2;
            } break;
			
			case OP_JMP_1:
            {
                short adr=*((short*)(memory+pc+1));
                pc=adr-1;
            } break;
			case OP_JE_1:
            {
                short adr=*((short*)(memory+pc+1));
                if (regs[4]==0) pc=adr-1;
				else pc+=2;
            } break;
			case OP_JL_1:
            {
                short adr=*((short*)(memory+pc+1));
                if (regs[4]==-1) pc=adr-1;
				else pc+=2;
            } break;
			case OP_JG_1:
            {
                short adr=*((short*)(memory+pc+1));
                if (regs[4]==1) pc=adr-1;
				else pc+=2;
            } break;
			case OP_JNE_1:
            {
                short adr=*((short*)(memory+pc+1));
                if (regs[4]!=0) pc=adr-1;
				else pc+=2;
            } break;			
            default:
            cout << "unknown cmd:\nPC=" << pc << "\n CODE=" << (int)*(memory+pc);
            exit(0);
        }
        pc++;
    }
    return 0;
}
