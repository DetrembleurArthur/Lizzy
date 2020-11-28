#include "Packageable.hpp"

using namespace std;
using namespace lizzy;


Packageable::Packageable(const std::string& name, const Packageable *super)
{
    setName(name);
    setSuper(super);
}

Packageable::~Packageable()
{
    cout << "clear " << getFullName() << endl;
}

void Packageable::setSuper(const Packageable *super)
{
    this->super = super;
}

void Packageable::setName(const std::string& name)
{
    if(name.find(".") != string::npos)
        throw LZException("package name must not contain '.' char : " + name);
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

bool Packageable::operator==(const Packageable& other) const
{
    return getFullName() == other.getFullName();
}

std::ostream& operator<<(std::ostream& out, const Packageable& p)
{
    return out << p.getFullName();
}
