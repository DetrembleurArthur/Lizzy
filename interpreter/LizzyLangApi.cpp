#include "LizzyLangApi.hpp"


using namespace std;
using namespace lizzy;

void lang::api::connect_api(Package& apiPkg)
{
    apiPkg.createCommand("var", false).getActionBundle().setAction({LZId::type}, lang::api::var_1_LZId);
    apiPkg.createCommand("if", false).getActionBundle().setAction({LZBool::type}, lang::api::if_1_LZBool);
    apiPkg.createCommand("elif", false).getActionBundle().setAction({LZBool::type}, lang::api::elif_1_LZBool);
    apiPkg.createCommand("else", false).getActionBundle().setAction({}, lang::api::else_0);
    apiPkg.createCommand("endif", false).getActionBundle().setAction({}, lang::api::endif_0);
}

LZDataType *lang::api::var_1_LZId(Arguments args, ExecutionEnv *env)
{
    LZId *id = *args[0];
    return nullptr;
}

LZDataType *lang::api::if_1_LZBool(Arguments args, ExecutionEnv *env)
{
    LZBool *value = *args[0];
    if(not value->getValue())
        env->setIPtr(env->getBranchController()->jump(env->getIPtr()));
    return nullptr;
}

LZDataType *lang::api::elif_1_LZBool(Arguments args, ExecutionEnv *env)
{
    return nullptr;
}

LZDataType *lang::api::else_0(Arguments args, ExecutionEnv *env)
{
    return nullptr;
}

LZDataType *lang::api::endif_0(Arguments args, ExecutionEnv *env)
{
    return nullptr;
}
