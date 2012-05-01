#include "misc.h"

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

//------------------------------------------------------------------------------------------
float atof(std::string const &str)  // строку в дробное число
{
	std::istringstream stream(str);
	float number = 0;
	stream >> number;
	if (stream.fail()) throw 1;
	return number;
}

//------------------------------------------------------------------------------------------
void error(int line,std::string errMsg)
{
    std::cout << "\nERROR! Line " << line << ": " << errMsg << ";\n";
    exit(19);
}
//------------------------------------------------------------------------------------------
bool isNumber(const std::string &str)
{
    unsigned numcnt=0;
    if (str[0]=='-') numcnt++;
    for (auto c=str.begin();c<str.end();c++)
    {
        if (((*c)>='0') && ((*c)<='9'))
        {
            numcnt++;
        }
    }
    return (str.length()==numcnt);
}
//------------------------------------------------------------------------------------------
bool isFloat(const std::string &str)
{
    unsigned numcnt=0;
    bool isDot=false;
    if (str[0]=='-') numcnt++;
    for (auto c=str.begin();c<str.end();c++)
    {
        if (((*c)>='0') && ((*c)<='9'))
        {
            numcnt++;
        }
        if ((*c)=='.')
        {
            numcnt++;
            isDot=true;
        }
    }
    return ((str.length()==numcnt) && isDot);
}

//------------------------------------------------------------------------------------------
void split(const std::string &str,Args &args,const char letter)
{
    int n=str.find(letter);
    std::string tmp,str2=str;
    while (n>=0)
    {
        tmp=str2.substr(0,n);
        str2.erase(0,n+1);
        args.push_back(tmp);
        n=str2.find(letter);
    }
    args.push_back(str2);
}
