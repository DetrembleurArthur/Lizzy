#include "Instruction.hpp"


using namespace std;
using namespace lizzy;



Instruction::Instruction(Command *command) : prototype(nullptr), command(command), super(nullptr), env(nullptr)
{
	Debug::loginfo("create instruction: " + command->getViewFullName());
}

Instruction::~Instruction()
{
	for(Callable *c : arguments)
	{
		delete c;
	}
	if(not super and env)
		delete env;
	Debug::loginfo("destroy instruction: " + getStackTrace());
}

Command *Instruction::getCommand()
{
	return command;
}


Instruction& Instruction::push(Callable* arg)
{
	arguments.push_back(arg);
	if(dynamic_cast<Instruction *>(arg))
	{
		if(not dynamic_cast<Instruction *>(arg)->getCommand()->isInner())
			throw LZException(dynamic_cast<Instruction *>(arg)->getCommand()->getViewFullName() + " is not an inner command");
		dynamic_cast<Instruction *>(arg)->setSuper(this);
		dynamic_cast<Instruction *>(arg)->setPEnv(env);
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
	if(not arguments.empty())
	{
		auto len = arguments.size();
		for(int i = 0; i < len; i++)
		{
			LZDataType *result = arguments[i]->getResult();
			results.push_back(result);
		}
	}
	return prototype->get(results)(results, *env);
}

void Instruction::setSuper(Instruction *super)
{
	this->super = super;
}

void Instruction::setPrototype(Prototype *protoMap, bool undefined)
{
	this->prototype = protoMap;
	this->undefined = undefined;
}

void Instruction::setEnv(ExecutionEnv *env)
{
	if(not this->env)
		this->env = new ExecutionEnv*;
	*this->env = env;
}

void Instruction::setPEnv(ExecutionEnv **env)
{
	this->env = env;
}
