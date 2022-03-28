#include <windows.h>

#define ID_EDIT     1

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szAppName[] = TEXT ("���±�");

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   PSTR szCmdLine, int iCmdShow) {
    HWND hwnd;
    MSG msg;
    WNDCLASS wndclass;

    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;

    if (!RegisterClass(&wndclass)) {
        MessageBox(NULL, TEXT ("This program requires Windows NT!"),
                   szAppName, MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindowEx(WS_EX_ACCEPTFILES, szAppName, szAppName,
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          700, 500,//���ÿ�͸�
                          NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

VOID read_file(HWND hwnd, TCHAR *szFileName) {
    TCHAR *chBuffer; //������
    int file_size;
    long dwReadSize = 0; //ʵ�ʶ�ȡ�ַ���
    HWND hEdit = GetDlgItem(hwnd, ID_EDIT);
    HANDLE hFile = CreateFile(szFileName,     //�����ļ������ơ�
                              GENERIC_READ,          // ���ļ���
                              0,                      // �������д��
                              NULL,                   // ȱʡ��ȫ���ԡ�
                              OPEN_EXISTING,          // ����ļ����ڡ�
                              FILE_ATTRIBUTE_NORMAL, // һ����ļ���
                              NULL);                 // ģ���ļ�Ϊ�ա�
    if (hFile == INVALID_HANDLE_VALUE) {
        OutputDebugString(TEXT("CreateFile fail!\r\n"));
    }

    file_size = GetFileSize(hFile, NULL);
    chBuffer = (TCHAR *) malloc(file_size * sizeof(TCHAR) + 1);//�����һ�ַ����ڴ洢'\0'
    ReadFile(hFile, chBuffer, file_size, reinterpret_cast<LPDWORD>(&dwReadSize), NULL);

    chBuffer[file_size] = '\0';
    SetWindowText(hEdit, chBuffer);
    CloseHandle(hFile);
    free(chBuffer);
}

VOID OnDropFiles(HWND hwnd, HDROP hDropInfo) {
    //  UINT  nFileCount = DragQueryFile(hDropInfo, (UINT)-1, NULL, 0);  //��ѯһ����ק�˼����ļ�
    TCHAR szFileName[MAX_PATH] = TEXT("");
    DragQueryFile(hDropInfo, 0, szFileName, sizeof(szFileName));  //����ק�ĵ�һ��(�±�Ϊ0)�ļ�

    read_file(hwnd, szFileName);
    //��������ļ�������ϵͳ�ͷŻ�����
    DragFinish(hDropInfo);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    static HWND hwndEdit;

    switch (message) {
        case WM_CREATE :
            hwndEdit = CreateWindow (TEXT("edit"), NULL,
                                     WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL |
                                     WS_BORDER | ES_LEFT | ES_MULTILINE |
                                     ES_AUTOHSCROLL | ES_AUTOVSCROLL,
                                     0, 0, 0, 0, hwnd, (HMENU) ID_EDIT,
                                     ((LPCREATESTRUCT) lParam)->hInstance, NULL);
            return 0;

        case WM_SETFOCUS :
            SetFocus(hwndEdit);
            return 0;

        case WM_SIZE :
            //�����Ӵ��ڵĴ�С�븸������ͬ
            MoveWindow(hwndEdit, 0, 0, LOWORD (lParam), HIWORD (lParam), TRUE);
            return 0;

        case WM_COMMAND :
            if (LOWORD (wParam) == ID_EDIT)
                if (HIWORD (wParam) == EN_ERRSPACE || HIWORD (wParam) == EN_MAXTEXT)
                    MessageBox(hwnd, TEXT ("Edit control out of space."), szAppName, MB_OK | MB_ICONSTOP);
            return 0;
        case WM_DROPFILES:
            OnDropFiles(hwnd, (HDROP) wParam);
            return 0;
        case WM_DESTROY :
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}