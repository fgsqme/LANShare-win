#include <windows.h>
#include <iostream>
#include <sys/stat.h>
#include <shellapi.h>
#include "CodeUtils.h"

using namespace std;

//显示消息
void show(string str);

//获取剪切板内容
string getPlateStr();

//根据文件路径获取所在文件夹的路径
string getFileDir(string path);

//判断是否为文件
bool isFile(string path);

//判断是否为文件夹
bool isDir(string path);

//运行程序或路径
void execute(string s);


int WINAPI WinMain(
        HINSTANCE hInstance,       //程序当前实例的句柄，以后随时可以用GetModuleHandle(0)来获得
        HINSTANCE hPrevInstance,   //这个参数在Win32环境下总是0，已经废弃不用了
        char *lpCmdLine,          //指向以/0结尾的命令行，不包括EXE本身的文件名，
        //以后随时可以用GetCommandLine()来获取完整的命令行
        int nCmdShow               //指明应该以什么方式显示主窗口
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

//显示消息
void show(string str) {
    MessageBox(nullptr, str.c_str(), "", MB_OK);
}

//判断是否为文件夹
bool isDir(string path) {
    struct _stat buf = {0};
    _stat(path.c_str(), &buf);
    return buf.st_mode & _S_IFDIR;
}

//判断是否为文件
bool isFile(string path) {
    struct _stat buf = {0};
    _stat(path.c_str(), &buf);
    return buf.st_mode & _S_IFREG;
}

//根据文件路径获取所在文件夹的路径
string getFileDir(string path) {
    int i = path.find_last_of('\\');
    std::string p2 = path.substr(0, i);
    MessageBox(nullptr, (const char *) p2.c_str(), "", MB_OK);
    return p2.c_str();
}

//获取剪切板内容
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

//运行程序或路径
void execute(std::string s) {
    ShellExecute(
            nullptr,
            ("open"),
            ("Explorer.exe"),
            (s.c_str()),
            nullptr,
            SW_SHOWDEFAULT);
}