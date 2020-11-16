#ifndef PACKAGE_HPP
#define PACKAGE_HPP
#include "Extractable.hpp"
#include <vector>


namespace lizzy
{
    class Package : public Extractable
    {
    private:
        std::vector<Extractable *> children;
    public:
        Package(const std::string& name, const Extractable* super=nullptr);
        virtual ~Package();
        Package& addPkg(const std::string& pkgname);
    };
}

#endif
