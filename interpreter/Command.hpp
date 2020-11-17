#ifndef COMMAND_HPP
#define COMMAND_HPP
#include "Packageable.hpp"
#include <vector>
#include <map>

namespace lizzy
{
    typedef std::string (*Arguments)(const std::vector<std::string> &args);

    class Command : public Packageable
    {
    private:
        std::vector<Command *> subcommands;
        std::map<int, Arguments> actions;

    public:
        Command(const std::string &name, const Packageable *super = nullptr);
    };
} // namespace lizzy

#endif
