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
    // TCP �ļ������߳�
    thread tTcpServer(LANShare::createTcpServer);
    // UDP ���������߳�
    thread tRunRecive(LANShare::runRecive, &lanShare, (HWND *) nullptr);
    // ɨ���豸�߳�
    thread tScannDevice(LANShare::scannDevice, &lanShare);
    char buffer[2048];

    sleep(1);

    while (true) {
        cout << "��������Ϣ:";
        if (gets(buffer) != nullptr) {
            if (strcmp(buffer, "exit") == 0) {
                break;
            }
            string str = CodeUtils::Gbk2Utf8(buffer);
            lanShare.broadcastMessage(nullptr, str, false);
        }
    }
    return 0;
}
