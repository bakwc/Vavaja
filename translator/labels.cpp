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