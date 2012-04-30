#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>

typedef std::vector<std::string> Args;

std::string itoa(int num);					// Число в строку
int atoi(std::string const &str);			// Строку в число
void error(int line,std::string errMsg);	// Вывод сообщения об ошибке
bool isNumber(const std::string &str);		// Проверка, является ли целым числом
bool isFloat(const std::string &str);		// Проверка, является ли дробным числом
void split(std::string &str,Args &args,const char letter=' ');
											// Функция, разбивающая строку на части
