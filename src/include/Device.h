//
// Created by Administrator on 2022/3/10 0010.
//

#ifndef LANSHARE_WIN_DEVICE_H
#define LANSHARE_WIN_DEVICE_H

#include <string>
#include "Type.h"

using namespace std;

class Device {
public:
    static const int L_UNKNOW = -1;
    static const int L_ANDROID = 1;
    static const int L_WIN = 2;
    static const int L_LINUX = 3;
    static const int L_MAC = 4;
    static const int L_IOS = 5;
private:
    string devName; // �豸����
    string devIP;   // �豸TCP�����ļ�IP
    int devPort;    // �豸TCP�����ļ��˿�
    int devMode;    // �豸����
    mlong setTime;   // �������ʱ��
public:


    const string &getDevName() const;

    void setDevName(const string &devName);

    const string &getDevIp() const;

    void setDevIp(const string &devIp);

    int getDevPort() const;

    void setDevPort(int devPort);

    int getDevMode() const;

    void setDevMode(int devMode);

    mlong getSetTime() const;

    void setSetTime(mlong setTime);
};


#endif //LANSHARE_WIN_DEVICE_H
