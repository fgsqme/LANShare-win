//
// Created by NotAdmin on 2021/9/19.
//

#ifndef EP_IOUTILS_H
#define EP_IOUTILS_H

#include  <string>
#include  "Type.h"
#include  "IOInter.h"

using namespace std;


class IOUtils : public IOInter {
private:
    FILE *file_fd = nullptr;
    const char *file_path;
    mlong file_seek = 0;
public:
    IOUtils(const char *path, const char *flags = "wb+");

    ~IOUtils();

    bool isOpen();

    mlong setSeek(int64_t off);

    mlong getSeek();

    int read(void *buff, int len);

    int write(const char *buff, int len);

    int write(const char *buff,int index, int len);

    int64_t getFileSize();

    static int64_t getFileSize(const char *path);

    void close();
};


#endif //EP_IOUTILS_H
