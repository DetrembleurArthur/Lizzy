#ifndef PACKAGE_HPP
#define PACKAGE_HPP
#include "Packageable.hpp"
#include <vector>
#include "Exceptions.hpp"

namespace lizzy
{
    class Package : public Packageable
    {
    private:
        std::vector<Packageable *> children;
        void extractPackageNames(const std::string& name, std::string& dstcurrent, std::string& dstsub);
    public:
        Package(const std::string &name, const Packageable *super = nullptr);
        virtual ~Package();
        Package &addPackage(const std::string &pkgname);
        void removePackage(const std::string& name);
        bool existsPackage(const std::string& name);
        Package& getPackage(const std::string& name);
    };
} // namespace lizzy

#endif
