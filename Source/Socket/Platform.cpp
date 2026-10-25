#include "Platform.h"
#include <iostream>

namespace BlinkNet
{
#ifdef _WIN32
    bool InitNetworking()
    {
        WSADATA wsadata;
        int err = WSAStartup(MAKEWORD(2, 2), &wsadata);
        if (err != 0)
        {
            std::cerr << "WSAStartup failed: " << err << std::endl;
            return false;
        }
        if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wVersion) != 2)
        {
            std::cerr << "Wrong Winsock version" << std::endl;
            WSACleanup();
            return false;
        }
        return true;
    }

    void ShutdownNetworking()
    {
        WSACleanup();
    }
#else
    bool InitNetworking() { return true; }
    void ShutdownNetworking() {}
#endif
}