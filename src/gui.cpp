// 待开发.....

#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nShowCmd) {
    HWND hwnd; // 定义窗口句柄
    MSG msg;   // 定义一个用来存储消息的变量
    TCHAR lpszClassName[] = TEXT("windows");

    WNDCLASS wc; // 定义一个窗口类变量
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = ::LoadIcon(nullptr, IDI_APPLICATION);
    wc.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) ::GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = lpszClassName;

    ::RegisterClass(&wc);                 // 注册窗口

    hwnd = CreateWindow(lpszClassName,    // 创建窗口
                        TEXT("win"),
                        WS_OVERLAPPEDWINDOW,
                        120, 50, 800, 600,
                        nullptr,
                        nullptr,
                        hInstance,
                        nullptr);

    ::ShowWindow(hwnd, SW_SHOWNORMAL);        // 显示窗口
    ::UpdateWindow(hwnd);

    while (::GetMessage(&msg, nullptr, 0, 0))       // 消息循环
    {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }
    return msg.wParam;
}


// 处理消息的窗口函数
LRESULT CALLBACK WndProc(HWND hwnd,
                         UINT message,
                         WPARAM wParam,
                         LPARAM lParam) {
    switch (message) {
        case WM_LBUTTONDOWN:    // 鼠标左键下消息
        {
            ::MessageBeep(0); // 可以发出声音的API函数
        }
            break;
        case WM_DESTROY:
            ::PostQuitMessage(0);
            break;
        default:
            return ::DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}