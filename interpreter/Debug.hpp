#ifndef DEBUG_HPP
#define DEBUG_HPP
#include <iostream>
#include <string>

namespace lizzy
{
    class Debug
    {
    public:
        static void loginfo(const std::string& msg);
        static void logerr(const std::string& msg);
        static void logwarn(const std::string& msg);
        static void logfatal(const std::string& msg);
    };
}




#endif