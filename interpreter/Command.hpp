#ifndef COMMAND_HPP
#define COMMAND_HPP
#include "Packageable.hpp"
#include <vector>
#include <map>
#include "ActionBundle.hpp"

namespace lizzy
{
    class Command : public Packageable
    {
    private:
        std::vector<Command *> subcommands;
        ActionBundle *actionBundle;

    public:
        Command(const std::string &name, const Packageable *super = nullptr);
        virtual ~Command();
        ActionBundle& getActionBundle();
        Command& createSubCommand(const std::string& name);
        void removeSubCommand(const std::string& name);
        Command& getSubCommand(const std::string& name);
        bool existsSubCommand(const std::string& name);
        std::string getViewFullName() const override;
        void setFlagsCascade() override;
    };
} // namespace lizzy

#endif
