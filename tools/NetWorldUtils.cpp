//
// Created by Administrator on 2022/3/9 0009.
//

#include <winsock.h>
#include <iostream>
#include "NetWorldUtils.h"

string NetWorldUtils::getLocalIP() {
    string result;
    WSAData wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    char name[256];
    int getNameRet = gethostname(name, sizeof(name));
    printf("getNameRet:%d\n", getNameRet);
    hostent *host = gethostbyname(name);
    if (NULL == host) {
        return string();
    }
    in_addr *pAddr = (in_addr *) *host->h_addr_list;
    for (int i = 0; i < (strlen((char *) *host->h_addr_list) - strlen(host->h_name)) / 4 && pAddr; i++) {
        string addr = inet_ntoa(pAddr[i]);
        cout << addr.c_str() << endl;
    }
    return result;

}

string NetWorldUtils::getHostNameIP(string hostname) {
    WSAData wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
    hostent *phst = gethostbyname(hostname.c_str());
    in_addr *iddr = (in_addr *) phst->h_addr;
//    unsigned long IPUL = iddr->s_addr;
    string IP = inet_ntoa(*iddr);
    return IP;
}
