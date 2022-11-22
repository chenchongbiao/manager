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
    static QByteArray GetImageList();                                           // 获取所有镜像
    static QByteArray SearchImageByName(QString imgName);                       // 通过镜像名搜索镜像

    static QByteArray GetContainerList();                                       // 获取所有容器
    static QByteArray SearchContainerByName(QString containerName);             // 通过容器名搜索镜像
    static bool StarContainerById(QString containerId);                         // 通过id启动容器
    static bool StopContainerById(QString containerId);                         // 通过id停止容器
    static bool CreateContainer();                                              // 创建容器
};

#endif // DBUSCLIENT_H
