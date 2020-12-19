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
        bool inner;

    public:
        Command(const std::string &name, const Packageable *super = nullptr, bool inner = true);
        virtual ~Command();
        ActionBundle& getActionBundle();
        Command& createSubCommand(const std::string& name, bool inner);
        void removeSubCommand(const std::string& name);
        Command *getSubCommand(const std::string& name);
        bool existsSubCommand(const std::string& name);
        std::string getViewFullName() const override;
        bool isInner() const;
    };
} // namespace lizzy

#endif
