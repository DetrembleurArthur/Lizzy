#include "Instruction.hpp"


using namespace std;
using namespace lizzy;



Instruction::Instruction(Command *command) : protoMap(nullptr), command(command), super(nullptr)
{
	Debug::loginfo("create instruction: " + command->getViewFullName());
}

Instruction::~Instruction()
{
	for(Callable *c : arguments)
	{
		delete c;
	}
	Debug::loginfo("destroy instruction: " + getStackTrace());
}


Instruction& Instruction::push(Callable* arg)
{
	arguments.push_back(arg);
	if(dynamic_cast<Instruction *>(arg))
	{
		dynamic_cast<Instruction *>(arg)->setSuper(this);
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
	Debug::loginfo("prepare execution...");
	vector<LZDataType *> results;
	string prototype = "";
	
	if(not arguments.empty())
	{
		auto len = arguments.size();
		LZDataType *result = arguments[0]->getResult();
		prototype = result->getId();
		results.push_back(result);
		for(int i = 1; i < len; i++)
		{
			result = arguments[i]->getResult();
			Debug::loginfo(result->getId());
			prototype += "&" + result->getId();
			results.push_back(result);
		}
	}
	if(not undefined)
	{
		if(protoMap->find(prototype) == protoMap->end())
			throwEx("has no prototype like (" + prototype + ")");
		Debug::loginfo("execute instruction: " + prototype);
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
