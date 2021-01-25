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
            LZDataType *if_1_LZBool(Arguments args, ExecutionEnv *env);
            LZDataType *elif_1_LZBool(Arguments args, ExecutionEnv *env);
            LZDataType *else_0(Arguments args, ExecutionEnv *env);
            LZDataType *endif_0(Arguments args, ExecutionEnv *env);
            LZDataType *while_1_LZBool(Arguments args, ExecutionEnv *env);
            LZDataType *endwhile_0(Arguments args, ExecutionEnv *env);
            LZDataType *var_1_LZId(Arguments args, ExecutionEnv *env);
            LZDataType *var_2_LZId_LZDataType(Arguments args, ExecutionEnv *env);
            LZDataType *print_X(Arguments args, ExecutionEnv *env);
            LZDataType *println_X(Arguments args, ExecutionEnv *env);
        }
    }
}


#endif
