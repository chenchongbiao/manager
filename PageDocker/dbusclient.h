#ifndef DBUSCLIENT_H
#define DBUSCLIENT_H

#include <QString>
/**
 * @brief The DBusClient class
 * 将调用的dbus的函数封装起来。
 */
class DBusClient
{
public:
    static QByteArray SearchImageByName(QString imgName);  // 通过镜像名搜索镜像
};

#endif // DBUSCLIENT_H
