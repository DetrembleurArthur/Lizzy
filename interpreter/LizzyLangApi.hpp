#ifndef LIZZY_LANG_API_HPP
#define LIZZY_LANG_API_HPP
#include "Package.hpp"

namespace lizzy
{
    namespace lang
    {
        namespace api
        {
            void connect_api(Package& apiPkg);
            LZDataType *var_1_LZId(Arguments args, ExecutionEnv *env);
            LZDataType *if_1_LZBool(Arguments args, ExecutionEnv *env);
            LZDataType *elif_1_LZBool(Arguments args, ExecutionEnv *env);
            LZDataType *else_0(Arguments args, ExecutionEnv *env);
            LZDataType *endif_0(Arguments args, ExecutionEnv *env);
        }
    }
}


#endif
