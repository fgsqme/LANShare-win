//
// Created by NotAdmin on 2021/9/19.
//

#include "IOUtils.h"
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

IOUtils::~IOUtils() {
    close();
}


IOUtils::IOUtils(const char *path, const char *flags) {
    file_path = path;
    file_fd = fopen(path, flags);
}

mlong IOUtils::setSeek(off64_t off) {
    if (fseeko(file_fd, off, SEEK_SET) == 0) {
        return file_seek = off;
    }
    return -1;
}

mlong IOUtils::getSeek() {
    return file_seek;
}

int IOUtils::read(void *buff, int len) {
    if (len <= 0) {
        puts("read len < 0");
        return -3;
    }
    size_t ten = ::fread(buff, 1, len, file_fd);
    if (ten > 0) {
        file_seek += ten;
    }
    return ten;
}

int IOUtils::write(const char *buff, int len) {
    return write(buff, 0, len);
}

int IOUtils::write(const char *buff, int index, int len) {

    if (len <= 0) {
        puts("write len < 0");
        return -3;
    }
    int ten = (int) ::fwrite(&buff[index], 1, len, file_fd);
    if (ten > 0) {
        file_seek += ten;
    }
    return ten;
}


void IOUtils::close() {
    ::fclose(file_fd);
}

int64_t IOUtils::getFileSize() {
    return getFileSize(file_path);
}

int64_t IOUtils::getFileSize(const char *path) {
    struct stat buf{};
    if (stat(path, &buf) < 0) {
        return 0;
    }
    return buf.st_size;
}

bool IOUtils::isOpen() {
    return file_fd != nullptr;
}




