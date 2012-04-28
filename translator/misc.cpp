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
    for (auto c:str)
    {
        if ((c>='0') && (c<='9'))
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
