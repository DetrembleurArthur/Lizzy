#include "Instruction.hpp"


using namespace std;
using namespace lizzy;



Instruction::Instruction(Command& command) : protoMap(nullptr), command(command), super(nullptr)
{
	cout << "instruction for " << command.getViewFullName() << endl;
}


Instruction& Instruction::push(Callable* arg)
{
	if(dynamic_cast<Instruction *>(arg))
		dynamic_cast<Instruction *>(arg)->setSuper(this);
	arguments.push_back(arg);
	return *this;
}



string Instruction::getStackTrace(string message) const
{
	return command.getFullName() + "(" + to_string(arguments.size()) + ") : " + message + (super ? "\n" + super->getStackTrace() : "\n");
}

void Instruction::throwEx(string message) const
{
	throw LZException(getStackTrace(message));
}


LZDataType *Instruction::getResult() const
{
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
			prototype += "-" + result->getId();
			results.push_back(result);
		}
	}
	if(protoMap->find(prototype) == protoMap->end())
		throwEx("has no prototype like (" + prototype + ")");
	return (*protoMap)[prototype](results);
}

void Instruction::setSuper(Instruction *super)
{
	this->super = super;
}

void Instruction::setProtoMap(ProtoMap *protoMap)
{
	this->protoMap = protoMap;
}
