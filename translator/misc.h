#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

std::string itoa(int num);
int atoi(std::string const &str);
void error(int line,std::string errMsg);
bool isNumber(const std::string &str);
bool isFloat(const std::string &str);

