#include "LZPrimitive.hpp"

using namespace std;
using namespace lizzy;



template <typename T> LZPrimitive<T>::LZPrimitive() : LZDataType()
{

}

template <typename T> LZPrimitive<T>::LZPrimitive(T value) : LZDataType(), value(value)
{

}

template <typename T> LZPrimitive<T>::LZPrimitive(const LZPrimitive<T>& value) : LZPrimitive(value.getValue())
{

}

template <typename T> LZPrimitive<T>::~LZPrimitive()
{

}

template <typename T> T LZPrimitive<T>::getValue() const
{
    return value;
}

template <typename T> void LZPrimitive<T>::setValue(T value)
{
    this->value = value;
}


template class lizzy::LZPrimitive<long>;
template class lizzy::LZPrimitive<double>;
template class lizzy::LZPrimitive<bool>;
template class lizzy::LZPrimitive<std::string>;
