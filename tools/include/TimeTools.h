//
// Created by Administrator on 2021/8/4 0004.
//

#ifndef EW_TIMETOOLS_H
#define EW_TIMETOOLS_H


#include "Type.h"

class TimeTools {
public:
    static void getFormatTime(char *str_time);
    static void sleep_s(int s);               //������ʱ
    static void sleep_ms(int ms);               //������ʱ
    static void sleep_us(int us);               //΢����ʱ
    static mlong getCurrentTime();           //��ȡϵͳʱ��
};


#endif //EW_TIMETOOLS_H
