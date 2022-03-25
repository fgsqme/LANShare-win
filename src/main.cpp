//
// Created by Administrator on 2022/3/10 0010.
//

#include "main.h"
#include "LANShare.h"
#include "CodeUtils.h"
#include <thread>
#include <iostream>

using namespace std;


int main() {
    LANShare lanShare;
    // TCP 文件接收线程
    thread tTcpServer(LANShare::createTcpServer);
    // UDP 接收命令线程
    thread tRunRecive(LANShare::runRecive, &lanShare);
    // 扫描设备线程
    thread tScannDevice(LANShare::scannDevice, &lanShare);
    char buffer[2048];

    sleep(1);

    while (true) {
        cout << "请输入消息:";
        if (gets(buffer) != nullptr) {
            if (strcmp(buffer, "exit") == 0) {
                break;
            }
        }
    }
            string str = CodeUtils::Gbk2Utf8(buffer);
            lanShare.broadcastMessage(nullptr, str, false);

    return 0;
}
