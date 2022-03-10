//
// Created by NotAdmin on 2021/9/21.
//


#include "UDPClient.h"


UDPClient::UDPClient() {

#if defined(PLATFORM_WINDOWS)
    WORD sockVision = MAKEWORD(2, 2);
    WSADATA wsadata;
    if (WSAStartup(sockVision, &wsadata) != 0) {
        printf("init wsa fail\n");
        return;
    }
#endif
    int i = 1;
    socklen_t len = sizeof(i);
    udp_fd = socket(AF_INET, SOCK_DGRAM, 0);
    setsockopt(udp_fd, SOL_SOCKET, SO_BROADCAST, reinterpret_cast<const char *>(&i), len);
}


UDPClient::UDPClient(const string &ip, int port) {
#if defined(PLATFORM_WINDOWS)
    WORD sockVision = MAKEWORD(2, 2);
    WSADATA wsadata;

    if (WSAStartup(sockVision, &wsadata) != 0) {
        printf("init wsa fail\n");
        return;
    }
#endif

    int i = 1;
    socklen_t len = sizeof(i);
    udp_fd = socket(AF_INET, SOCK_DGRAM, 0);
    setsockopt(udp_fd, SOL_SOCKET, SO_BROADCAST, reinterpret_cast<const char *>(&i), len);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
}

ssize_t UDPClient::sendto(const char *ip, int port, const void *buff, int len, int flag) const {
    sockaddr_in temp_addr{};
    temp_addr.sin_family = AF_INET;
    temp_addr.sin_port = htons(port);
    temp_addr.sin_addr.s_addr = inet_addr(ip);
    return ::sendto(udp_fd, static_cast<const char *>(buff), len, flag, (sockaddr *) &temp_addr,
                    sizeof(temp_addr));
}

ssize_t UDPClient::send(const void *buff, int len, int flag) {
    return ::sendto(udp_fd, static_cast<const char *>(buff), len, flag, (sockaddr *) &addr, sizeof(addr));
}

ssize_t UDPClient::recv(void *buff, int len, int flag) const {
    ssize_t i = ::recv(udp_fd, static_cast<char *>(buff), len, flag);
    return i;
}

ssize_t UDPClient::recvo(void *buff, size_t len, int flag) const {
    return recvo(buff, 0, len, flag);
}

ssize_t UDPClient::recvo(void *buff, int index, size_t len, int flag) const {
    auto *tempBuff = (unsigned char *) buff;
    int totalRecv = 0;
    int off = index;
    size_t size = len;
    while (size > 0) {
        ssize_t i = ::recv(udp_fd, reinterpret_cast<char *>(&tempBuff[off]), size, flag);
        if (i == 0) {
            return i;
        } else if (i == -1) {
            // 数据接收错误，可能客户端断开连接
            printf("error during recvall: %d\n", (int) i);
            return i;
        }
        totalRecv += i;
        off += i;
        size -= i;
    }
    return totalRecv;
}


ssize_t UDPClient::close() const {
#if defined(PLATFORM_WINDOWS)
    return ::closesocket(udp_fd);
#elif defined(PLATFORM_ANDROID) || defined(PLATFORM_LINUX)
    return ::close(udp_fd);
#endif
}


