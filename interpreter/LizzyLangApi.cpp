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
    apiPkg.createCommand("var", false).getActionBundle().setAction({LZDataType::isId}, lang::api::var_1_LZId);
    apiPkg.getCommand("var")->getActionBundle().setAction({LZDataType::isId, LZDataType::isDataType}, lang::api::var_2_LZId_LZDataType);
    apiPkg.createCommand("print", false).getActionBundle().setAction(lang::api::print_X);
    apiPkg.createCommand("println", false).getActionBundle().setAction(lang::api::println_X);
}

LZDataType *lang::api::if_1_LZBool(Arguments args, ExecutionEnv *env)
{
    bool value = args[0]->toBool();
    int res = env->getBranchController()->rif(env->getIPtr(), value);
    if(res != env->getIPtr())
    {
        env->setIPtr(res);
    }
    else
    {
        env->getDataStack()->push();
    }
    
    return nullptr;
}

LZDataType *lang::api::elif_1_LZBool(Arguments args, ExecutionEnv *env)
{
    bool value = args[0]->toBool();
    int res = env->getBranchController()->relif(env->getIPtr(), value);
    if(res != env->getIPtr())
    {
        env->setIPtr(res);
    }
    else
    {
        env->getDataStack()->push();
    }
    return nullptr;
}

LZDataType *lang::api::else_0(Arguments args, ExecutionEnv *env)
{
    int res = env->getBranchController()->relse(env->getIPtr());
    if(res != env->getIPtr())
    {
        env->setIPtr(res);
    }
    else
    {
        env->getDataStack()->push();
    }
    return nullptr;
}

LZDataType *lang::api::endif_0(Arguments args, ExecutionEnv *env)
{
    env->getBranchController()->rendif(env->getIPtr());
    env->getDataStack()->pop();
    return nullptr;
}

LZDataType *lang::api::while_1_LZBool(Arguments args, ExecutionEnv *env)
{
    bool value = args[0]->toBool();
    int res = env->getBranchController()->rwhile(env->getIPtr(), value);
    if(res != env->getIPtr())
    {
        env->setIPtr(res);
    }
    else
    {
        env->getDataStack()->push();
    }
    return nullptr;
}

LZDataType *lang::api::endwhile_0(Arguments args, ExecutionEnv *env)
{
    env->setIPtr(env->getBranchController()->rendwhile(env->getIPtr()));
    env->getDataStack()->pop();
    return nullptr;
}

LZDataType *lang::api::var_1_LZId(Arguments args, ExecutionEnv *env)
{
    env->getDataStack()->push(DataBuilder::buildVariable(args[0]->toString()));
    return nullptr;
}

LZDataType *lang::api::var_2_LZId_LZDataType(Arguments args, ExecutionEnv *env)
{
    LZVariable *variable = DataBuilder::buildVariable(args[0]->toString());
    variable->setValue(args[1]);
    cout << " value "<<args[1]->getId() << endl;
    env->getDataStack()->push(variable);
    return nullptr;
}

LZDataType *lang::api::print_X(Arguments args, ExecutionEnv *env)
{
    if(not args.empty())
    {
        LZDataType *data = LZDataType::isId(args[0]) ? env->getDataStack()->getVariable(
            dynamic_cast<LZId *>(args[0])->getValue().substr(1)
        ) : args[0];
        cout << data->toString();
        for(int i = 1; i < args.size(); i++)
        {
            data = LZDataType::isId(args[i]) ? env->getDataStack()->getVariable(
            dynamic_cast<LZId *>(args[i])->getValue().substr(1)
        ) : args[1];
            cout << " " << data->toString();
        }
    }
    return nullptr;
}

LZDataType *lang::api::println_X(Arguments args, ExecutionEnv *env)
{
    print_X(args, env);
    cout << endl;
    return nullptr;
}
