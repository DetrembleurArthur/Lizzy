#include "Instruction.hpp"


using namespace std;
using namespace lizzy;


Instruction::Instruction() : Instruction(nullptr)
{

}

Instruction::Instruction(Runnable runnable) : runnable(runnable)
{

}

Instruction::Instruction(const Instruction& other) : Instruction(other.getRunnable())
{

}

Instruction::Instruction(Instruction&& other) : Instruction(other.getRunnable())
{

}

void Instruction::setRunnable(Runnable runnable)
{
	this->runnable = runnable;
}

Runnable Instruction::getRunnable() const
{
	return runnable;
}

Instruction& Instruction::push(const Callable& arg)
{
	arguments.push(arg);
}

Instruction& Instruction::push(Callable&& arg)
{
	arguments.push(arg);
}

string Instruction::getResult() const
{
	return runnable(arguments);
}
