//
// Created by Administrator on 2022/3/10 0010.
//

#ifndef LANSHARE_WIN_DEVICE_H
#define LANSHARE_WIN_DEVICE_H

#include <string>

using namespace std;

class Device {
public:
    static const int UNKNOW = -1;
    static const int ANDROID = 1;
    static const int WIN = 2;
    static const int LINUX = 3;
    static const int MAC = 4;
    static const int IOS = 5;
private:
    string devName; // 设备名称
    string devIP;   // 设备TCP接收文件IP
    int devPort;    // 设备TCP接收文件端口
    int devMode;    // 设备代号
    long setTime;   // 最后心跳时间
public:


    const string &getDevName() const;

    void setDevName(const string &devName);

    const string &getDevIp() const;

    void setDevIp(const string &devIp);

    int getDevPort() const;

    void setDevPort(int devPort);

    int getDevMode() const;

    void setDevMode(int devMode);

    long getSetTime() const;

    void setSetTime(long setTime);
};


#endif //LANSHARE_WIN_DEVICE_H
