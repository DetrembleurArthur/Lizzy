#include "Command.hpp"


using namespace std;
using namespace lizzy;


Command::Command(const std::string &name, const Packageable *super) : Packageable(name, super)
{

}
