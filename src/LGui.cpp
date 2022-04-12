//
// Created by fgsq on 2022/4/9.
//

#include "LGui.h"
#include "LANShare.h"
#include <windows.h>
#include <tchar.h>
#include <cstdio>
#include <thread>

#define SEND_BUTTON_ID  501
#define ON_LINE_USER    502
#define MESSAGE_BOX     503
#define EDIT_BOX        504


using namespace std;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// http://www.yfvb.com/help/win32sdk/ 文档
//1 设计窗口类
//2 注册窗口类
//3 创建窗口类
//4 显示窗口
//5 更新窗口
//6 消息循环
TCHAR szAppName[] = TEXT ("fastWindows");

HINSTANCE appInstance;
HWND hwnd;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInsrance, LPSTR lpCmdLine, int nCmdShow) {




    appInstance = hInstance;

    WNDCLASS wc;
    wc.style = CS_HREDRAW | CS_VREDRAW;  // 窗口类的风格
    wc.lpfnWndProc = WindowProc;         // 窗口处理函数
    wc.cbClsExtra = 0;                   // 窗口类额外空间内存大小
    wc.cbWndExtra = 0;                   // 床楼额外空间内存大小
    wc.hInstance = hInstance;           // 当前应用程序实例句柄
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION); // 加载系统图标
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);  // 光标颜色
//    wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));           // 设置背景
    wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);

    wc.lpszClassName = szAppName;


    if (RegisterClass(&wc) == FALSE) {
        MessageBox(nullptr, TEXT("Hello World"), TEXT("注册失败"), MB_ERR_INVALID_CHARS);
        return 0;
    }
    hwnd = CreateWindow(
            szAppName,                                                             //窗口名
            "LANShare",                                                          // 窗口标题
            WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SIZEBOX,  // 窗口风格
            200, // 窗口横坐标
            200, // 窗口纵坐标
            800, // 窗口宽
            610, // 窗口高
            nullptr, // 父窗口句柄
            nullptr, // 菜单句柄
            hInstance,// 当前应用程序句柄
            nullptr // 附加参数
    );
    HICON hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM) hIcon);


    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    LANShare lanShare;
    // TCP 文件接收线程
    thread tTcpServer(LANShare::createTcpServer);
    // UDP 接收命令线程
    thread tRunRecive(LANShare::runRecive, &lanShare,&hwnd);
    // 扫描设备线程
    thread tScannDevice(LANShare::scannDevice, &lanShare);


//    SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
//    SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);


    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        // 将虚拟键消息转换为字符消息
        TranslateMessage(&msg);
        // 将消息转换为窗口处理函数
        DispatchMessage(&msg);
    }

    return 0;
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    switch (uMsg) {
        case WM_CREATE:

            // 创建在线用户窗口
            CreateWindow(TEXT("static"),
                         "在线用户",
                         WS_VISIBLE | WS_CHILD,
                         600,//列表x坐标
                         0,//列表y坐标
                         180,//列表宽
                         250,//高度
                         hwnd,
                         (HMENU) ON_LINE_USER,
                         appInstance, nullptr);

//            SetWindowText(GetDlgItem(hwnd, ON_LINE_USER), "listu");
//            SetWindowText(GetDlgItem(hwnd, ON_LINE_USER), "");

            CreateWindow(TEXT("listbox"),
                         "消息列表",
                         LBS_NOTIFY | WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL,
                         30,
                         20,
                         550,
                         380,
                         hwnd,
                         (HMENU) MESSAGE_BOX,
                         appInstance, NULL);


            CreateWindow(TEXT("edit"), NULL,
                         WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_BORDER | ES_LEFT | ES_MULTILINE |
                         ES_AUTOHSCROLL | ES_AUTOVSCROLL,
                         30,
                         420,
                         570,
                         90,
                         hwnd,
                         (HMENU) EDIT_BOX,
                         appInstance, NULL);


            CreateWindow(TEXT("Button"),//Button是预定义窗体类
                         TEXT("发送1"),
                         WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                         500,
                         510,
                         80,
                         25,
                         hwnd,
                         (HMENU) SEND_BUTTON_ID,
                         appInstance, NULL);

            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}