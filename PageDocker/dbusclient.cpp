#include <QList>
#include <QDBusConnection>
#include <QVariant>

#include "dbusclient.h"

QDBusMessage DBusClient::ContainerMessage(const QString methodName)
{
    //构造一个method_call消息，服务名称为：com.bluesky.docker.Container，对象路径为：/com/bluesky/docker/Container
    //接口名称为com.bluesky.docker.Container，method名称为为传进来的methodName
    QDBusMessage message = QDBusMessage::createMethodCall("com.bluesky.docker.Container",
                           "/com/bluesky/docker/Container",
                           "com.bluesky.docker.Container",
                           methodName);
    return message;
}

QDBusMessage DBusClient::ImageMessage(const QString methodName)
{
    //构造一个method_call消息，服务名称为：com.bluesky.docker.Image，对象路径为：/com/bluesky/docker/Image
    //接口名称为com.bluesky.docker.Image，method名称为为传进来的methodName
    QDBusMessage message = QDBusMessage::createMethodCall("com.bluesky.docker.Image",
                           "/com/bluesky/docker/Image",
                           "com.bluesky.docker.Image",
                           methodName);
    return message;
}

QDBusMessage DBusClient::VolumeMessage(const QString methodName)
{
    //构造一个method_call消息，服务名称为：com.bluesky.docker.Volume，对象路径为：/com/bluesky/docker/Volume
    //接口名称为com.bluesky.docker.Volume，method名称为为传进来的methodName
    QDBusMessage message = QDBusMessage::createMethodCall("com.bluesky.docker.Volume",
                           "/com/bluesky/docker/Volume",
                           "com.bluesky.docker.Volume",
                           methodName);
    return message;
}

QByteArray DBusClient::SearchImageByName(QString imgName) // 通过镜像名搜索镜像
{
    //构造一个method_call消息，服务名称为：com.bluesky.docker.Image，对象路径为：/com/bluesky/docker/Image
    //接口名称为com.bluesky.docker.Image，method名称为SearchImageListByName
    QDBusMessage message = QDBusMessage::createMethodCall("com.bluesky.docker.Image",
                           "/com/bluesky/docker/Image",
                           "com.bluesky.docker.Image",
                           "SearchImageListByName");
    if (!imgName.isEmpty()) {
        message << imgName ;
    }
    //发送消息
    QDBusMessage response = QDBusConnection::sessionBus().call(message);
    //判断method是否被正确返回
    if (response.type() == QDBusMessage::ReplyMessage)
    {
        //从返回参数获取返回值
        QByteArray imageArray = response.arguments().takeFirst().toString().toUtf8();
        return imageArray;
    }
    else
    {
        return "";
    }
}

QByteArray DBusClient::GetImageList()
{
    //构造一个method_call消息，服务名称为：com.bluesky.docker.Image，对象路径为：/com/bluesky/docker/Image
    //接口名称为com.bluesky.docker.Image，method名称为GetImageList
    QDBusMessage message = QDBusMessage::createMethodCall("com.bluesky.docker.Image",
                           "/com/bluesky/docker/Image",
                           "com.bluesky.docker.Image",
                           "GetImageList");
    //发送消息
    QDBusMessage response = QDBusConnection::sessionBus().call(message);
    //判断method是否被正确返回
    if (response.type() == QDBusMessage::ReplyMessage)
    {
        //从返回参数获取返回值
        QByteArray imageArray = response.arguments().takeFirst().toString().toUtf8();
        return imageArray;

    }
    else
    {
        return "";
    }
}

QByteArray DBusClient::SearchImageFromHub(const QString imgName)
{
    // 构造QDBusMessage
    QDBusMessage message = ImageMessage("SearchImage");
    if (!imgName.isEmpty()) {
        message << imgName ;
    }
    //发送消息
    QDBusMessage response = QDBusConnection::sessionBus().call(message);
    //判断method是否被正确返回
    if (response.type() == QDBusMessage::ReplyMessage)
    {
        //从返回参数获取返回值
        QByteArray imageArray = response.arguments().takeFirst().toString().toUtf8();
        return imageArray;
    }
    else
    {
        return "";
    }
}

bool DBusClient::PullImage(const QString imgName)
{
    // 构造QDBusMessage
    QDBusMessage message = ImageMessage("PullImage");
    if (!imgName.isEmpty()) {
        message << imgName ;
    }

    //发送消息
    QDBusMessage response = QDBusConnection::sessionBus().call(message);
    //判断method是否被正确返回
    if (response.type() == QDBusMessage::ReplyMessage)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool DBusClient::RmImageById(const QString imgId)
{
    // 构造QDBusMessage
    QDBusMessage message = ImageMessage("RemoveImage");
    message << imgId;
    //发送消息
    QDBusMessage response = QDBusConnection::sessionBus().call(message);
    //判断method是否被正确返回
    if (response.type() == QDBusMessage::ReplyMessage)
    {
        return true;
    }
    else
    {
        return false;
    }
}

QByteArray DBusClient::GetContainerList(QMap<QString,QVariant> args)
{
    // 构造QDBusMessage
    QDBusMessage message = ContainerMessage("GetContainerList");
    message << QVariant(args);
    //发送消息
    QDBusMessage response = QDBusConnection::sessionBus().call(message);
    //判断method是否被正确返回
    if (response.type() == QDBusMessage::ReplyMessage)
    {
        //从返回参数获取返回值
        QByteArray contaierArray = response.arguments().takeFirst().toString().toUtf8();
        return contaierArray;
    }
    else
    {
        return "";
    }
}

bool DBusClient::StartContainer(QList<QString> ids)
{
    // 构造QDBusMessage
    QDBusMessage message = ContainerMessage("StartContainer");
    message << QVariant(ids);
    //发送消息
    QDBusMessage response = QDBusConnection::sessionBus().call(message);
    //判断method是否被正确返回
    if (response.type() == QDBusMessage::ReplyMessage)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool DBusClient::StopContainer(QList<QString> ids)
{
    // 构造QDBusMessage
    QDBusMessage message = ContainerMessage("StopContainer");
    message << QVariant(ids);
    //发送消息
    QDBusMessage response = QDBusConnection::sessionBus().call(message);
    //判断method是否被正确返回
    if (response.type() == QDBusMessage::ReplyMessage)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool DBusClient::RestartContainer(QList<QString> ids)
{
    // 构造QDBusMessage
    QDBusMessage message = ContainerMessage("RestartContainer");
    message << QVariant(ids);
    //发送消息
    QDBusMessage response = QDBusConnection::sessionBus().call(message);
    //判断method是否被正确返回
    if (response.type() == QDBusMessage::ReplyMessage)
    {
        return true;
    }
    else
    {
        return false;
    }
}


QByteArray DBusClient::GetVolumeList()
{
    // 构造QDBusMessage
    QDBusMessage message = VolumeMessage("GetVolumeList");
    //发送消息
    QDBusMessage response = QDBusConnection::sessionBus().call(message);
    //判断method是否被正确返回
    if (response.type() == QDBusMessage::ReplyMessage)
    {
        //从返回参数获取返回值
        QByteArray volumeArray = response.arguments().takeFirst().toString().toUtf8();
        return volumeArray;
    }
    else
    {
        return "";
    }
}


















QByteArray DBusClient::SearchContainerByName(QString containerName)
{
    //构造一个method_call消息，服务名称为：com.bluesky.docker.Container，对象路径为：/com/bluesky/docker/Container
    //接口名称为com.bluesky.docker.Container，method名称为SearchContainerListByName
    QDBusMessage message = QDBusMessage::createMethodCall("com.bluesky.docker.Container",
                           "/com/bluesky/docker/Container",
                           "com.bluesky.docker.Container",
                           "SearchContainerListByName");
    if (!containerName.isEmpty()) {
        message << containerName ;
    }
    //发送消息
    QDBusMessage response = QDBusConnection::sessionBus().call(message);
    //判断method是否被正确返回
    if (response.type() == QDBusMessage::ReplyMessage)
    {
        //从返回参数获取返回值
        QByteArray contaierArray = response.arguments().takeFirst().toString().toUtf8();
        return contaierArray;
    }
    else
    {
        return "";
    }
}

bool DBusClient::StarContainerById(QString containerId)
{
    //构造一个method_call消息，服务名称为：com.bluesky.docker.Container，对象路径为：/com/bluesky/docker/Container
      //接口名称为com.bluesky.docker.Container，method名称为StartContainer
      QDBusMessage message = QDBusMessage::createMethodCall("com.bluesky.docker.Container",
                             "/com/bluesky/docker/Container",
                             "com.bluesky.docker.Container",
                             "StartContainer");
      message << containerId;
      //发送消息
      QDBusMessage response = QDBusConnection::sessionBus().call(message);
      //判断method是否被正确返回
      if (response.type() == QDBusMessage::ReplyMessage)
      {
          return true;

      } else {
          return false;
      }
}

bool DBusClient::StopContainerById(QString containerId)
{
    //构造一个method_call消息，服务名称为：com.bluesky.docker.Container，对象路径为：/com/bluesky/docker/Container
    //接口名称为com.bluesky.docker.Container，method名称为StopContainer
    QDBusMessage message = QDBusMessage::createMethodCall("com.bluesky.docker.Container",
                         "/com/bluesky/docker/Container",
                         "com.bluesky.docker.Container",
                         "StopContainer");
    message << containerId;
    //发送消息
   QDBusMessage response = QDBusConnection::sessionBus().call(message);
   //判断method是否被正确返回
   if (response.type() == QDBusMessage::ReplyMessage)
   {
       return true;
   } else {
       return false;
   }
}

bool DBusClient::CreateContainer(QString name,QString image,QList<QString> cmd,QList<QString> ports,QMap<QString,QVariant> volume,bool tty,bool openStdin)
{
    //构造一个method_call消息，服务名称为：com.bluesky.docker.Container，对象路径为：/com/bluesky/docker/Container
    //接口名称为com.bluesky.docker.Container，method名称为CreateContainer
    QDBusMessage message = QDBusMessage::createMethodCall("com.bluesky.docker.Container",
                         "/com/bluesky/docker/Container",
                         "com.bluesky.docker.Container",
                         "CreateContainer");
//    QString name = "test2";
//    QString image = "python:3.9";

//    QList<QString> cmd;
//    cmd << "";
//    QList<QString> ports;
//    cmd << "";
//    ports << "8081:tcp:0.0.0.0:8080" << "8082:udp:0.0.0.0:8082";
//    QMap<QString,QVariant> volume;
//    volume.insert("/home/bluesky/Desktop/name","/home/bluesky/Desktop/name2");


    message << QVariant(name)<< QVariant(image) << QVariant(cmd) << QVariant(ports) << QVariant(volume) << tty << openStdin;
    //发送消息
    QDBusMessage response = QDBusConnection::sessionBus().call(message);
    //判断method是否被正确返回
    if (response.type() == QDBusMessage::ReplyMessage)
    {
        return true;
    } else {
        return false;
    }
}

bool DBusClient::RmContainerById(QString containerId)
{
    //构造一个method_call消息，服务名称为：com.bluesky.docker.Container，对象路径为：/com/bluesky/docker/Container
    //接口名称为com.bluesky.docker.Container，method名称为RmContainerById
    QDBusMessage message = QDBusMessage::createMethodCall("com.bluesky.docker.Container",
                         "/com/bluesky/docker/Container",
                         "com.bluesky.docker.Container",
                         "RmContainerById");
    message << containerId;
    //发送消息
    QDBusMessage response = QDBusConnection::sessionBus().call(message);
    //判断method是否被正确返回
    if (response.type() == QDBusMessage::ReplyMessage)
    {
        return true;
    } else {
        return false;
    }
}

QByteArray DBusClient::GetNetworkList()
{
    //构造一个method_call消息，服务名称为：com.bluesky.docker.Container，对象路径为：/com/bluesky/docker/Container
    //接口名称为com.bluesky.docker.Container，method名称为GetContainerList
    QDBusMessage message = QDBusMessage::createMethodCall("com.bluesky.docker.Network",
                           "/com/bluesky/docker/Network",
                           "com.bluesky.docker.Network",
                           "GetNetworkList");
    //发送消息
    QDBusMessage response = QDBusConnection::sessionBus().call(message);
    //判断method是否被正确返回
    if (response.type() == QDBusMessage::ReplyMessage)
    {
        //从返回参数获取返回值
        QByteArray contaierArray = response.arguments().takeFirst().toString().toUtf8();
        return contaierArray;
    }
    else
    {
        return "";
    }
}


