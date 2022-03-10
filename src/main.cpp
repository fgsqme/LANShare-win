//
// Created by Administrator on 2022/3/10 0010.
//

#include "main.h"
#include "LANShare.h"
#include <thread>

using namespace std;

int main() {
    LANShare lanShare;
    // TCP 文件接收线程
    thread tTcpServer(LANShare::createTcpServer);
    // UDP 接收命令线程
    thread tRunRecive(LANShare::runRecive, &lanShare);
    // 扫描设备线程
//    thread tScannDevice(scannDevice);
    LANShare::scannDevice();
    return 0;
}
