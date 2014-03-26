#include "master.hpp"

#include <iostream>
#include <sstream>
#include <random>

#ifdef _WIN32
#include <windows.h>
#endif

int main()
{
    std::cout << "= AKM Proxy =" << std::endl << std::endl;

    master::create("213.248.126.37", (unsigned short)443).start(5555);

    system("PAUSE");

    return 0;
}