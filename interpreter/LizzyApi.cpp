#include "LizzyApi.hpp"


using namespace std;
using namespace lizzy;

void api::connect_api(Package& apiPkg)
{
    apiPkg.setName("lizzy");
    apiPkg.createCommand("nop", false).getActionBundle().setAction({}, api::nop);

    lang::api::connect_api(apiPkg.createPackage("lang"));
}

LZDataType *api::nop(Arguments args, ExecutionEnv *env)
{
    Debug::logwarn(to_string(env->getIPtr()) + "]---nop---");
    return nullptr;
}
