//
// Created by me on 2021/9/25 0025.
//


#include "UDPServer.h"


UDPServer::~UDPServer() {
    close();
}


UDPServer::UDPServer(int port) : port(port) {

#if defined(PLATFORM_WINDOWS)

    WORD sockVision = MAKEWORD(2, 2);
    WSADATA wsadata;

    if (WSAStartup(sockVision, &wsadata) != 0) {
        printf("init wsa fail\n");
        return;
    }

    //创建套接字
    udp_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (udp_fd == INVALID_SOCKET) {
        printf("create socket fail\n");
        return;
    }


#elif defined(PLATFORM_ANDROID) || defined(PLATFORM_LINUX)
    udp_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_fd < 0) {
        printf("create socket fail\n");
        return;
    }
#endif

    sockaddr_in local_addr{};
    local_addr.sin_family = AF_INET;          // 使用IPV4协议
    local_addr.sin_port = htons(port);
    local_addr.sin_addr.s_addr = INADDR_ANY;  // 绑定本地IP
    int ret = bind(udp_fd, (sockaddr *) &local_addr, sizeof local_addr);
    if (ret < 0) {
        printf("bind fail:\n");
        close();
        return;
    } else {
        printf("init UDPServer Success!\n");
    }
}

ssize_t UDPServer::sendto(const char *ip, int clientPort, const void *buff, size_t len, int flag) {
    sockaddr_in clientAddr{};
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_port = htons(clientPort);
    clientAddr.sin_addr.s_addr = inet_addr(ip);
    return sendto(&clientAddr, buff, len, flag);
}


ssize_t UDPServer::sendto(CLIENT_ADDR *src_addr, const void *buff, size_t len, int flag) {
    return ::sendto(udp_fd, static_cast<const char *>(buff), len, flag, (sockaddr *) src_addr, addr_len);
}

ssize_t UDPServer::recv(void *buff, size_t len, int flag) {
    return ::recv(udp_fd, static_cast<char *>(buff), len, flag);
}

ssize_t UDPServer::recvo(void *buff, size_t len, int flag) {
    auto *tempBuff = (unsigned char *) buff;
    int totalRecv = 0;
    size_t size = len;
    while (size > 0) {
        ssize_t i = ::recv(udp_fd, reinterpret_cast<char *>(&tempBuff[totalRecv]), size, flag);
        if (i == 0) {
            return i;
        } else if (i == -1) {
            // 数据接收错误，可能客户端断开连接
            printf("error during recvall: %d\n", (int) i);
            return i;
        }
        totalRecv += i;
        size -= i;
    }
    return totalRecv;
}


ssize_t UDPServer::recv(CLIENT_ADDR *src_addr, void *buff, size_t len, int flag) {
#if defined(PLATFORM_WINDOWS)
    return ::recvfrom(udp_fd, static_cast<char *>(buff), len, flag, (sockaddr *) src_addr, &addr_len);
#elif defined(PLATFORM_ANDROID) || defined(PLATFORM_LINUX)
    return ::recvfrom(udp_fd, static_cast<char *>(buff), len, flag, (sockaddr *) src_addr,
                      (socklen_t *) &addr_len);
#endif
}

ssize_t UDPServer::recvo(CLIENT_ADDR *src_addr, void *buff, size_t len, int flag) {
    auto *tempBuff = (unsigned char *) buff;
    int totalRecv = 0;
    size_t size = len;
    while (size > 0) {

#if defined(PLATFORM_WINDOWS)
        ssize_t i = recvfrom(udp_fd, reinterpret_cast<char *>(&tempBuff[totalRecv]), size, flag, (sockaddr *) src_addr,
                             &addr_len);
#elif defined(PLATFORM_ANDROID) || defined(PLATFORM_LINUX)
        ssize_t i = recvfrom(udp_fd, &tempBuff[totalRecv], size, flag, (sockaddr *) src_addr,
                             (socklen_t *) (&addr_len));
#endif
        if (i == 0) {
            return i;
        } else if (i == -1) {
            // 数据接收错误，可能客户端断开连接
            printf("error during recvall: %d\n", (int) i);
            return i;
        }
        totalRecv += i;
        size -= i;
    }
    return totalRecv;
}


ssize_t UDPServer::close() {
#if defined(PLATFORM_WINDOWS)
    return ::closesocket(udp_fd);
#elif defined(PLATFORM_ANDROID) || defined(PLATFORM_LINUX)
    return ::close(udp_fd);
#endif
}



