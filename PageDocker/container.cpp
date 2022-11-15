#include <QDebug>
#include <DSwitchButton>
#include <QToolButton>
#include <QSqlQuery>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusConnection>
#include <DMessageManager>

#include "Utils/utils.h"
#include "container.h"
#include "ui_container.h"
#include "mapper/containermapper.h"

Container::Container(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Container)
{
    ui->setupUi(this);
//    Utils::initDB(db);                // 初始化数据库
    GetContainerArrayFromSessionBus();  // 调用sessionbus获取容器列表数据
    initUI();
}

Container::~Container()
{
    db.close();
    delete ui;
}

void Container::initUI()
{
    /*
        按钮初始化
    */
    int width = ui->conDfrm->width();
    int height = ui->conDfrm->height();
    // 操作按钮布局
    conBtnWidget = new QWidget(ui->conDfrm);
    conBtnWidget->resize(width,height);
    conBtnLayout = new QHBoxLayout(conBtnWidget);
    conBtnLayout->setSpacing(6);  // 部件之间的间距
    conBtnLayout->setContentsMargins(10, 0, 0, 0);  //  设置左侧、顶部、右侧和底部边距，
    conBtnLayout->setAlignment(Qt::AlignLeft);
    conBtnLayout->insertSpacing(0, -12);
    conBtnLayout->addSpacing(10);

    startBtn = new DPushButton("启动");
    startBtn->setStyleSheet("color: #FFFFFF; background-color: #1E90FF; border-radius: 5; border: 0px; height: 35px; width: 90px; font-size:15px;");
    connect(startBtn,&DPushButton::clicked,this,&Container::StartContainer);
    conBtnLayout->addWidget(startBtn);

    stopBtn = new DPushButton("停止");
    stopBtn->setStyleSheet("color: #FFFFFF; background-color: #F56C6C; border-radius: 5; border: 0px; height: 35px; width: 90px; font-size:15px;");
    connect(stopBtn,&DPushButton::clicked,this,&Container::StopContainer);
    conBtnLayout->addWidget(stopBtn);

    restartBtn = new DPushButton("重启");
    restartBtn->setStyleSheet("color: #FFFFFF; background-color: #1E90FF; border-radius: 5; border: 0px; height: 35px; width: 90px; font-size:15px;");
    conBtnLayout->addWidget(restartBtn);

    deleteBtn = new DPushButton("删除");
    deleteBtn->setStyleSheet("color: #FFFFFF; background-color: #F56C6C; border-radius: 5; border: 0px; height: 35px; width: 90px; font-size:15px;");
    conBtnLayout->addWidget(deleteBtn);

    createBtn = new DPushButton("创建");
    createBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; height: 35px; width: 90px; font-size:15px;");
    conBtnLayout->addWidget(createBtn);

    /*
        列名初始化
    */

    columnWidget = new QWidget(ui->columnDfrm);
    columnLayout = new QHBoxLayout(columnWidget);
    columnLayout->setContentsMargins(15, 0, 0, 0);  //  设置左侧、顶部、右侧和底部边距，
    columnLayout->setSpacing(0);  // 部件之间的间距

    checkAllBtn = new QRadioButton(columnWidget);
    checkAllBtn->setFixedSize(height-20,height);
    connect(checkAllBtn,&QRadioButton::clicked,this,[=](){
        if (checkAllBtn->isChecked())
        {
            qDebug() << "全选按钮被点击";
            for(int i=0;i < ui->dockerListWdg->count();i++)
            {
                QWidget *curContaier = ui->dockerListWdg->itemWidget(ui->dockerListWdg->item(i));
                QRadioButton *radio = curContaier->findChildren<QRadioButton*>().at(0);
                if (checkRadioBtnList.indexOf(radio) == -1)  // 等于-1表示没被选中
                {
                    radio->setChecked(true);
                    checkRadioBtnList.append(radio);
                }

            }
        } else {
            qDebug() << "全选按钮取消";
            for(QRadioButton *radio: checkRadioBtnList)
            {
                radio->setChecked(false);
            }
            checkRadioBtnList.clear();
        }
    });
    columnLayout->addWidget(checkAllBtn);

    contaierId = new DLabel("ID");
    contaierId->setAlignment(Qt::AlignCenter);
    contaierId->setFixedWidth(110);
    columnLayout->addWidget(contaierId);

    name = new DLabel("容器名");
    name->setAlignment(Qt::AlignCenter);
    name->setFixedWidth(110);
    columnLayout->addWidget(name);

    status = new DLabel("状态");
    status->setAlignment(Qt::AlignCenter);
    status->setFixedWidth(90);
    columnLayout->addWidget(status);

    address = new DLabel("监控");
    address->setAlignment(Qt::AlignCenter);
    address->setFixedWidth(110);
    columnLayout->addWidget(address);

    image = new DLabel("镜像");
    image->setAlignment(Qt::AlignCenter);
    image->setFixedWidth(150);
    columnLayout->addWidget(image);

    port = new DLabel("端口");
    port->setAlignment(Qt::AlignCenter);
    port->setFixedWidth(90);
    columnLayout->addWidget(port);

    /*
     * 从sqlite初始化docker列表
    */
//    QSqlQuery query =containerMapper.GetContainerList();
//    while(query.next()){
//        QWidget *dockerWidget = new QWidget(ui->dockerListWdg);  // 主页软件单条数据控件
//        dockerWidget->resize(ui->dockerListWdg->width(),ui->dockerListWdg->height());

//        QHBoxLayout *layout = new QHBoxLayout(dockerWidget);
//        layout->setContentsMargins(0, 0, 0, 0);  //  设置左侧、顶部、右侧和底部边距，

//        QRadioButton *checkBtn = new QRadioButton(ui->dockerListWdg);
//        checkBtn->setFixedSize(height-20,height);
//        layout->addWidget(checkBtn);

//        QString id= query.value(0).toString().left(12);
//        DLabel *dockerId = new DLabel(id);
//        dockerId->setAlignment(Qt::AlignCenter);
//        dockerId->setFixedWidth(110);
//        layout->addWidget(dockerId);

//        QString name = query.value(1).toString();
//        DLabel *dockerName = new DLabel(name);
//        dockerName->setFixedWidth(110);
//        layout->addWidget(dockerName);

//        QString state = query.value(2).toString();
//        DSwitchButton *statusBtn = new DSwitchButton();
//        if (state == "running"){
//            statusBtn->setChecked(true);
//        }
//        statusBtn->setFixedWidth(60);
//        layout->addWidget(statusBtn);

//        DLabel *dockerAddress = new DLabel();
//        dockerAddress->setAlignment(Qt::AlignCenter);
//        dockerAddress->setFixedWidth(110);
//        layout->addWidget(dockerAddress);

//        QWidget *addressWidget = new QWidget(dockerAddress);
//        addressWidget->resize(addressWidget->width(),addressWidget->height());
//        QHBoxLayout *addressLayout = new QHBoxLayout(addressWidget);
//        addressLayout->setContentsMargins(0, 0, 0, 0);  //  设置左侧、顶部、右侧和底部边距，
//        DPushButton *logBtn = new DPushButton(addressWidget);
//        logBtn->setFixedSize(20,20);
//        logBtn->setIcon(QIcon(":/images/log.svg"));
//        logBtn->setStyleSheet("DPushButton{background-color:transparent}");        //背景透明
//        addressLayout->addWidget(logBtn);

//        DPushButton *terminalBtn = new DPushButton(addressWidget);
//        terminalBtn->setFixedSize(20,20);
//        terminalBtn->setIcon(QIcon(":/images/terminal.svg"));
//        logBtn->setStyleSheet("DPushButton{background-color:transparent}");
//        addressLayout->addWidget(terminalBtn);

//        QString image = query.value(3).toString();
//        if (image.indexOf("sha256") != -1) {
//            image = image.mid(7,18);
//        }
//        DLabel *dockerImage = new DLabel(image);
//        dockerImage->setFixedWidth(150);
//        layout->addWidget(dockerImage);

//        QByteArray portArray = query.value(4).toString().toUtf8();
//        QString port = GetPortFromJson(portArray);
//        DLabel *dockerPort = new DLabel(port);
//        dockerPort->setAlignment(Qt::AlignCenter);
//        dockerPort->setFixedWidth(90);
//        layout->addWidget(dockerPort);


//        QListWidgetItem *containerItem=new QListWidgetItem(ui->dockerListWdg);
//        containerItem->setSizeHint(QSize(40,40));
//    //        WContainerItem->setToolTip(); // 提示框
//        containerItem->setFlags(Qt::ItemIsSelectable); // 取消选择项
//        ui->dockerListWdg->setItemWidget(containerItem,dockerWidget);  // 将dockerWidgetr赋予containerItem
//    }
    /*
     * 从sessionbus初始化docker列表
    */
    GetContainerListFromJson();
}

void Container::GetContainerArrayFromSessionBus()
{
    //构造一个method_call消息，服务名称为：com.bluesky.docker.Container，对象路径为：/com/bluesky/docker/Container
    //接口名称为com.bluesky.docker.Container，method名称为GetContainerList
    QDBusMessage message = QDBusMessage::createMethodCall("com.bluesky.docker.Container",
                           "/com/bluesky/docker/Container",
                           "com.bluesky.docker.Container",
                           "GetContainerList");
    //发送消息
    QDBusMessage response = QDBusConnection::sessionBus().call(message);
    //判断method是否被正确返回
    if (response.type() == QDBusMessage::ReplyMessage)
    {
        //从返回参数获取返回值
        contaierArray = response.arguments().takeFirst().toString().toUtf8();

    }
    else
    {
        qDebug() << "容器数据获取失败";
    }
}

void Container::GetContainerListFromJson()
{
    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(contaierArray, &jsonError);  // 转化为 JSON 文档
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)) { // 解析未发生错误
        if (doucment.isArray()) { // JSON 文档为数组
            QJsonArray containerArray = doucment.array();
            int conSize = containerArray.size();
            for (int i = 0; i < conSize; i++) {
                QJsonValue value = containerArray.at(i);      // 取出单个json
                QJsonObject obj = value.toObject();           // 转换为object

                QWidget *dockerWidget = new QWidget(ui->dockerListWdg);  // 主页软件单条数据控件
                dockerWidget->resize(ui->dockerListWdg->width(),ui->dockerListWdg->height());

                QHBoxLayout *layout = new QHBoxLayout(dockerWidget);
                layout->setContentsMargins(0, 0, 0, 0);  //  设置左侧、顶部、右侧和底部边距，

                QRadioButton *checkBtn = new QRadioButton(ui->dockerListWdg);
                checkBtn->setFixedSize(ui->conDfrm->height()-20,ui->conDfrm->height());
                layout->addWidget(checkBtn);
                connect(checkBtn,&QRadioButton::clicked, this, [=](){
                    QRadioButton *curBtn = (QRadioButton *) sender();// 槽函数中调用sender函数，返回指向发送信号的对象的指针
                    int index = checkRadioBtnList.indexOf(curBtn);
                    if (index == -1) // 等于-1代表没有被选中了，添加到QList中
                    {
                        qDebug() << "当前选中" << curBtn->parent()->findChildren<DLabel *>().at(0)->text();
                        checkRadioBtnList.append(curBtn);
                    } else {
                        qDebug() << "当前取消" << curBtn->parent()->findChildren<DLabel *>().at(0)->text();
                        checkRadioBtnList.removeAt(index);
                    }
                    if (checkRadioBtnList.count() == ui->dockerListWdg->count() && !checkAllBtn->isChecked()) // 所有数据都被选中 并且全选按钮未被选中
                    {
                        checkAllBtn->setChecked(true);
                    } else if (checkRadioBtnList.count() != ui->dockerListWdg->count() && checkAllBtn->isChecked()){ // 所有数据未被选中 但是全选按钮被选中
                        checkAllBtn->setChecked(false);
                    }

                });

                QString id = obj.value("Id").toString().left(12);
                DLabel *dockerId = new DLabel(id);
                dockerId->setAlignment(Qt::AlignCenter);
                dockerId->setFixedWidth(110);
                layout->addWidget(dockerId);

                QString name = obj.value("Names").toArray().at(0).toString();
                DLabel *dockerName = new DLabel(name);
                dockerName->setFixedWidth(110);
                layout->addWidget(dockerName);

                QString state = obj.value("State").toString();
                DSwitchButton *statusBtn = new DSwitchButton();
                if (state == "running"){
                    statusBtn->setChecked(true);
                }
                statusBtn->setFixedWidth(60);
                connect(statusBtn,&DSwitchButton::clicked,this,[=](){
                    if (statusBtn->isChecked())
                    {
                        qDebug() << "DSwitch开发打开 "<< contaierId;
                        QString contaierId = statusBtn->parent()->findChildren<DLabel*>().at(0)->text();
                        //构造一个method_call消息，服务名称为：com.bluesky.docker.Container，对象路径为：/com/bluesky/docker/Container
                        //接口名称为com.bluesky.docker.Container，method名称为StartContainer
                        QDBusMessage message = QDBusMessage::createMethodCall("com.bluesky.docker.Container",
                                               "/com/bluesky/docker/Container",
                                               "com.bluesky.docker.Container",
                                               "StartContainer");
                        message << contaierId;
                        //发送消息
                        QDBusMessage response = QDBusConnection::sessionBus().call(message);
                        //判断method是否被正确返回
                        if (response.type() == QDBusMessage::ReplyMessage)
                        {
                            DMessageManager::instance()->sendMessage(this, style()->standardIcon(QStyle::SP_MessageBoxWarning),"启动成功");
                            ui->dockerListWdg->clear();         // 清除控件
                            checkRadioBtnList.clear();
                            GetContainerArrayFromSessionBus();  // 调用sessionbus获取容器列表数据
                            GetContainerListFromJson();         // 重新获取容器数据
                            checkAllBtn->setChecked(false);

                        } else {
                            DMessageManager::instance()->sendMessage(this, style()->standardIcon(QStyle::SP_MessageBoxWarning),"启动失败");
                        }
                    } else {
                        qDebug() << "DSwitch开发关闭 "<< contaierId;
                        QString contaierId = statusBtn->parent()->findChildren<DLabel*>().at(0)->text();
                        qDebug() << contaierId;
                        //构造一个method_call消息，服务名称为：com.bluesky.docker.Container，对象路径为：/com/bluesky/docker/Container
                        //接口名称为com.bluesky.docker.Container，method名称为StopContainer
                        QDBusMessage message = QDBusMessage::createMethodCall("com.bluesky.docker.Container",
                                               "/com/bluesky/docker/Container",
                                               "com.bluesky.docker.Container",
                                               "StopContainer");
                        message << contaierId;
                        //发送消息
                        QDBusMessage response = QDBusConnection::sessionBus().call(message);
                        //判断method是否被正确返回
                        if (response.type() == QDBusMessage::ReplyMessage)
                        {
                            DMessageManager::instance()->sendMessage(this, style()->standardIcon(QStyle::SP_MessageBoxWarning),"停止成功");
                            ui->dockerListWdg->clear();         // 清除控件
                            checkRadioBtnList.clear();
                            GetContainerArrayFromSessionBus();  // 调用sessionbus获取容器列表数据
                            GetContainerListFromJson();         // 重新获取容器数据
                            checkAllBtn->setChecked(false);

                        } else {
                            DMessageManager::instance()->sendMessage(this, style()->standardIcon(QStyle::SP_MessageBoxWarning),"停止失败");
                        }
                    }

                });
                layout->addWidget(statusBtn);

                DLabel *dockerAddress = new DLabel();
                dockerAddress->setAlignment(Qt::AlignCenter);
                dockerAddress->setFixedWidth(110);
                layout->addWidget(dockerAddress);

                QWidget *addressWidget = new QWidget(dockerAddress);
                addressWidget->resize(addressWidget->width(),addressWidget->height());
                QHBoxLayout *addressLayout = new QHBoxLayout(addressWidget);
                addressLayout->setContentsMargins(0, 0, 0, 0);  //  设置左侧、顶部、右侧和底部边距，
                DPushButton *logBtn = new DPushButton(addressWidget);
                logBtn->setFixedSize(20,20);
                logBtn->setIcon(QIcon(":/images/log.svg"));
                logBtn->setStyleSheet("DPushButton{background-color:transparent}");        //背景透明
                addressLayout->addWidget(logBtn);

                DPushButton *terminalBtn = new DPushButton(addressWidget);
                terminalBtn->setFixedSize(20,20);
                terminalBtn->setIcon(QIcon(":/images/terminal.svg"));
                logBtn->setStyleSheet("DPushButton{background-color:transparent}");
                addressLayout->addWidget(terminalBtn);

                QString image = obj.value("Image").toString();
                if (image.indexOf("sha256") != -1) {
                    image = image.mid(7,18);
                }
                DLabel *dockerImage = new DLabel(image);
        //        dockerImage->setAlignment(Qt::AlignCenter);
                dockerImage->setFixedWidth(150);
                layout->addWidget(dockerImage);

                QString portStr;
                QJsonArray portsArray = obj.value("Ports").toArray();
                int portsSize = portsArray.size();
                for (int i = 0; i < portsSize; ++i) {
                    QJsonValue value = portsArray.at(i);      // 取出单个json
                    QJsonObject obj = value.toObject();  // 转换为object
                    double privatePort =obj.value("PrivatePort").toDouble();
                    double publicPort = obj.value("PublicPort").toDouble();
                    portStr += QString("%1:%2\n").arg(publicPort).arg(privatePort);
                }
                portStr = portStr.left(portStr.length()-1);  // 去掉最后一个\n
                DLabel *dockerPort = new DLabel(portStr);
                dockerPort->setAlignment(Qt::AlignCenter);
                dockerPort->setFixedWidth(90);
                dockerPort->setToolTip(portStr);
                layout->addWidget(dockerPort);

                QListWidgetItem *containerItem=new QListWidgetItem(ui->dockerListWdg);
                containerItem->setSizeHint(QSize(40,40));
//                containerItem->setToolTip(); // 提示框
//              containerItem->setFlags(Qt::ItemIsSelectable); // 取消选择项
                ui->dockerListWdg->setItemWidget(containerItem,dockerWidget);  // 将dockerWidgetr赋予containerItem
            }
        }
    }
}

void Container::StartContainer()
{
    qDebug() << "容器启动按钮被点击" ;
    for(QRadioButton *radio : checkRadioBtnList)
    {
        QString contaierId = radio->parent()->findChildren<DLabel*>().at(0)->text();
        qDebug() << contaierId;
        //构造一个method_call消息，服务名称为：com.bluesky.docker.Container，对象路径为：/com/bluesky/docker/Container
        //接口名称为com.bluesky.docker.Container，method名称为StartContainer
        QDBusMessage message = QDBusMessage::createMethodCall("com.bluesky.docker.Container",
                               "/com/bluesky/docker/Container",
                               "com.bluesky.docker.Container",
                               "StartContainer");
        message << contaierId;
        //发送消息
        QDBusMessage response = QDBusConnection::sessionBus().call(message);
        //判断method是否被正确返回
        if (response.type() == QDBusMessage::ReplyMessage)
        {
            DMessageManager::instance()->sendMessage(this, style()->standardIcon(QStyle::SP_MessageBoxWarning),"启动成功");
            ui->dockerListWdg->clear();         // 清除控件
            checkRadioBtnList.clear();
            GetContainerArrayFromSessionBus();  // 调用sessionbus获取容器列表数据
            GetContainerListFromJson();         // 重新获取容器数据
            checkAllBtn->setChecked(false);

        } else {
            DMessageManager::instance()->sendMessage(this, style()->standardIcon(QStyle::SP_MessageBoxWarning),"启动失败");
        }
    }
}

void Container::StopContainer()
{
    qDebug() << "容器停止按钮被点击" ;
    for(QRadioButton *radio : checkRadioBtnList)
    {
        QString contaierId = radio->parent()->findChildren<DLabel*>().at(0)->text();
        qDebug() << contaierId;
        //构造一个method_call消息，服务名称为：com.bluesky.docker.Container，对象路径为：/com/bluesky/docker/Container
        //接口名称为com.bluesky.docker.Container，method名称为StopContainer
        QDBusMessage message = QDBusMessage::createMethodCall("com.bluesky.docker.Container",
                               "/com/bluesky/docker/Container",
                               "com.bluesky.docker.Container",
                               "StopContainer");
        message << contaierId;
        //发送消息
        QDBusMessage response = QDBusConnection::sessionBus().call(message);
        //判断method是否被正确返回
        if (response.type() == QDBusMessage::ReplyMessage)
        {
            DMessageManager::instance()->sendMessage(this, style()->standardIcon(QStyle::SP_MessageBoxWarning),"停止成功");
            ui->dockerListWdg->clear();         // 清除控件
            checkRadioBtnList.clear();
            GetContainerArrayFromSessionBus();  // 调用sessionbus获取容器列表数据
            GetContainerListFromJson();         // 重新获取容器数据
            checkAllBtn->setChecked(false);

        } else {
            DMessageManager::instance()->sendMessage(this, style()->standardIcon(QStyle::SP_MessageBoxWarning),"停止失败");
        }
    }
}
