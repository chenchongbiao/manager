#include <QDBusMessage>
#include <QDBusConnection>

#include "dbusclient.h"

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
