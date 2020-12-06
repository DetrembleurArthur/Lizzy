#include "LizzyApi.hpp"


using namespace std;
using namespace lizzy;



void api::connect_api(Package& apiPkg)
{
    apiPkg.setName("lizzy");
    Package& std_io_pkg = apiPkg.createPackage("std.io");

    ActionBundle& print_cmd_bdl = std_io_pkg.createCommand("print").getActionBundle();
    print_cmd_bdl.setAction(api::print_1_str_cmd);
}

LZDataType *api::print_1_str_cmd(Arguments args)
{
    for(auto arg : args)
    {
        cout << arg->toString() << " ";
    }
    cout << endl;
    return new LZInteger(args.size());
}

