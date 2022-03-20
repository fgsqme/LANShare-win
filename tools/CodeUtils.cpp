//
// Created by Administrator on 2022/3/20 0020.
//

#include "CodeUtils.h"
#include <windows.h>

char *CodeUtils::UTFToGBK(const char *utf8) {
    int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, nullptr, 0);
    auto *wstr = new wchar_t[len + 1];
    memset(wstr, 0, len + 1);
    MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
    len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
    char *str = new char[len + 1];
    memset(str, 0, len + 1);
    WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, nullptr, nullptr);
    if (wstr) delete[] wstr;
    return str;
}

char *CodeUtils::Gbk2Utf8(const char *gbkStr) {
    int len = MultiByteToWideChar(CP_ACP, 0, gbkStr, -1, nullptr, 0);
    WCHAR *wstr = new WCHAR[len];
    MultiByteToWideChar(CP_ACP, 0, gbkStr, -1, wstr, len);
    len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
    char *str = new char[len];
    memset(str, 0, len + 1);
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, nullptr, nullptr);
    if (wstr) delete[] wstr;
    return str;
}
