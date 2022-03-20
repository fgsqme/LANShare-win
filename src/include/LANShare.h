//
// Created by Administrator on 2022/3/9 0009.
//

#ifndef LANSHARE_LANSHARE_H
#define LANSHARE_LANSHARE_H

#include "TCPClient.h"
#include "Device.h"
#include <list>
#include <map>

// 局域网通讯命令
#define UDP_GET_DEVICES  1001       // 获取设备
#define UDP_SET_DEVICES  1002       // 设置设备
#define UDP_DEVICES_OFF_LINE 1003   // 设备下线
#define UDP_DEVICES_MESSAGE  1004    // 广播消息

// 文件服务命令
#define FS_SHARE_FILE  1101    // 发送文件
#define FS_AGREE  1102         // 同意
#define FS_NOT_AGREE  1103     // 不同意

#define FS_DATA  1            // 数据
#define FS_END  2            // 接收结束
#define FS_CLOSE  3           // 取消

// Service 连接命令
#define SERVICE_IF_RECIVE_FILES  1201    // 是否接收文件
#define SERVICE_SHOW_PROGRESS  1202      // 显示文件进度框
#define SERVICE_PROGRESS  1203           // 文件进度
#define SERVICE_CLOSE_PROGRESS  1204     // 关闭文件进度框
#define SERVICE_UPDATE_DEVICES  1205     // 更新设备列表

// 默认端口
#define DEFAULT_UDPPORT 4573
#define DEFAULT_TCPPORT 5856

struct MFile {
    string fileName;
    mlong fileSize;
};


class LANShare {

public:
    // 保存在线的设备
    map <string, Device> onLineDevices;
    // 自己设备信息
    Device *mDevice;
    bool isRun = true;

    Device *getMDevice() const;

    LANShare();

    ~LANShare();

    static void runRecive(LANShare *lanShare);

    static void createTcpServer();

    static void scannDevice(LANShare *lanShare);

    static void handelFile(TCPClient *client);
};

#endif //LANSHARE_LANSHARE_H
