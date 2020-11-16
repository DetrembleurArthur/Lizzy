#ifndef EXTRACTABLE_HPP
#define EXTRACTABLE_HPP
#include <string>
#include <iostream>

namespace lizzy
{
    class Extractable
    {
    private:
        std::string name;
        const Extractable* super;
    public:
        Extractable(const std::string& name, const Extractable *super=nullptr);
        virtual ~Extractable();
        void setSuper(const Extractable *super);
        void setName(const std::string& name);
        const Extractable *getSuper();
        std::string getName() const;
        std::string getFullName() const;
        bool operator==(const Extractable& other) const;
    };
}


#endif
