#ifndef BLINKNET_PLATFORM_H
#define BLINKNET_PLATFORM_H

#ifdef _WIN32
    #define _WINSOCK_DEPRECATED_NO_WARNINGS
    #include <WinSock2.h>
    #include <WS2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <errno.h>

    using SOCKET = int;
    static constexpr SOCKET INVALID_SOCKET = -1;
    static constexpr int SOCKET_ERROR = -1;

    inline int closesocket(SOCKET s) { return close(s); }
    inline int WSAGetLastError() { return errno; }

    static constexpr int WSAEWOULDBLOCK = EWOULDBLOCK;
    static constexpr int WSAEINTR       = EINTR;
    static constexpr int WSAECONNRESET  = ECONNRESET;
    static constexpr int WSAEINVAL      = EINVAL;
#endif

#include <string>

namespace BlinkNet
{
    /** @brief Initialize platform networking (WSAStartup on Windows, no-op on POSIX) */
    bool InitNetworking();

    /** @brief Tear down platform networking (WSACleanup on Windows) */
    void ShutdownNetworking();
}

#endif //BLINKNET_PLATFORM_H
