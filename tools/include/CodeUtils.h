//
// Created by Administrator on 2022/3/20 0020.
//

#ifndef LANSHARE_WIN_CODEUTILS_H
#define LANSHARE_WIN_CODEUTILS_H

#include <string>
#include "Type.h"

using namespace std;

class CodeUtils {
public:
    static char *UTFToGBK(const char *srcStr);

    static char *Gbk2Utf8(const char *gbkStr);
};


#endif //LANSHARE_WIN_CODEUTILS_H
