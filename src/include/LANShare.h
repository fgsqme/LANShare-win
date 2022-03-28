//
// Created by Administrator on 2022/3/9 0009.
//

#ifndef LANSHARE_LANSHARE_H
#define LANSHARE_LANSHARE_H

#include "UDPServer.h"
#include "TCPClient.h"
#include "Device.h"
#include <list>
#include <map>

// ������ͨѶ����
#define UDP_GET_DEVICES  1001       // ��ȡ�豸
#define UDP_SET_DEVICES  1002       // �����豸
#define UDP_DEVICES_OFF_LINE 1003   // �豸����
#define UDP_DEVICES_MESSAGE  1004    // �㲥��Ϣ
#define UDP_DEVICES_MESSAGE_TO_CLIPBOARD  1005  // �㲥��Ϣ�����а�
// �ļ���������
#define FS_SHARE_FILE  1101    // �����ļ�
#define FS_AGREE  1102         // ͬ��
#define FS_NOT_AGREE  1103     // ��ͬ��

#define FS_DATA  1            // ����
#define FS_END  2            // ���ս���
#define FS_CLOSE  3           // ȡ��

// Service ��������
#define SERVICE_IF_RECIVE_FILES  1201    // �Ƿ�����ļ�
#define SERVICE_SHOW_PROGRESS  1202      // ��ʾ�ļ����ȿ�
#define SERVICE_PROGRESS  1203           // �ļ�����
#define SERVICE_CLOSE_PROGRESS  1204     // �ر��ļ����ȿ�
#define SERVICE_UPDATE_DEVICES  1205     // �����豸�б�

// Ĭ�϶˿�
#define DEFAULT_UDPPORT 4573
#define DEFAULT_TCPPORT 5856

struct MFile {
    string fileName;
    mlong fileSize;
};


class LANShare {

public:
    // �������ߵ��豸
    map <string, Device> onLineDevices;
    // �Լ��豸��Ϣ
    Device *mDevice;
    bool isRun = true;
    UDPServer *server;

    Device *getMDevice() const;

    LANShare();

    ~LANShare();

    static void runRecive(LANShare *lanShare);

    static void createTcpServer();

    static void scannDevice(LANShare *lanShare);

    static void handelFile(TCPClient *client);

    void broadcastMessage(Device *device, string message,bool isClip);
};

#endif //LANSHARE_LANSHARE_H
