#pragma once

#include <string>
#include <iostream>
#include "regs.h"
#include "misc.h"

bool isMemory(std::string &str);	// Проверка, является памятью (и удаление % из строки)
void putByte(const unsigned char byte,unsigned char *addr,int &cur);
									// Кладёт заданный байт по заданному адресу, увеличивает cur на 1
void putNum(std::string num,unsigned char *addr,int &cur);
									// Кладёт заданное целое число по заданному адресу
void putFloat(std::string num,unsigned char *addr,int &cur);
									// Кладёт заданное дробное число по заданному адресу
void putReg(std::string reg,Regs &regs,unsigned char *addr,int &cur);
									// Кладёт заданнй регистр по заданному адресу
void printBcode(unsigned char *bcode, size_t len);
									// Выводит содержимое массива байт-кодов на экран
