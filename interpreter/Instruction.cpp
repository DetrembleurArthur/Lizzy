#include "Instruction.hpp"


using namespace std;
using namespace lizzy;



Instruction::Instruction(Command *command) : protoMap(nullptr), command(command), super(nullptr), dataStack(nullptr)
{
	Debug::loginfo("create instruction: " + command->getViewFullName());
}

Instruction::~Instruction()
{
	for(Callable *c : arguments)
	{
		delete c;
	}
	if(not super and dataStack)
		delete dataStack;
	Debug::loginfo("destroy instruction: " + getStackTrace());
}


Instruction& Instruction::push(Callable* arg)
{
	arguments.push_back(arg);
	if(dynamic_cast<Instruction *>(arg))
	{
		dynamic_cast<Instruction *>(arg)->setSuper(this);
		dynamic_cast<Instruction *>(arg)->setPDataStack(dataStack);
		Debug::loginfo("push instruction:\n" + dynamic_cast<Instruction *>(arg)->getStackTrace());
	}
	Debug::loginfo("push argument");
	return *this;
}



string Instruction::getStackTrace(string message) const
{
	return command->getViewFullName() + "(" + to_string(arguments.size()) + ") " + message + (super ? "\n\t" + super->getStackTrace() : "");
}

void Instruction::throwEx(string message) const
{
	throw LZException(getStackTrace(message));
}


LZDataType *Instruction::getResult() const
{
	vector<LZDataType *> results;
	string prototype = "";
	cout << "exec" << endl;
	if(not arguments.empty())
	{
		auto len = arguments.size();
		LZDataType *result = arguments[0]->getResult();
		if(dynamic_cast<LZId *>(result))
		{
			LZVariable *temp = (*dataStack)->getVariable(result->toString());
			if(temp)
			{
				result = temp;
			}
		}
		prototype = result->getId();
		results.push_back(result);
		for(int i = 1; i < len; i++)
		{
			result = arguments[i]->getResult();
			if(dynamic_cast<LZId *>(result))
			{
				LZVariable *temp = (*dataStack)->getVariable(result->toString());
				if(temp)
				{
					result = temp;
				}
			}
			prototype += "&" + result->getId();
			results.push_back(result);
		}
	}
	cout << "PROTO: " << prototype << endl;
	if(not undefined)
	{
		if(protoMap->find(prototype) == protoMap->end())
		{
			if(protoMap->find("") != protoMap->end())
			{
				prototype = "";
			}
			else
			{
				throwEx("has no prototype like (" + prototype + ")");
			}
		}
		return (*protoMap)[prototype](results);
	}
	else
	{
		return (*protoMap)[""](results);
	}
}

void Instruction::setSuper(Instruction *super)
{
	this->super = super;
}

void Instruction::setProtoMap(ProtoMap *protoMap, bool undefined)
{
	this->protoMap = protoMap;
	this->undefined = undefined;
}

void Instruction::setDataStack(DataStack *dataStack)
{
	if(not this->dataStack)
		this->dataStack = new DataStack*;
	*this->dataStack = dataStack;
}

void Instruction::setPDataStack(DataStack **pdataStack)
{
	this->dataStack = pdataStack;
}
