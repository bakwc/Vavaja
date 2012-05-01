#include "labels.h"


bool Label::isLabel(const std::string & str)
{
	return ((str[str.length()-1]==':') && (str.length()>=2));
}

void Label::addLabel(const std::string & str, unsigned char addr)
{
	labels1_[str]=addr;
}

void Label::addAddr(unsigned char addr, const std::string & lbl)
{
	labels2_[addr]=lbl+":";
}

void Label::setLabels()
{
	for (auto i=labels2_.begin();i!=labels2_.end();i++)
	{
		memory_->putTwoBytes(i->first,(short)labels1_[i->second]);
	}
}