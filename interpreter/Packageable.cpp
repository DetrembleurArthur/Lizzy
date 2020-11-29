#include "Packageable.hpp"

using namespace std;
using namespace lizzy;


Packageable::Packageable(const std::string& name, const Packageable *super)
{
    setName(name);
    setSuper(super);
    flags.able = true;
}

Packageable::~Packageable()
{
    
}

void Packageable::setSuper(const Packageable *super)
{
    this->super = super;
}

void Packageable::setName(const std::string& name)
{
    if(name.find(".") != string::npos)
        throw LZException("package name must not contains '.' char : " + name);
    this->name = name;
}

const Packageable *Packageable::getSuper()
{
    return super;
}

std::string Packageable::getName() const
{
    return name;
}

std::string Packageable::getFullName() const
{
    return super ? super->getFullName() + "." + getName() : getName();
}

std::string Packageable::getViewFullName() const
{
    return getViewFullName();
}

bool Packageable::operator==(const Packageable& other) const
{
    return getFullName() == other.getFullName();
}

std::ostream& operator<<(std::ostream& out, const Packageable& p)
{
    return out << p.getFullName();
}

void Packageable::extractNames(const std::string& name, std::string& dstcurrent, std::string& dstsub)
{
    int i = name.find(".");
    if(i != string::npos)
    {
        if(i == name.size() - 1)
            throw LZException(name + " package path is not correctly formatted");
        dstsub = name.substr(i + 1);
        dstcurrent = name.substr(0, i);
    }
    else
    {
        dstsub = "";
        dstcurrent = name;
    }
}

bool Packageable::isAble() const
{
    return flags.able;
}

void Packageable::setAble(bool state)
{
    flags.able = state;
}
