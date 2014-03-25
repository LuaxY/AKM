#include "master.hpp"

#include <iostream>
#include <sstream>
#include <random>

#ifdef _WIN32
#include <windows.h>
#endif

int main()
{
    std::cout << "= AKM Master Sound =" << std::endl << std::endl;

    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<unsigned short> rand(1024, 65535);
    unsigned short port = rand(generator);

#ifdef _WIN32
    STARTUPINFO startup_info;
    PROCESS_INFORMATION reg_process_info, client_process_info;

    memset(&startup_info, 0, sizeof(startup_info));
    memset(&reg_process_info, 0, sizeof(reg_process_info));
    memset(&client_process_info, 0, sizeof(client_process_info));

    std::ostringstream cmd_reg;
    std::ostringstream cmd_client;

    cmd_reg << "C:\\Program Files (x86)\\Dofus2Beta\\app\\reg\\Reg.exe --reg-engine-port=" << port + 1;
    cmd_client << "C:\\Program Files (x86)\\Dofus2Beta\\app\\DofusMod.exe --lang=fr --update-server-port=" << port << " --updater_version=v2 --reg-client-port=" << port + 2;

    CreateProcess(NULL, (LPSTR)cmd_reg.str().c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &startup_info, &reg_process_info);
    CreateProcess(NULL, (LPSTR)cmd_client.str().c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &startup_info, &client_process_info);
#endif

    master::create().start(port);

    return 0;
}