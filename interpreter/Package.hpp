#ifndef PACKAGE_HPP
#define PACKAGE_HPP
#include "Packageable.hpp"
#include <vector>

namespace lizzy
{
    class Package : public Packageable
    {
    private:
        std::vector<Packageable *> children;

    public:
        Package(const std::string &name, const Packageable *super = nullptr);
        virtual ~Package();
        Package &addPkg(const std::string &pkgname);
    };
} // namespace lizzy

#endif
