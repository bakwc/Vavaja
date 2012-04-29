#include "labels.h"

bool Label::isLabel(const std::string & str)
{
	return str[str.length()-1]==':';
}

void Label::addLabel(const std::string & str, unsigned char addr)
{
	labels1_[str]=addr;
}

void Label::addAddr(unsigned char addr, std::string & lbl)
{
	labels2_[addr]=lbl+":";
}

void Label::setLabels()
{
	//for (auto i=labels1_.begin();i!=labels1_.end();i++)
	//{
		
		//std::cout << i->first << " - " << (int)(i->second) << "\n";
	//} //std::cout << std::endl;
	for (auto i=labels2_.begin();i!=labels2_.end();i++)
	{
		memory_->putTwoBytes(i->first,(short)labels1_[i->second]);
		//std::cout << (short)labels1_[i->second] << "\n";
	} //std::cout << std::endl;
}