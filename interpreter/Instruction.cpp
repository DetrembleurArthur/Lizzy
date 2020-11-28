#include "Instruction.hpp"


using namespace std;
using namespace lizzy;



Instruction::Instruction(ProtoMap& ProtoMap) : protoMap(protoMap)
{

}


Instruction& Instruction::push(const Callable& arg)
{
	arguments.push_back(arg);
}

Instruction& Instruction::push(Callable&& arg)
{
	arguments.push_back(arg);
}



LZDataType *Instruction::getResult() const
{
	vector<LZDataType *> results;
	string prototype = "";
	if(not arguments.empty())
	{
		auto len = arguments.size();
		prototype = arguments[0].getResult()->getId();
		for(int i = 1; i < len; i++)
		{
			LZDataType *result = arguments[i].getResult();
			prototype += "-" + result->getId();
			results.push_back(result);
		}
	}
	return protoMap[prototype](results);
}
