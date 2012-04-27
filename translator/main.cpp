#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <conio.h>

using namespace std;

typedef map<string,unsigned> Regs;
typedef vector<string> Args;

//------------------------------------------------------------------------------------------
std::string itoa(int num)	// число в строку
{
	std::stringstream out;
	out << num;
	return out.str();
}
//------------------------------------------------------------------------------------------
int atoi(std::string const &str)  // строку в число
{
	std::istringstream stream(str);
	int number = 0;
	stream >> number;
	if (stream.fail()) throw 1;
	return number;
}

void error(int line,string errMsg)
{
    cout << "\nERROR! Line " << line << ": " << errMsg << ";\n";
    exit(19);
}

bool isNumber(const string &str)
{
    unsigned numcnt=0;
    if (str[0]=='-') numcnt++;
    for (auto c:str)
    {
        if ((c>='0') && (c<='9'))
        {
            numcnt++;
        }
    }
    return (str.length()==numcnt);
}

bool isRegister(string &str, Regs &regs)
{
    return regs.find(str)!=regs.end();
}

bool isMemory(string &str)
{
    if (str[0]=='%')
    {
        str.erase(0,1);
        return true;
    }
    return false;
}

bool isFloat(const string &str)
{
    unsigned numcnt=0;
    bool isDot=false;
    if (str[0]=='-') numcnt++;
    for (auto c:str)
    {
        if ((c>='0') && (c<='9'))
        {
            numcnt++;
        }
        if (c=='.')
        {
            numcnt++;
            isDot=true;
        }
    }
    return ((str.length()==numcnt) && isDot);
}

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

void initRegsFloat(Regs &regs)
{
    regs["eax"]=0;
    regs["ebx"]=1;
    regs["ecx"]=2;
    regs["edx"]=3;
    regs["eex"]=4;
    regs["esp"]=5;
}
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

void putByte(const unsigned char byte,unsigned char *addr,int &cur)
{
    *(addr+cur)=byte;
    cur++;
}

void putNum(string num,unsigned char *addr,int &cur)
{
    *((short*)(addr+cur))=atoi(num);
    cur+=2;
}

void putFloat(string num,unsigned char *addr,int &cur)
{
    *((float*)(addr+cur))=atoi(num);
    cur+=4;
}

void putReg(string reg,Regs &regs,unsigned char *addr,int &cur)
{
    *(addr+cur)=regs[reg];
    cur++;
}

int main(int arc, char **argv)
{
    unsigned char bcode[5000];
    Regs regs,regsFloat; // Список целых и дробных регистров и их номера
    int cur=0,cline=0;
    string infile,outfile;
    infile="program.asm";
    outfile="program.ve";
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
            putByte(19,bcode,cur);
        }
        else
        if (args[0]=="mov")
        {
            if (args.size()!=3) error(cline,"Syntax error"); else
            if (isNumber(args[1]) && isRegister(args[2],regs))
            {
                putByte(1,bcode,cur);
                putNum(args[1],bcode,cur);
                putReg(args[2],regs,bcode,cur);
            } else
            if (isNumber(args[1]) && isMemory(args[2]))
            {
                if (isNumber(args[2]))
                {
                    putByte(2,bcode,cur);
                    putNum(args[1],bcode,cur);
                    putNum(args[2],bcode,cur);
                } else
                if (isRegister(args[2],regs))
                {
                    putByte(3,bcode,cur);
                    putNum(args[1],bcode,cur);
                    putReg(args[2],regs,bcode,cur);
                } else
                {
                    error(cline,"Syntax error");
                }
            } else
            if (isFloat(args[1]) && isRegister(args[2],regsFloat))
            {
                putByte(4,bcode,cur);
                putFloat(args[1],bcode,cur);
                putReg(args[2],regsFloat,bcode,cur);
            }else
            if (isFloat(args[1]) && isMemory(args[2]))
            {
                if (isNumber(args[2]))
                {
                    putByte(5,bcode,cur);
                    putFloat(args[1],bcode,cur);
                    putNum(args[2],bcode,cur);
                } else
                if (isRegister(args[2],regs))
                {
                    putByte(6,bcode,cur);
                    putFloat(args[1],bcode,cur);
                    putReg(args[2],regs,bcode,cur);
                } else
                {
                    error(cline,"Syntax error");
                }
            } else
            if (isRegister(args[1],regs) && isRegister(args[2],regs))
            {
                putByte(7,bcode,cur);
                putReg(args[1],regs,bcode,cur);
                putReg(args[2],regs,bcode,cur);
            } else
            if (isRegister(args[1],regs) && isMemory(args[2]))
            {
                if (isNumber(args[2]))
                {
                    putByte(8,bcode,cur);
                    putReg(args[1],regs,bcode,cur);
                    putNum(args[2],bcode,cur);
                } else
                if (isRegister(args[2],regs))
                {
                    putByte(9,bcode,cur);
                    putReg(args[1],regs,bcode,cur);
                    putReg(args[2],regs,bcode,cur);
                } else
                {
                    error(cline,"Syntax error");
                }
            } else
            if (isRegister(args[1],regsFloat) && isRegister(args[2],regsFloat))
            {
                putByte(10,bcode,cur);
                putReg(args[1],regsFloat,bcode,cur);
                putReg(args[2],regsFloat,bcode,cur);
            } else
            if (isRegister(args[1],regsFloat) && isMemory(args[2]))
            {
                if (isNumber(args[2]))
                {
                    putByte(11,bcode,cur);
                    putReg(args[1],regsFloat,bcode,cur);
                    putNum(args[2],bcode,cur);
                } else
                if (isRegister(args[2],regs))
                {
                    putByte(12,bcode,cur);
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
                        putByte(13,bcode,cur);
                        putNum(args[1],bcode,cur);
                        putReg(args[2],regs,bcode,cur);
                    } else
                    if (isRegister(args[2],regsFloat))
                    {
                        putByte(14,bcode,cur);
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
                        putByte(15,bcode,cur);
                        putReg(args[1],regs,bcode,cur);
                        putReg(args[2],regs,bcode,cur);
                    } else
                    if (isRegister(args[2],regsFloat))
                    {
                        putByte(16,bcode,cur);
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
        else
        if (args[0]=="int")
        {
            if (args.size()!=2) error(cline,"Syntax error"); else
            if (isNumber(args[1]))
            {
                putByte(20,bcode,cur);
                putNum(args[1],bcode,cur);
            } else
                error(cline,"Syntax error");
        }
        else
        if (args[0]=="add")
        {
            if (args.size()!=3) error(cline,"Syntax error"); else
            if (isRegister(args[2],regs))
            {
                if (isRegister(args[1],regs))
                {
                    putByte(23,bcode,cur);
                    putReg(args[1],regs,bcode,cur);
                    putReg(args[2],regs,bcode,cur);
                } else
                if (isNumber(args[1]))
                {
                    putByte(22,bcode,cur);
                    putNum(args[1],bcode,cur);
                    putReg(args[2],regs,bcode,cur);
                }else error(cline,"Syntax error");
            } else
            if (isRegister(args[2],regsFloat))
            {
                if (isRegister(args[1],regsFloat))
                {
                    putByte(25,bcode,cur);
                    putReg(args[1],regsFloat,bcode,cur);
                    putReg(args[2],regsFloat,bcode,cur);
                } else
                if (isFloat(args[1]))
                {
                    putByte(24,bcode,cur);
                    putFloat(args[1],bcode,cur);
                    putReg(args[2],regs,bcode,cur);
                }else error(cline,"Syntax error");

            } else error(cline,"Syntax error");
        }
        else
        if (args[0]=="sub")
        {
            if (args.size()!=3) error(cline,"Syntax error"); else
            if (isRegister(args[2],regs))
            {
                if (isRegister(args[1],regs))
                {
                    putByte(27,bcode,cur);
                    putReg(args[1],regs,bcode,cur);
                    putReg(args[2],regs,bcode,cur);
                } else
                if (isNumber(args[1]))
                {
                    putByte(26,bcode,cur);
                    putNum(args[1],bcode,cur);
                    putReg(args[2],regs,bcode,cur);
                }else error(cline,"Syntax error");
            } else
            if (isRegister(args[2],regsFloat))
            {
                if (isRegister(args[1],regsFloat))
                {
                    putByte(29,bcode,cur);
                    putReg(args[1],regsFloat,bcode,cur);
                    putReg(args[2],regsFloat,bcode,cur);
                } else
                if (isFloat(args[1]))
                {
                    putByte(28,bcode,cur);
                    putFloat(args[1],bcode,cur);
                    putReg(args[2],regs,bcode,cur);
                }else error(cline,"Syntax error");

            } else error(cline,"Syntax error");
        }
        else
        {
            error(cline,"Unknown command");
        }
    }
    source.close();

    ofstream out(outfile,ofstream::binary);
    out.write((char*)bcode,cur);
    out.close();

    for (int i=0;i<cur;i++)
    {
        int j=(*(char*)(bcode+i));
        cout << j << "\n";
    }
    _getch();

    return 0;
}
