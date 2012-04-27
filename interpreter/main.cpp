#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

void interrupt(short intId,unsigned char *memory,short *regs, float *regsFloat)
{
    //cout << "INT " << intId << "\n";
    switch (intId)
    {
        case 10:
        exit(0);
        break;
        case 11:
        cout << regs[0] << endl;
        break;
        case 12:
        cout << regsFloat[0] << endl;
        break;
        case 13:
        cin >> regs[0];
        break;
        case 14:
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

    ifstream in("program.ve",ios::binary);
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
            case 19:
            cout << "PASS\n";
            break;
            case 20:
            {
                short intId=*((short*)(memory+pc+1));
                interrupt(intId,memory,regs,regsFloat);
                pc+=2;
            } break;

            case 1:
            {
                short num=*((short*)(memory+pc+1));
                size_t reg=*(memory+pc+3);
                regs[reg]=num;
                pc+=3;
            } break;
            case 2:
            {
                short num=*((short*)(memory+pc+1));
                short mem=*((short*)(memory+pc+3));
                *((short*)memory+mem)=num;
                pc+=4;
            } break;
            case 3:
            {
                short num=*((short*)(memory+pc+1));
                size_t reg=*(memory+pc+3);
                short mem=regs[reg];
                *((short*)memory+mem)=num;
                pc+=3;
            } break;

            case 7:
            {
                size_t reg1=*(memory+pc+1);
                size_t reg2=*(memory+pc+2);
                regs[reg2]=regs[reg1];
                pc+=2;
            } break;

            case 8:
            {
                size_t reg=*(memory+pc+1);
                short mem=*((short*)(memory+pc+2));
                *((short*)memory+mem)=regs[reg];
                pc+=3;
            } break;

            case 9:
            {
                size_t reg1=*(memory+pc+1);
                size_t reg2=*(memory+pc+2);
                short mem=regs[reg2];
                *((short*)memory+mem)=regs[reg1];
                pc+=2;
            } break;

            case 13:
            {
                short mem=*((short*)(memory+pc+1));
                size_t reg=*(memory+pc+3);
                regs[reg]=*((short*)memory+mem);
                pc+=3;
            } break;
            case 15:
            {
                size_t memreg=*(memory+pc+1);
                size_t reg=*(memory+pc+2);
                short mem=regs[memreg];
                regs[reg]=*((short*)memory+mem);
                pc+=2;
            } break;

            case 22:
            {
                short num=*((short*)(memory+pc+1));
                size_t reg=*(memory+pc+3);
                regs[reg]+=num;
                pc+=3;
            } break;
            case 23:
            {
                size_t reg1=*(memory+pc+1);
                size_t reg2=*(memory+pc+2);
                regs[reg2]+=regs[reg1];
                pc+=2;
            } break;
            case 26:
            {
                short num=*((short*)(memory+pc+1));
                size_t reg=*(memory+pc+3);
                regs[reg]-=num;
                pc+=3;
            } break;
            case 27:
            {
                size_t reg1=*(memory+pc+1);
                size_t reg2=*(memory+pc+2);
                regs[reg2]-=regs[reg1];
                pc+=2;
            } break;
            default:
            cout << "unknown cmd!\n";
            exit(0);
        }
        pc++;
    }
    return 0;
}
