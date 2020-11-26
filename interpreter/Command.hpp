#ifndef COMMAND_HPP
#define COMMAND_HPP
#include "Packageable.hpp"
#include <vector>
#include <map>

namespace lizzy
{
    typedef const std::vector<std::string>& Arguments;
    typedef std::string (*Action)(Arguments args);

    class Command : public Packageable
    {
    private:
        std::vector<Command *> subcommands;
        std::map<int, Action> actions;

    public:
        Command(const std::string &name, const Packageable *super = nullptr);
    };
} // namespace lizzy

#endif
