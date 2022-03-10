#ifndef EP_UDPCLIENT_H
#define EP_UDPCLIENT_H

#include <string>
#include "SocketBase.h"

using namespace std;

class UDPClient {
private:
    mFd udp_fd = -1;
    sockaddr_in addr{};

public:

    UDPClient();

    UDPClient(const string &ip, int port);

    ssize_t sendto(const char *ip, int port, const void *buff, int len, int flag = 0) const;

    ssize_t send(const void *buff, int len, int flag = 0);

    ssize_t recv(void *buff, int len, int flag = 0) const;

    ssize_t recvo(void *buff, size_t len, int flag = 0) const;

    ssize_t close() const;

    ssize_t recvo(void *buff, int index, size_t len, int flag) const;
};


#endif //EP_UDPCLIENT_H
