#include "Socket/Platform.h"
#include <iostream>

int main()
{
    std::cout << "Blinknet test: starting" << std::endl;

    if (!BlinkNet::InitNetworking())
    {
        std::cerr << "Blinknet test: InitNetworking failed" << std::endl;
        return 1;
    }

    std::cout << "Blinknet test: networking initialized" << std::endl;

    BlinkNet::ShutdownNetworking();

    std::cout << "Blinknet test: done" << std::endl;
    return 0;
}
