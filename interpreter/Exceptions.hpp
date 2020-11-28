#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP
#include <string>
#include <iostream>

namespace lizzy
{
    class LZException
    {
    private:
        const std::string message;
    public:
        LZException();
        LZException(const std::string& message);
        LZException(std::string&& message);
        LZException(const LZException& other);
        virtual ~LZException();
        std::string getMessage() const;
        friend std::ostream& operator<<(std::ostream& out, const LZException& e);
    };
}


#endif

