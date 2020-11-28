#include "Exceptions.hpp"


using namespace std;
using namespace lizzy;


LZException::LZException() : LZException("...")
{

}

LZException::LZException(const string& message) : message(message)
{

}

LZException::LZException(string&& message) : message(message)
{

}

LZException::LZException(const LZException& other) : LZException(other.getMessage())
{

}

LZException::~LZException()
{

}

string LZException::getMessage() const
{
    return message;
}

ostream& operator<<(ostream& out, const LZException& e)
{
    return out << e.getMessage();
}
