#include "LizzyLangApi.hpp"


using namespace std;
using namespace lizzy;

void lang::api::connect_api(Package& apiPkg)
{
    apiPkg.createCommand("if", false).getActionBundle().setAction({LZDataType::isBool}, lang::api::if_1_LZBool);
    apiPkg.createCommand("elif", false).getActionBundle().setAction({LZDataType::isBool}, lang::api::elif_1_LZBool);
    apiPkg.createCommand("else", false).getActionBundle().setAction({}, lang::api::else_0);
    apiPkg.createCommand("endif", false).getActionBundle().setAction({}, lang::api::endif_0);
    apiPkg.createCommand("while", false).getActionBundle().setAction({LZDataType::isBool}, lang::api::while_1_LZBool);
    apiPkg.createCommand("endwhile", false).getActionBundle().setAction({}, lang::api::endwhile_0);
    apiPkg.createCommand("end.if", false).getActionBundle().setAction({}, lang::api::endif_0);
    apiPkg.createCommand("end.while", false).getActionBundle().setAction({}, lang::api::endwhile_0);
}

LZDataType *lang::api::if_1_LZBool(Arguments args, ExecutionEnv *env)
{
    bool value = args[0]->toBool();
    env->setIPtr(env->getBranchController()->rif(env->getIPtr(), value));
    return nullptr;
}

LZDataType *lang::api::elif_1_LZBool(Arguments args, ExecutionEnv *env)
{
    bool value = args[0]->toBool();
    env->setIPtr(env->getBranchController()->relif(env->getIPtr(), value));
    return nullptr;
}

LZDataType *lang::api::else_0(Arguments args, ExecutionEnv *env)
{
    env->setIPtr(env->getBranchController()->relse(env->getIPtr()));
    return nullptr;
}

LZDataType *lang::api::endif_0(Arguments args, ExecutionEnv *env)
{
    env->getBranchController()->rendif(env->getIPtr());
    return nullptr;
}

LZDataType *lang::api::while_1_LZBool(Arguments args, ExecutionEnv *env)
{
    bool value = args[0]->toBool();
    env->setIPtr(env->getBranchController()->rwhile(env->getIPtr(), value));
    return nullptr;
}

LZDataType *lang::api::endwhile_0(Arguments args, ExecutionEnv *env)
{
    env->setIPtr(env->getBranchController()->rendwhile(env->getIPtr()));
    return nullptr;
}
