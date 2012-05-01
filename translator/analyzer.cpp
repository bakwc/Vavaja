#include "analyzer.h"

//------------------------------------------------------------------------------------------
void Analyzer::load(const std::string fname)
{
	std::ifstream source(fname);
	std::string tmp;
	while (!source.eof())
	{
		getline(source,tmp);
		if (tmp.length()!=0)
			listing_.push_back(tmp);
	}
	source.close();
}

//------------------------------------------------------------------------------------------
void Analyzer::loadSyntax(const std::string fname)
{
	std::ifstream source(fname);
	while (!source.eof())
	{
		std::string tmp;
		getline(source,tmp);
		if (tmp.length()!=0)
		{
			SyntaxRecord synt;
			Lines splited;
			split(tmp,splited,':');
			synt.cmd=splited[0];
			synt.code=atoi(*(splited.end()-1));
			for (auto i=(splited.begin()+1);i<(splited.end()-1);i++)
			{
				synt.args.push_back(*i);
			}
			syntax_.push_back(synt);
		}
	}
	source.close();
}

//------------------------------------------------------------------------------------------
void Analyzer::process()
{
	for (auto i=listing_.begin();i<listing_.end();i++)
	{
        Args args;
        split((*i),args);
        curLine_++;
		
		bool matched=false;
		if (args[0][0]=='.')
		{
			if (args[0]==".byte")
			{
				memory_->putByte(atoi(args[1]));
				matched=true;
			} else
			if (args[0]==".short")
			{
				memory_->putNum(args[1]);
				matched=true;
			} else
			if (args[0]==".float")
			{
				memory_->putFloat(args[1]);
				matched=true;
			} else
			if (args[0]==".space")
			{
				int count=atoi(args[1]);
				for (auto i=0;i<count;++i)
				{
					memory_->putByte(0);
				}
				matched=true;
			} else
			if (args[0]==".string")
			{
				std::string tmp;
				for (auto i=(args.begin()+1);i<args.end();i++)
				{
					tmp+=(*i)+" ";
				}
				for (auto i=0;i<tmp.length()-1;i++)
				{
					memory_->putByte(tmp[i]);
				}
				matched=true;
			}
		} else
		if (labels_->isLabel(args[0]))
		{
			labels_->addLabel(args[0],memory_->getCurrent());
			matched=true;
		} else
		for (auto j=syntax_.begin();j<syntax_.end();j++)
		{
			if (args[0]==j->cmd)
			{
				int mCount=0,currArg=0;
				
				for (auto k=j->args.begin();k<j->args.end();k++)
				{								// в первом проходе считаем соответствия
					currArg++;
					if (currArg>=args.size()) break;
					
					if ( ((*k)=="num") && isNumber(args[currArg]))
					{
						mCount++;
						continue;
					} else
					if ( ((*k)=="float") && isFloat(args[currArg]))
					{
						mCount++;
						continue;
					} else
					if ( ((*k)=="reg") && regs_->isReg(args[currArg]))
					{
						mCount++;
						continue;
					} else
					if ( ((*k)=="regfloat") && regs_->isRegFloat(args[currArg]))
					{
						mCount++;
						continue;
					} else
					if ( ( ((*k)=="mem") || ((*k)=="regmem") ) && (args[currArg][0]=='%') )
					{
						//std::cout << "Memory: " << args[currArg] << "\n";
						std::string tmpStr=args[currArg];
						tmpStr.erase(0,1);
						if ( ((*k)=="mem") && isNumber(tmpStr))
						{
							mCount++;
							continue;
						} else
						if ( ((*k)=="regmem") && regs_->isReg(tmpStr))
						{
							mCount++;
							continue;
						} else
						if ((*k)=="mem")
						{
							mCount++;
							continue;
						}
					} else
					if (((*k)=="num") &&
						(isNumber(args[currArg])==false) &&
						(isFloat(args[currArg])==false) &&
						(regs_->isReg(args[currArg])==false) &&
						(regs_->isRegFloat(args[currArg])==false) &&
						(args[currArg][0]!='%'))
					{
						mCount++;
						continue;
					}
				}
				
				if (mCount==(args.size()-1))
				{
					//std::cout << j->cmd << ": " << mCount << "\n";
					matched=true;
					
					memory_->putByte(j->code);
					currArg=0;
					for (auto k=j->args.begin();k<j->args.end();k++)
					{								// во втором проставляем байты
						currArg++;
						if (currArg>=args.size()) break;
						
						if ( ((*k)=="num") && isNumber(args[currArg]))
						{
							memory_->putNum(args[currArg]);
							continue;
						} else
						if ( ((*k)=="float") && isFloat(args[currArg]))
						{
							memory_->putFloat(args[currArg]);
							continue;
						} else
						if ( ((*k)=="reg") && regs_->isReg(args[currArg]))
						{
							memory_->putReg(args[currArg]);
							continue;
						} else
						if ( ((*k)=="regfloat") && regs_->isRegFloat(args[currArg]))
						{
							memory_->putRegFloat(args[currArg]);
							continue;
						} else
						if ( ( ((*k)=="mem") || ((*k)=="regmem") ) && (args[currArg][0]=='%') )
						{
							std::string tmpStr=args[currArg];
							tmpStr.erase(0,1);
							if ( ((*k)=="mem") && isNumber(tmpStr))
							{
								memory_->putNum(tmpStr);
								continue;
							} else
							if ( ((*k)=="regmem") && regs_->isReg(tmpStr))
							{
								memory_->putReg(tmpStr);
								continue;
							} else
							if ((*k)=="mem")
							{
								labels_->addAddr(memory_->getCurrent(),tmpStr);
								//std::cout << "Added: " << memory_->getCurrent() << " - " << tmpStr << "\n";
								memory_->putByte(0);
								memory_->putByte(0);
								continue;
							}
						}  else
						if (((*k)=="num") &&
							(isNumber(args[currArg])==false) &&
							(isFloat(args[currArg])==false) &&
							(regs_->isReg(args[currArg])==false) &&
							(regs_->isRegFloat(args[currArg])==false) &&
							(args[currArg][0]!='%'))
						{
							labels_->addAddr(memory_->getCurrent(),args[currArg]);
							//std::cout << "Added: " << memory_->getCurrent() << " - " << args[currArg] << "\n";
							memory_->putByte(0);
							memory_->putByte(0);
							continue;
						}
					}
					break;
				}
			}
		}
		
		if (matched==false)
			error(curLine_,"Syntax error");
	}
	memory_->print();
	labels_->setLabels();
}

