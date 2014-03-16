#include "akm/master.hpp"

#include <iostream>

int main()
{
	std::cout << "= AKM Proxy =" << std::endl << std::endl;
	akm::master::create().start(5555);

	return 0;
}