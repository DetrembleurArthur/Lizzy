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
        Package(const std::string &name, const Packageable *super = nullptr);
    public:
        static Package *create(const std::string& name="root");
        virtual ~Package();
        Package &createPackage(const std::string &pkgname);
        void remove(const std::string& name);
        bool exists(const std::string& name);
        Packageable *get(const std::string& name);
        void search(const std::string& name, std::vector<Command *>& occurences);
        void searchExceptionThrowing(const std::string& name, std::vector<Command *>& occurences);
        void removePackage(const std::string& name);
        bool existsPackage(const std::string& name);
        Package *getPackage(const std::string& name);
        Command &createCommand(const std::string &name, bool inner = true);
        void removeCommand(const std::string& name);
        bool existsCommand(const std::string& name);
        Command *getCommand(const std::string& name);
        std::string getViewFullName() const override;
    };
} // namespace lizzy

#endif
