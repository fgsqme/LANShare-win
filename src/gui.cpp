#include <windows.h>
#include <iostream>
#include <sys/stat.h>
#include <shellapi.h>
#include "CodeUtils.h"

using namespace std;

//��ʾ��Ϣ
void show(string str);

//��ȡ���а�����
string getPlateStr();

//�����ļ�·����ȡ�����ļ��е�·��
string getFileDir(string path);

//�ж��Ƿ�Ϊ�ļ�
bool isFile(string path);

//�ж��Ƿ�Ϊ�ļ���
bool isDir(string path);

//���г����·��
void execute(string s);


int WINAPI WinMain(
        HINSTANCE hInstance,       //����ǰʵ���ľ�����Ժ���ʱ������GetModuleHandle(0)�����
        HINSTANCE hPrevInstance,   //���������Win32����������0���Ѿ�����������
        char *lpCmdLine,          //ָ����/0��β�������У�������EXE������ļ�����
        //�Ժ���ʱ������GetCommandLine()����ȡ������������
        int nCmdShow               //ָ��Ӧ����ʲô��ʽ��ʾ������
) {
    string plateStr = getPlateStr();
    show(plateStr);
    if (isDir(plateStr)) {
        execute(plateStr);
    }
    if (isFile(plateStr)) {
        execute(getFileDir(plateStr));
    }
    return 0;
}

//��ʾ��Ϣ
void show(string str) {
    MessageBox(nullptr, str.c_str(), "", MB_OK);
}

//�ж��Ƿ�Ϊ�ļ���
bool isDir(string path) {
    struct _stat buf = {0};
    _stat(path.c_str(), &buf);
    return buf.st_mode & _S_IFDIR;
}

//�ж��Ƿ�Ϊ�ļ�
bool isFile(string path) {
    struct _stat buf = {0};
    _stat(path.c_str(), &buf);
    return buf.st_mode & _S_IFREG;
}

//�����ļ�·����ȡ�����ļ��е�·��
string getFileDir(string path) {
    int i = path.find_last_of('\\');
    std::string p2 = path.substr(0, i);
    MessageBox(nullptr, (const char *) p2.c_str(), "", MB_OK);
    return p2.c_str();
}

//��ȡ���а�����
string getPlateStr() {
    if (OpenClipboard(nullptr)) {
        if (IsClipboardFormatAvailable(CF_TEXT)) {
            HGLOBAL hGlobal = ::GetClipboardData(CF_UNICODETEXT);
            auto *pGlobal = (wchar_t *) ::GlobalLock(hGlobal);
            CloseClipboard();
            return CodeUtils::WcharToChar(pGlobal);
        }
    }
    return "";
}

//���г����·��
void execute(std::string s) {
    ShellExecute(
            nullptr,
            ("open"),
            ("Explorer.exe"),
            (s.c_str()),
            nullptr,
            SW_SHOWDEFAULT);
}