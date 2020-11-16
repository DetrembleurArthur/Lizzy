#include "Extractable.hpp"

using namespace std;
using namespace lizzy;


Extractable::Extractable(const std::string& name, const Extractable *super)
{
    setName(name);
    setSuper(super);
}

Extractable::~Extractable()
{
    cout << "destroy: " << getFullName() << endl;
}

void Extractable::setSuper(const Extractable *super)
{
    this->super = super;
}

void Extractable::setName(const std::string& name)
{
    this->name = name;
}

const Extractable *Extractable::getSuper()
{
    return super;
}

std::string Extractable::getName() const
{
    return name;
}

std::string Extractable::getFullName() const
{
    return super ? super->getFullName() + "." + getName() : getName();
}

bool Extractable::operator==(const Extractable& other) const
{
    return getFullName() == other.getFullName();
}
