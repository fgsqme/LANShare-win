//
// Created by Administrator on 2022/3/9 0009.
//

#ifndef LANSHARE_NETWORLDTOOLS_H
#define LANSHARE_NETWORLDTOOLS_H

#include <string>

using namespace std;

class NetWorldUtils {
public:
    // 获取本机IP
    static string getLocalIP();

    static string getHostNameIP(string hostname);
};


#endif //LANSHARE_NETWORLDTOOLS_H
