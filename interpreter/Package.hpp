#ifndef PACKAGE_HPP
#define PACKAGE_HPP
#include "Command.hpp"
#include <vector>
#include "Exceptions.hpp"

namespace lizzy
{
    class Package : public Packageable
    {
    private:
        std::vector<Packageable *> children;
    public:
        Package(const std::string &name, const Packageable *super = nullptr);
        virtual ~Package();
        Package &createPackage(const std::string &pkgname);
        void removePackage(const std::string& name);
        bool existsPackage(const std::string& name);
        Package& getPackage(const std::string& name);
        Command &createCommand(const std::string &name);
        void removeCommand(const std::string& name);
        bool existsCommand(const std::string& name);
        Command& getCommand(const std::string& name);
    };
} // namespace lizzy

#endif
