//
// Created by root on 2021/5/10.
//

#include "Type.h"
#include <string>

#ifndef WZ_CHEAT_DATAENC_H
#define WZ_CHEAT_DATAENC_H

using namespace std;

class DataEnc {
private:
    static const int HEADER_LEN = 12;//ͷ����

    mbyte *m_bytes;
    int index = HEADER_LEN;

    int m_byteLen = 0;

public:
    DataEnc();

    DataEnc(mbyte *bytes, int bytelen);

    void setData(mbyte *bytes, int bytelen);

    void setCmd(int cmd);

    void setByteCmd(mbyte cmd);

    void setCount(int count);

    void setLength(int len);


    DataEnc &putInt(int val);                 //�����ݰ����int
    DataEnc &putLong(mlong val);              //�����ݰ����long
    DataEnc &putByte(mbyte val);              //�����ݰ����byte
    DataEnc &putBool(bool val);              //�����ݰ����bool
    DataEnc &putFloat(float val);             //�����ݰ����flaot
    DataEnc &putDouble(double val);           //�����ݰ����double
    DataEnc &putStr(const char *str, int len);       //�����ݰ�����ַ�
    DataEnc &putStr(const char *str);       //�����ݰ�����ַ�
    DataEnc &putString(const string &str);       //�����ݰ�����ַ�

    DataEnc &putInt(int val, int i);                 //�����ݰ����int
    DataEnc &putLong(mlong val, int i);              //�����ݰ����long
    DataEnc &putByte(mbyte val, int i);              //�����ݰ����byte
    DataEnc &putFloat(float val, int i);             //�����ݰ����flaot
    DataEnc &putDouble(double val, int i);           //�����ݰ����double
    DataEnc &putStr(const char *str, int len, int i);       //�����ݰ�����ַ�

    int getDataLen();

    mbyte *getData();

    void reset();

    static int headerSize();

    int getDataIndex() const;

    void setDataIndex(int i);
};


#endif //WZ_CHEAT_DATAENC_H
