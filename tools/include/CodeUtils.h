//
// Created by Administrator on 2022/3/20 0020.
//

#ifndef LANSHARE_WIN_CODEUTILS_H
#define LANSHARE_WIN_CODEUTILS_H

#include <string>
#include <windows.h>
#include "Type.h"

using namespace std;

class CodeUtils {
public:
    // utf8×ªgbk
    static string UTFToGBK(const char *srcStr);

    // gbk×ªutf-8
    static string Gbk2Utf8(const char *gbkStr);

    // ×Ö·û×ª¿í×Ö·û
    static wstring CharToWchar(const char *c, size_t m_encode = CP_ACP);

    // ¿í×Ö·û×ª×Ö·û
    static string WcharToChar(const wchar_t *wp, size_t m_encode = CP_ACP);

    static int getGbkStrLen(const char *str);

    static int getUtf8StrLen(const char *str);
};


#endif //LANSHARE_WIN_CODEUTILS_H
