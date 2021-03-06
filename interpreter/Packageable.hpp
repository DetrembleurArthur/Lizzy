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
    protected:
        const Packageable *super;
        void setSuper(const Packageable *super);
        static void extractNames(const std::string& name, std::string& dstcurrent, std::string& dstsub);
    public:
        Packageable(const std::string &name, const Packageable *super = nullptr);
        virtual ~Packageable();
        void setName(const std::string &name);
        const Packageable *getSuper();
        std::string getName() const;
        std::string getFullName() const;
        bool operator==(const Packageable &other) const;
        virtual std::string getViewFullName() const;
        friend std::ostream& operator<<(std::ostream& out, const Packageable& p);
    };
} // namespace lizzy

#endif
