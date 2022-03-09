#include <iostream>
#include <list>
#include <thread>
#include "DataDec.h"
#include "DataEnc.h"
#include "UDPServer.h"
#include "TCPServer.h"
#include "LANShare.h"
#include "IOUtils.h"
#include "NetWorldUtils.h"

#define BUFF_SIZE 1024 * 1024 * 2
using namespace std;

struct MFile {
    string fileName;
    mlong fileSize;
};

void *handelFile(void *data) {
    TCPClient *client = static_cast<TCPClient *>(data);
    mbyte *buffer = new mbyte[BUFF_SIZE];

    if (client->recvo(buffer, DataEnc::headerSize()) != DataEnc::headerSize()) return nullptr;

    DataDec dataDec(buffer, BUFF_SIZE);

    int cmd = dataDec.getCmd();

    if (cmd == FS_SHARE_FILE) {
        int count = dataDec.getCount();
        int length = dataDec.getLength();
        if (client->recvo(buffer, DataEnc::headerSize(), length, 0) != length) return nullptr;
        dataDec.setData(buffer, DataEnc::headerSize() + length);

        int port = dataDec.getInt();
        char *ip = dataDec.getStr();
        char *name = dataDec.getStr();

        printf("ip:%s:%d name:%s\n", ip, port, name);

        list<MFile> files;

        for (int i = 0; i < count; i++) {
            if (client->recvo(buffer, 0, DataEnc::headerSize(), 0) != DataEnc::headerSize()) return nullptr;
            length = dataDec.getLength();
            if (client->recvo(buffer, DataEnc::headerSize(), length, 0) != length) return nullptr;
            dataDec.setData(buffer, DataEnc::headerSize() + length);

            long fileSize = dataDec.getLong();
            // 文件名称
            char *fileName = dataDec.getStr();

            printf("fileName:%s fileSize:%ld\n", fileName, fileSize);

            MFile mFile{fileName, fileSize};
            files.push_back(mFile);

            delete fileName;
        }

        DataEnc dataEnc(buffer, BUFF_SIZE);
        dataEnc.setCmd(FS_AGREE);
        client->send(dataEnc.getData(), dataEnc.getDataLen());

        // 需要手动创建文件夹
        string path = "D:\\LANShare\\";


        list<MFile>::iterator iterator;
        for (iterator = files.begin(); iterator != files.end(); ++iterator) {
            string newPath = path + iterator->fileName;
            printf("recv fileName%s fileSize:%lld\n", iterator->fileName.c_str(), iterator->fileSize);
            IOUtils fileIO(newPath.c_str());
            mlong totalRecv = 0;
            int p = 0;
            while (true) {
                if (client->recvo(buffer, 0, DataEnc::headerSize(), 0) != DataEnc::headerSize()) break;
                dataDec.setData(buffer, BUFF_SIZE);

                mbyte rCmd = dataDec.getByteCmd();

                if (rCmd == FS_DATA) {
                    length = dataDec.getLength();
                    if (client->recvo(buffer, DataEnc::headerSize(), length, 0) != length) return nullptr;
                    int rel = fileIO.write((char *) buffer,DataEnc::headerSize(), length);
//                    int rel = length;
                    totalRecv += rel;
                    int progeress = (int) (totalRecv * 100.0F / iterator->fileSize);
                    if (p != progeress) {
                        printf("prngeress:%d\n", progeress);
                        p = progeress;
                    }
                } else if (rCmd == FS_END) {
                    break;
                } else {  // 关闭传输
                    totalRecv = 0;
                    break;
                }
            }
            fileIO.close();

            if (totalRecv != iterator->fileSize) {
                puts("recv fail");
            } else {
                puts("recv sucess");
            }

        }
    }
    client->close();
    return nullptr;
}

void createTcpServer() {
    TCPServer tcpServer(DEFAULT_TCPPORT);
    while (true) {
        TCPClient *client = tcpServer.accept();
        puts("tcp client connectd");
        pthread_t newClient;
        pthread_create(&newClient, nullptr, handelFile, client);
    }

}

int main() {
    thread t(createTcpServer);
//    string ip = NetWorldUtils::getLocalIP();
//    cout << ip << endl;
    UDPServer server(DEFAULT_UDPPORT);
    mbyte *buffer = new mbyte[2048];
    sockaddr_in clientAddr;
    while (true) {
        int len = server.recv(&clientAddr, buffer, 2048);
        DataDec dataDec(buffer, len);

        int cmd = dataDec.getCmd();


        if (cmd == UDP_SET_DEVICES) {
            int port = dataDec.getInt();
            char *ip = dataDec.getStr();
            char *devName = dataDec.getStr();
            int devModel = dataDec.getInt();

            printf("device on line ip:%s:%d devName:%s devModel:%d\n", ip, port, devName, devModel);

            delete ip;
            delete devName;
        } else if (cmd == UDP_GET_DEVICES) {
            char *ip = dataDec.getStr();
//            printf("recv ip:%s\n", ip);
            DataEnc dataEnc(buffer, 2048);
            dataEnc.setCmd(UDP_SET_DEVICES);
            dataEnc.putInt(DEFAULT_TCPPORT);
            // 此处要手动输入Win IP 应为暂时还没有实现获取Win IP 的方法
            dataEnc.putStr("192.168.31.231");
            dataEnc.putStr("Win Test Client");
            dataEnc.putInt(1);

            struct sockaddr_in clientAddr1;
            clientAddr1.sin_family = AF_INET;
            clientAddr1.sin_port = htons(DEFAULT_UDPPORT);
            clientAddr1.sin_addr.S_un.S_addr = inet_addr(ip);
//            long addr = inet_addr("127.0.0.1");
            server.send(&clientAddr1, dataEnc.getData(), dataEnc.getDataLen());

            delete ip;
        }
    }
    return 0;
}
