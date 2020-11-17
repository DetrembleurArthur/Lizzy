#ifndef EXTRACTABLE_HPP
#define EXTRACTABLE_HPP
#include <string>
#include <iostream>

namespace lizzy
{
    class Packageable
    {
    private:
        std::string name;
        const Packageable *super;

    public:
        Packageable(const std::string &name, const Packageable *super = nullptr);
        virtual ~Packageable();
        void setSuper(const Packageable *super);
        void setName(const std::string &name);
        const Packageable *getSuper();
        std::string getName() const;
        std::string getFullName() const;
        bool operator==(const Packageable &other) const;
    };
} // namespace lizzy

#endif
