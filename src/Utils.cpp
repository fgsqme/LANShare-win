//
// Created by Administrator on 2022/3/21 0021.
//

#include "Utils.h"
#include <windows.h>

bool Utils::SetClipboardText(const char *str) {
    if (::OpenClipboard(nullptr)) {
        ::EmptyClipboard();
        HGLOBAL clipbuffer;
        char *buffer;
        clipbuffer = ::GlobalAlloc(GMEM_DDESHARE, strlen(str) + 1);
        buffer = (char *) ::GlobalLock(clipbuffer);
        strcpy(buffer, str);
        ::GlobalUnlock(clipbuffer);
        ::SetClipboardData(CF_TEXT, clipbuffer);
        ::CloseClipboard();
        return true;
    }
    return false;
}
