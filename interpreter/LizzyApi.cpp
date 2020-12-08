#include "LizzyApi.hpp"


using namespace std;
using namespace lizzy;



void api::connect_api(Package& apiPkg)
{
    apiPkg.setName("lizzy");
    Package& std_io_pkg = apiPkg.createPackage("std.io");
    Package& std_th_pkg = apiPkg.createPackage("std.thread");

    ActionBundle& print_cmd_bdl = std_io_pkg.createCommand("print").getActionBundle();
    print_cmd_bdl.setAction(api::print_1_str_cmd);

    ActionBundle& wait_cmd_bdl = std_th_pkg.createCommand("sleep").getActionBundle();
    wait_cmd_bdl.setAction({LZInteger::type}, api::delay_1_flt_cmd);
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

LZDataType *api::delay_1_flt_cmd(Arguments args)
{
    LZInteger *delayms = *args[0];
    std::this_thread::sleep_for(std::chrono::milliseconds(delayms->getValue()));
    return new LZInteger(delayms->getValue());
}
