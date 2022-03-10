//
// Created by Administrator on 2022/3/10 0010.
//

#include "Device.h"

const string &Device::getDevName() const {
    return devName;
}

void Device::setDevName(const string &devName) {
    Device::devName = devName;
}

const string &Device::getDevIp() const {
    return devIP;
}

void Device::setDevIp(const string &devIp) {
    devIP = devIp;
}

int Device::getDevPort() const {
    return devPort;
}

void Device::setDevPort(int devPort) {
    Device::devPort = devPort;
}

int Device::getDevMode() const {
    return devMode;
}

void Device::setDevMode(int devMode) {
    Device::devMode = devMode;
}

long Device::getSetTime() const {
    return setTime;
}

void Device::setSetTime(long setTime) {
    Device::setTime = setTime;
}
