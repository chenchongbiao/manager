#ifndef DBUSCLIENT_H
#define DBUSCLIENT_H

#include <QString>
#include <QVariant>
#include <QDBusMessage>
/**
 * @brief The DBusClient class
 * 将调用的dbus的函数封装起来。
 */
class DBusClient
{
public:
    static QByteArray GetImageList();                                           // 获取所有镜像
    static QByteArray SearchImageByName(QString imgName);                       // 通过镜像名搜索镜像


    static QByteArray SearchContainerByName(QString containerName);             // 通过容器名搜索镜像
    static bool StarContainerById(QString containerId);                         // 通过id启动容器
    static bool StopContainerById(QString containerId);                         // 通过id停止容器
    static bool CreateContainer(QString name,QString image,QList<QString> cmd,\
                                QList<QString> ports,QMap<QString,QVariant> volume,\
                                bool tty,bool openStdin);                       // 创建容器
    static bool RmContainerById(QString containerId);                           // 通过id删除容器
    static QByteArray GetNetworkList();                                         // 获取所有网络


    static QDBusMessage ContainerMessage(const QString methodName);             // 构造一个容器的QDBusMessage，传入方法名
    static QDBusMessage ImageMessage(const QString methodName);                 // 构造一个镜像的QDBusMessage，传入方法名
    static QDBusMessage NetworkMessage(const QString methodName);               // 构造一个网络的QDBusMessage，传入方法名
    static QDBusMessage VolumeMessage(const QString methodName);                // 构造一个存储卷的QDBusMessage，传入方法名

    // 容器
    static QByteArray GetContainerList(QMap<QString,QVariant> args);            // 获取所有容器,传入参数容器名，如果不为空搜索容器获取列表
    static bool StartContainer(QList<QString> ids);                             // 运行容器 传入的是个字符串 列表
    static bool StopContainer(QList<QString> ids);                              // 停止容器 传入的是个字符串 列表
    static bool  RestartContainer(QList<QString> ids);                          // 重启容器 传入的是个字符串 列表

    // 镜像
    static QByteArray SearchImageFromHub(const QString imgName);                // 从镜像仓库搜索镜像
    static bool PullImage(const QString imgName);                               // 从镜像仓库拉取镜像
    static bool RmImage(const QList<QString> ids);                              // 删除镜像

    // 网络
    static QByteArray GetNetworkList(QMap<QString,QVariant> args);              // 获取网络列表

    // 存储卷
    static QByteArray GetVolumeList(QMap<QString,QVariant> args);               // 获取所有存储卷
};

#endif // DBUSCLIENT_H
