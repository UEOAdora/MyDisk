#ifndef COMMON_H
#define COMMON_H

#include <QString>

struct FileInfo {
    FileInfo(): fileid(0), size(0), pfile(nullptr), pos(0), isPause(0){

    }
    int fileid;
    QString name;
    QString dir;
    QString time;
    int size;
    QString md5;
    QString type;
    QString absolutePath;

    int pos;//文件指针位置
    int isPause;//是否暂停
    //文件指针
    FILE * pfile;

    static QString getSize(int size) {
        //看能被1024 除几次 0次 字节 1次 KB 2次 MB 3次 GB
        int tmp = size;
        int count = 0;
        while (tmp != 0) {
            tmp /= 1024;
            if (tmp != 0) {
                count++;
            }
        }
        switch (count)
        {
        case 0:
            return QString::number(size) + "B";
            break;
        case 1:
            return QString::number(size / 1024) + "KB";
            break;
        case 2://计算至小数点后一位
            return QString::number(size / 1024 / 1024) + "." + QString::number((size / 1024 / 1024) % 10) + "MB";
            break;
        case 3://计算至小数点后一位
            return QString::number(size / 1024 / 1024 / 1024) + "." + QString::number((size / 1024 / 1024 / 1024) % 10) + "GB";
            break;
        default:
            return QString::number(size / 1024 / 1024 / 1024) + "." + QString::number((size / 1024 / 1024 / 1024) % 10) + "GB";
            break;
        }
    }
};
#endif // COMMON_H

