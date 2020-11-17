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
    cout << "destroy: " << getFullName() << endl;
}

void Packageable::setSuper(const Packageable *super)
{
    this->super = super;
}

void Packageable::setName(const std::string& name)
{
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
