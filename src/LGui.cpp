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

// http://www.yfvb.com/help/win32sdk/ �ĵ�
//1 ��ƴ�����
//2 ע�ᴰ����
//3 ����������
//4 ��ʾ����
//5 ���´���
//6 ��Ϣѭ��
TCHAR szAppName[] = TEXT ("fastWindows");

HINSTANCE appInstance;
HWND hwnd;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInsrance, LPSTR lpCmdLine, int nCmdShow) {




    appInstance = hInstance;

    WNDCLASS wc;
    wc.style = CS_HREDRAW | CS_VREDRAW;  // ������ķ��
    wc.lpfnWndProc = WindowProc;         // ���ڴ�����
    wc.cbClsExtra = 0;                   // ���������ռ��ڴ��С
    wc.cbWndExtra = 0;                   // ��¥����ռ��ڴ��С
    wc.hInstance = hInstance;           // ��ǰӦ�ó���ʵ�����
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION); // ����ϵͳͼ��
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);  // �����ɫ
//    wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));           // ���ñ���
    wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);

    wc.lpszClassName = szAppName;


    if (RegisterClass(&wc) == FALSE) {
        MessageBox(nullptr, TEXT("Hello World"), TEXT("ע��ʧ��"), MB_ERR_INVALID_CHARS);
        return 0;
    }
    hwnd = CreateWindow(
            szAppName,                                                             //������
            "LANShare",                                                          // ���ڱ���
            WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SIZEBOX,  // ���ڷ��
            200, // ���ں�����
            200, // ����������
            800, // ���ڿ�
            610, // ���ڸ�
            nullptr, // �����ھ��
            nullptr, // �˵����
            hInstance,// ��ǰӦ�ó�����
            nullptr // ���Ӳ���
    );
    HICON hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM) hIcon);


    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    LANShare lanShare;
    // TCP �ļ������߳�
    thread tTcpServer(LANShare::createTcpServer);
    // UDP ���������߳�
    thread tRunRecive(LANShare::runRecive, &lanShare,&hwnd);
    // ɨ���豸�߳�
    thread tScannDevice(LANShare::scannDevice, &lanShare);


//    SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
//    SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);


    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        // ���������Ϣת��Ϊ�ַ���Ϣ
        TranslateMessage(&msg);
        // ����Ϣת��Ϊ���ڴ�����
        DispatchMessage(&msg);
    }

    return 0;
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    switch (uMsg) {
        case WM_CREATE:

            // ���������û�����
            CreateWindow(TEXT("static"),
                         "�����û�",
                         WS_VISIBLE | WS_CHILD,
                         600,//�б�x����
                         0,//�б�y����
                         180,//�б��
                         250,//�߶�
                         hwnd,
                         (HMENU) ON_LINE_USER,
                         appInstance, nullptr);

//            SetWindowText(GetDlgItem(hwnd, ON_LINE_USER), "listu");
//            SetWindowText(GetDlgItem(hwnd, ON_LINE_USER), "");

            CreateWindow(TEXT("listbox"),
                         "��Ϣ�б�",
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


            CreateWindow(TEXT("Button"),//Button��Ԥ���崰����
                         TEXT("����1"),
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