/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
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
