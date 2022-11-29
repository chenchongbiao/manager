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
#include <QMenu>
#include <DWidgetUtil>

#include "Utils/utils.h"
#include "container.h"
#include "ui_container.h"
#include "mapper/containermapper.h"
#include "containerinfodialog.h"
#include "createcontainerdialog.h"
#include "dbusclient.h"

Container::Container(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Container)
{
    ui->setupUi(this);
//    Utils::initDB(db);                // 初始化数据库
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

    searchEdit = new DLineEdit();
    searchEdit->setPlaceholderText("请输入容器名");
    conBtnLayout->addWidget(searchEdit);

    searchBtn = new QPushButton("搜索");
    searchBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; height: 35px; width: 60px; font-size:15px;");
    connect(searchBtn,&QPushButton::clicked,this,&Container::SearchContainer);
    conBtnLayout->addWidget(searchBtn);

    startBtn = new DPushButton("启动");
    startBtn->setStyleSheet("color: #FFFFFF; background-color: #1E90FF; border-radius: 5; border: 0px; height: 35px; width: 80px; font-size:15px;");
    connect(startBtn,&DPushButton::clicked,this,&Container::StartContainer);
    conBtnLayout->addWidget(startBtn);

    stopBtn = new DPushButton("停止");
    stopBtn->setStyleSheet("color: #FFFFFF; background-color: #F56C6C; border-radius: 5; border: 0px; height: 35px; width: 80px; font-size:15px;");
    connect(stopBtn,&DPushButton::clicked,this,&Container::StopContainer);
    conBtnLayout->addWidget(stopBtn);

    restartBtn = new DPushButton("重启");
    restartBtn->setStyleSheet("color: #FFFFFF; background-color: #1E90FF; border-radius: 5; border: 0px; height: 35px; width: 80px; font-size:15px;");
    conBtnLayout->addWidget(restartBtn);

    deleteBtn = new DPushButton("删除");
    deleteBtn->setStyleSheet("color: #FFFFFF; background-color: #F56C6C; border-radius: 5; border: 0px; height: 35px; width: 80px; font-size:15px;");
    conBtnLayout->addWidget(deleteBtn);

    createBtn = new DPushButton("创建");
    createBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; height: 35px; width: 80px; font-size:15px;");
    connect(createBtn,&DPushButton::clicked,this,&Container::OpenCreateConDialog);
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
    connect(checkAllBtn,&QRadioButton::clicked,this,&Container::CheckAllContainer);
    columnLayout->addWidget(checkAllBtn);

    contaierId = new DLabel("ID");
    contaierId->setAlignment(Qt::AlignCenter);
    contaierId->setFixedWidth(110);
    columnLayout->addWidget(contaierId);

    name = new DLabel("容器名");
    name->setAlignment(Qt::AlignCenter);
    name->setFixedWidth(130);
    columnLayout->addWidget(name);

    status = new DLabel("状态");
    status->setAlignment(Qt::AlignCenter);
    status->setFixedWidth(60);
    columnLayout->addWidget(status);

    image = new DLabel("镜像");
    image->setAlignment(Qt::AlignCenter);
    image->setFixedWidth(150);
    columnLayout->addWidget(image);

    operation = new DLabel("操作");
    operation->setAlignment(Qt::AlignCenter);
    operation->setFixedWidth(150);
    columnLayout->addWidget(operation);

//    port = new DLabel("端口");
//    port->setAlignment(Qt::AlignCenter);
//    port->setFixedWidth(90);
//    columnLayout->addWidget(port);

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
    containerArray = DBusClient::GetContainerList();
    initContainerListUI();
}

void Container::initContainerListUI()
{
    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(containerArray, &jsonError);  // 转化为 JSON 文档
    if (!document.isNull() && (jsonError.error == QJsonParseError::NoError)) { // 解析未发生错误
        if (document.isArray()) { // JSON 文档为数组
            QJsonArray containerJson = document.array();
            int conSize = containerJson.size();
            for (int i = 0; i < conSize; i++) {
                QJsonValue value = containerJson.at(i);      // 取出单个json
                QJsonObject obj = value.toObject();           // 转换为object

                QWidget *dockerWidget = new QWidget(ui->dockerListWdg);  // 主页软件单条数据控件
                dockerWidget->resize(ui->dockerListWdg->width(),ui->dockerListWdg->height());

                QHBoxLayout *layout = new QHBoxLayout(dockerWidget);
                layout->setContentsMargins(0, 0, 0, 0);  //  设置左侧、顶部、右侧和底部边距，

                QRadioButton *checkBtn = new QRadioButton(ui->dockerListWdg);
                checkBtn->setFixedSize(ui->conDfrm->height()-20,ui->conDfrm->height());
                layout->addWidget(checkBtn);
                connect(checkBtn,&QRadioButton::clicked, this, &Container::CheckContainer);

                QString id = obj.value("Id").toString().left(12);
                DLabel *dockerId = new DLabel(id);
                dockerId->setAlignment(Qt::AlignCenter);
                dockerId->setFixedWidth(110);
                layout->addWidget(dockerId);

                QString name = obj.value("Names").toArray().at(0).toString();
                name = name.mid(1,name.size()-1);
                DLabel *dockerName = new DLabel(name);
                dockerName->setFixedWidth(130);
                layout->addWidget(dockerName);

                QString state = obj.value("State").toString();
                DSwitchButton *statusBtn = new DSwitchButton();
                if (state == "running"){
                    statusBtn->setChecked(true);
                }
                statusBtn->setFixedWidth(60);
                connect(statusBtn,&DSwitchButton::clicked,this,[=](){SwitchContainer(statusBtn,id);});
                layout->addWidget(statusBtn);

                QString image = obj.value("Image").toString();
                if (image.indexOf("sha256") != -1) {
                    image = image.mid(7,18);
                }
                DLabel *dockerImage = new DLabel(image);
        //        dockerImage->setAlignment(Qt::AlignCenter);
                dockerImage->setFixedWidth(150);
                layout->addWidget(dockerImage);

                QWidget *operationWidget = new QWidget();
                operationWidget->resize(50,ui->conDfrm->height());
                QHBoxLayout *operationLayout = new QHBoxLayout(operationWidget);
                operationLayout->setContentsMargins(10, 0, 0, 0);  //  设置左侧、顶部、右侧和底部边距，

                DPushButton *infoBtn = new DPushButton("信息");
                infoBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; height: 30px; width: 30px; font-size:13px;");
                connect(infoBtn,&QPushButton::clicked,this,[=](){OpenInfoDialog(obj);});
                operationLayout->addWidget(infoBtn);

                DPushButton *delBtn = new DPushButton("删除");
                delBtn->setStyleSheet("color: #FFFFFF; background-color: #F56C6C; border-radius: 5; border: 0px; height: 30px; width: 30px; font-size:13px;");
                operationLayout->addWidget(delBtn);

                DPushButton *operationBtn = new DPushButton("操作");
                operationBtn->setStyleSheet("color: #FFFFFF; background-color: #1E90FF; border-radius: 5; border: 0px; height: 30px; width: 60px; font-size:13px;");
                operationBtn->setCheckable(true);
                QMenu *operationMenu = new QMenu(this);
                QAction *action = operationMenu->addAction("item_1");
                connect(action ,&QAction::triggered ,this ,[=](){
                        //里面写点击后执行的函数就行

                });
                operationMenu->addAction("item_2");
                operationMenu->addAction("item_3");
                operationBtn->setMenu(operationMenu);
                operationLayout->addWidget(operationBtn);
                layout->addWidget(operationWidget);

                QListWidgetItem *containerItem=new QListWidgetItem(ui->dockerListWdg);
                containerItem->setSizeHint(QSize(40,40));
//                containerItem->setToolTip(); // 提示框
                containerItem->setFlags(Qt::ItemIsSelectable); // 取消选择项
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
//        DBusClient::StarContainerById(contaierId);
        if (DBusClient::StarContainerById(contaierId)) {
                DMessageManager::instance()->sendMessage(this, style()->standardIcon(QStyle::SP_MessageBoxWarning),"启动成功");
        }
    }
    ReInitContainerList();
}

void Container::StopContainer()
{
    qDebug() << "容器停止按钮被点击" ;
    for(QRadioButton *radio : checkRadioBtnList)
    {
        QString contaierId = radio->parent()->findChildren<DLabel*>().at(0)->text();
        qDebug() << contaierId;
//        DBusClient::StopContainerById(contaierId);
        if (DBusClient::StopContainerById(contaierId)) {
            DMessageManager::instance()->sendMessage(this, style()->standardIcon(QStyle::SP_MessageBoxWarning),"停止成功");
        }
    }
    ReInitContainerList();
}   

void Container::SwitchContainer(DSwitchButton *btn,QString id)
{
    // 使用DSwitch开关控制容器
    qDebug() << "DSwitch开关被点击";
    if (btn->isChecked())  // 如果switch开关被打开
    {
        if (DBusClient::StarContainerById(id))  //  如果打开成功
        {
            DMessageManager::instance()->sendMessage(this, style()->standardIcon(QStyle::SP_MessageBoxWarning),"启动成功");
        } else {
            DMessageManager::instance()->sendMessage(this, style()->standardIcon(QStyle::SP_MessageBoxWarning),"启动失败");
        }
    } else {
        if (DBusClient::StopContainerById(id))
        {
            DMessageManager::instance()->sendMessage(this, style()->standardIcon(QStyle::SP_MessageBoxWarning),"停止成功");
        } else {
            DMessageManager::instance()->sendMessage(this, style()->standardIcon(QStyle::SP_MessageBoxWarning),"停止失败");
        }
    }
    ReInitContainerList();
}

void Container::CheckContainer()
{
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
}

void Container::CheckAllContainer()
{
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
}

void Container::SearchContainer()
{
    qDebug() << "搜索容器按钮被点击";
    QString keyword = searchEdit->text();
    qDebug() << "容器名" << keyword;
    containerArray = DBusClient::SearchContainerByName(keyword);
    if (containerArray.isEmpty()) {
        qDebug() << "容器数据为空";
        containerArray = DBusClient::GetContainerList();  // 获取所有容器数据
    }
    ui->dockerListWdg->clear();    // 清除控件
    initContainerListUI();       // 重新获取镜像数据
}

void Container::ReInitContainerList()
{
    ui->dockerListWdg->clear();                         // 清除控件
    checkRadioBtnList.clear();
    checkAllBtn->setChecked(false);
    containerArray = DBusClient::GetContainerList();    // 获取容器数据
    initContainerListUI();                              // 重新生成容器列表
}

void Container::OpenInfoDialog(QJsonObject containerJson)
{
    qDebug() << "打开容器信息窗口 " << containerJson.value("Id").toString();
    ContainerInfoDialog *infoDialog = new ContainerInfoDialog();
    infoDialog->setWindowModality(Qt::ApplicationModal);  // 禁止操作其他窗口
    infoDialog->setWindowTitle("");
    infoDialog->SetContainerJson(containerJson);
    infoDialog->show();
    Dtk::Widget::moveToCenter(infoDialog);
}

void Container::OpenCreateConDialog()
{
    qDebug() << "打开创建容器窗口 " ;
    CreateContainerDialog *createConDialog = new CreateContainerDialog();
    createConDialog->setWindowModality(Qt::ApplicationModal);  // 禁止操作其他窗口
    createConDialog->setWindowTitle("");
    createConDialog->show();
    connect(createConDialog,&CreateContainerDialog::create_finish,this,&Container::ReInitContainerList);
    Dtk::Widget::moveToCenter(createConDialog);
}
