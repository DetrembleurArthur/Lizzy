#include "LizzyApi.hpp"


using namespace std;
using namespace lizzy;

void api::connect_api(Package& apiPkg)
{
    apiPkg.setName("lizzy");
    apiPkg.createCommand("nop", false).getActionBundle().setAction({}, api::nop);

    Command& command = apiPkg.createCommand("test", false);
    command.getActionBundle().setAction([](Arguments args, ExecutionEnv *env){
            cout << args.size() << endl;
            return (LZDataType *) nullptr;
    });
    command.getActionBundle().setAction({LZDataType::isFloat},
    [](Arguments args, ExecutionEnv *env){
            cout << "FL" << endl;
            return (LZDataType *) nullptr;
    });
    command.getActionBundle().setAction({LZDataType::isInteger},
    [](Arguments args, ExecutionEnv *env){
            cout << "INT" << endl;
            return (LZDataType *) nullptr;
    });

    lang::api::connect_api(apiPkg.createPackage("lang"));
}

LZDataType *api::nop(Arguments args, ExecutionEnv *env)
{
    Debug::logwarn(to_string(env->getIPtr()) + "]---nop---");
    return nullptr;
}
