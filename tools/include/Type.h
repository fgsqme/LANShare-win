#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(_WIN32_) || defined(WIN64) || defined(_WIN64) || defined(_WIN64_)
#define PLATFORM_WINDOWS 1 //Windows平台
#define PATH_E '\\'

#include <direct.h>

#elif defined(ANDROID) || defined(_ANDROID_)
#define PATH_E '/'
#include <sys/stat.h>
#include <unistd.h>
#define PLATFORM_ANDROID 1 //Android平台
#define PATH_E '/'
#elif defined(__linux__)
#define PATH_E '/'
#define PLATFORM_LINUX	 1 //Linux平台
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#else
#define PLATFORM_UNKNOWN 1
#endif

typedef signed char mbyte;
typedef long long mlong;       //long 8
typedef unsigned long ulong;  //unsig long 4/8
typedef ulong Addr;  //unsig long 4/8
typedef long Offset;  //unsig long 4/8
typedef double mdouble;       //double 8
typedef float mfloat;         //float 4
typedef unsigned int uint;
typedef int TYPE;
typedef unsigned char boolean;
typedef unsigned char uchar;
typedef unsigned int CharType;
typedef unsigned char UTF8;
typedef unsigned short UTF16;
typedef unsigned int UTF32;

typedef union {
    mlong bits;
    double d;
} Double;

typedef union {
    unsigned int bits;
    float f;
} Float;


// 3D结构体
struct C3D {
    float x;
    float y;
    float z;
};

// 2D结构体
struct C2D {
    float x;
    float y;
    float w;
    float h;
};

struct RADDR {
    Addr addr;                    // 起始地址
    Addr taddr;                   // 结束地址
};



