#ifndef EXTRACTABLE_HPP
#define EXTRACTABLE_HPP
#include <string>
#include <iostream>
#include "Exceptions.hpp"

namespace lizzy
{
    class Packageable
    {
    private:
        std::string name;
        const Packageable *super;
    protected:
        void extractNames(const std::string& name, std::string& dstcurrent, std::string& dstsub);
    public:
        Packageable(const std::string &name, const Packageable *super = nullptr);
        virtual ~Packageable();
        void setSuper(const Packageable *super);
        void setName(const std::string &name);
        const Packageable *getSuper();
        std::string getName() const;
        std::string getFullName() const;
        bool operator==(const Packageable &other) const;
        friend std::ostream& operator<<(std::ostream& out, const Packageable& p);
    };
} // namespace lizzy

#endif
