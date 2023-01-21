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
    // 获取通用列表界面
    mlist = new MListWidget(this);

    // 搜索框及按钮等部分初始化
    initOperationUI();

    // 列名初始化
    initColumnUI();

    // 从sessionbus获取容器数据
    containerArray = DBusClient::GetContainerList(QMap<QString,QVariant>());

    // 初始化容器列表
    initContainerListUI();
}

void Container::initContainerListUI()
{
    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(containerArray, &jsonError);  // 转化为 JSON 文档
    if (!document.isNull() && (jsonError.error == QJsonParseError::NoError)) { // 解析未发生错误
        if (document.isObject()) {  // JSON 文档为对象
            QJsonObject object = document.object();  // 转化为对象
            if (object.contains("data")) {  // 包含指定的 key
                QJsonValue dataValue = object.value("data");  // 获取指定 key 对应的 value

                if (dataValue.isArray()) { // JSON 文档为数组
                    QJsonArray containerJson = dataValue.toArray();
                    int conSize = containerJson.size();
                    for (int i = 0; i < conSize; i++) {
                        QJsonValue value = containerJson.at(i);      // 取出单个json
                        QJsonObject obj = value.toObject();           // 转换为object

                        QWidget *dockerWidget = new QWidget(mlist->getListWidget());  // 主页软件单条数据控件
        //                dockerWidget->resize( ui->dockerListWdg->width(),ui->dockerListWdg->height());

                        QHBoxLayout *layout = new QHBoxLayout(dockerWidget);
                        layout->setMargin(0);  //  设置外边距，左侧、顶部、右侧和底部边距，

                        QCheckBox *checkBtn = new QCheckBox(mlist->getListWidget());
                        checkBtn->setFixedSize(mlist->getBtnDrm()->height()-20,mlist->getBtnDrm()->height());
                        layout->addWidget(checkBtn);
                        connect(checkBtn,&QCheckBox::clicked, this, &Container::CheckContainer);

                        QString id = obj.value("id").toString().left(12);
                        DLabel *dockerId = new DLabel(id);
                        dockerId->setAlignment(Qt::AlignCenter);
                        dockerId->setFixedWidth(110);
                        layout->addWidget(dockerId);

                        QString name = obj.value("name").toArray().at(0).toString();
                        name = name.mid(1,name.size()-1);
                        DLabel *dockerName = new DLabel(name);
                        dockerName->setFixedWidth(130);
                        layout->addWidget(dockerName);

                        QString state = obj.value("state").toString();
                        DSwitchButton *statusBtn = new DSwitchButton();
                        if (state == "running"){
                            statusBtn->setChecked(true);
                        }
                        statusBtn->setFixedWidth(60);
                        connect(statusBtn,&DSwitchButton::clicked,this,[=](){SwitchContainer(statusBtn,id);});
                        layout->addWidget(statusBtn);


                        QJsonObject imgObj = obj.value("image").toObject();
                        QString image = imgObj.value("tags").toArray().at(0).toString();
                        DLabel *dockerImage = new DLabel(image);
                //        dockerImage->setAlignment(Qt::AlignCenter);
                        dockerImage->setFixedWidth(150);
                        layout->addWidget(dockerImage);

                        QWidget *operationWidget = new QWidget(dockerWidget);
                        operationWidget->resize(50,mlist->getBtnDrm()->height());
                        QHBoxLayout *operationLayout = new QHBoxLayout(operationWidget);
                        operationLayout->setContentsMargins(10, 0, 0, 0);  //  设置左侧、顶部、右侧和底部边距，

                        DPushButton *infoBtn = new DPushButton("信息");
                        infoBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; height: 30px; width: 30px; font-size:13px;");
                        connect(infoBtn,&QPushButton::clicked,this,[=](){OpenInfoDialog(obj);});
                        operationLayout->addWidget(infoBtn);

                        DPushButton *delBtn = new DPushButton("删除");
                        delBtn->setStyleSheet("color: #FFFFFF; background-color: #F56C6C; border-radius: 5; border: 0px; height: 30px; width: 30px; font-size:13px;");
                        connect(delBtn,&DPushButton::clicked,this,[=](){RmContainerById(id);});
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

                        QListWidgetItem *containerItem=new QListWidgetItem(mlist->getListWidget());
                        containerItem->setSizeHint(QSize(40,40));
        //                containerItem->setToolTip(); // 提示框
                        containerItem->setFlags(Qt::ItemIsSelectable); // 取消选择项
                        mlist->getListWidget()->setItemWidget(containerItem,dockerWidget);  // 将dockerWidgetr赋予containerItem
                    }
                }
            }
        }
    }
}

void Container::initOperationUI()
{
    // 操作按钮布局
    conBtnWidget = new QWidget(mlist->getBtnDrm());
    conBtnWidget->resize(mlist->getBtnDrm()->width(),mlist->getBtnDrm()->height());
    conBtnLayout = new QHBoxLayout(conBtnWidget);
    conBtnLayout->setSpacing(6);  // 部件之间的间距
    conBtnLayout->setContentsMargins(10, 0, 0, 0);  //  设置左侧、顶部、右侧和底部边距，
    conBtnLayout->setAlignment(Qt::AlignLeft);

    searchEdit = new DLineEdit();
    searchEdit->setPlaceholderText("请输入容器名");
    searchEdit->setFixedWidth(200);
    conBtnLayout->addWidget(searchEdit);

    searchBtn = new DPushButton("搜索");
    searchBtn->setFixedSize(60,35);
    searchBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; font-size:15px;");
    connect(searchBtn,&QPushButton::clicked,this,&Container::SearchContainer);
    conBtnLayout->addWidget(searchBtn);

    startBtn = new DPushButton("启动");
    startBtn->setFixedSize(60,35);
    startBtn->setStyleSheet("color: #FFFFFF; background-color: #1E90FF; border-radius: 5; border: 0px; font-size:15px;");
    connect(startBtn,&DPushButton::clicked,this,&Container::StartContainer);
    conBtnLayout->addWidget(startBtn);

    stopBtn = new DPushButton("停止");
    stopBtn->setFixedSize(60,35);
    stopBtn->setStyleSheet("color: #FFFFFF; background-color: #F56C6C; border-radius: 5; border: 0px; font-size:15px;");
    connect(stopBtn,&DPushButton::clicked,this,&Container::StopContainer);
    conBtnLayout->addWidget(stopBtn);

    restartBtn = new DPushButton("重启");
    restartBtn->setFixedSize(60,35);
    restartBtn->setStyleSheet("color: #FFFFFF; background-color: #1E90FF; border-radius: 5; border: 0px; font-size:15px;");
    connect(restartBtn,&DPushButton::clicked,this,&Container::RestartContainer);
    conBtnLayout->addWidget(restartBtn);

    deleteBtn = new DPushButton("删除");
    deleteBtn->setFixedSize(60,35);
    deleteBtn->setStyleSheet("color: #FFFFFF; background-color: #F56C6C; border-radius: 5; border: 0px; font-size:15px;");
    connect(deleteBtn,&DPushButton::clicked,this,&Container::RmContainer);
    conBtnLayout->addWidget(deleteBtn);

    createBtn = new DPushButton("创建");
    createBtn->setFixedSize(60,35);
    createBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; font-size:15px;");
    connect(createBtn,&DPushButton::clicked,this,&Container::OpenCreateConDialog);
    conBtnLayout->addWidget(createBtn);
}

void Container::initColumnUI()
{
    QString labStyle = "font-size:15px;";
    int idLabWidth = 110;
    int nameLabWidth = 130;
    int statusLabWidth = 60;
    int imageLabWidth = 150;
    int operationLabWidth = 150;
    columnWidget = new QWidget(mlist->getColDrm());
    columnLayout = new QHBoxLayout(columnWidget);
    columnLayout->setContentsMargins(10, 0, 0, 0);  //  设置左侧、顶部、右侧和底部边距
    columnLayout->setSpacing(0);  // 部件之间的间距

//    checkAllBtn = new QRadioButton(columnWidget);
    checkAllBtn = new QCheckBox(columnWidget);
    checkAllBtn->setFixedSize(mlist->getBtnDrm()->height()-20,mlist->getBtnDrm()->height());
    connect(checkAllBtn,&QCheckBox::clicked,this,&Container::CheckAllContainer);
    columnLayout->addWidget(checkAllBtn);

    // 定义一个函数，用来添加表头，依次传入，表头名称，以及宽度
    auto addColumnItem = [&](const QString labName, const int labWidth){
        DLabel *label = new DLabel(labName);
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet(labStyle);
        label->setFixedWidth(labWidth);
        columnLayout->addWidget(label);
    };

    addColumnItem("ID", idLabWidth);
    addColumnItem("容器名", nameLabWidth);
    addColumnItem("状态", statusLabWidth);
    addColumnItem("镜像", imageLabWidth);
    addColumnItem("操作", operationLabWidth);
}

void Container::StartContainer()
{
    qDebug() << "容器启动按钮被点击" ;
    QList<QString> ids;  // 存放被选中的容器的id,

    for(QCheckBox *checkBox : checkBoxBtnList)
    {
        QString contaierId = checkBox->parent()->findChildren<DLabel*>().at(0)->text();
        qDebug() << contaierId;
        ids << contaierId;

//        if (DBusClient::StarContainerById(contaierId)) {  // 循环单个启动容器
//                DMessageManager::instance()->sendMessage(this, style()->standardIcon(QStyle::SP_MessageBoxWarning),"启动成功");
//        }
    }
    if (ids.isEmpty()) {
        DMessageManager::instance()->sendMessage(this, style()->standardIcon(QStyle::SP_MessageBoxWarning),"未选中容器");
    } else {
        // 传入一个容器id的列表，传给后端调用
        if (DBusClient::StartContainer(ids)) {
            DMessageManager::instance()->sendMessage(this, style()->standardIcon(QStyle::SP_MessageBoxWarning),"启动成功");
        }
    }
    ReInitContainerList();
}

void Container::StopContainer()
{
    qDebug() << "容器停止按钮被点击" ;
    QList<QString> ids;  // 存放被选中的容器的id,
    for(QCheckBox *checkBox : checkBoxBtnList)
    {
        QString containerId = checkBox->parent()->findChildren<DLabel*>().at(0)->text();
        qDebug() << containerId;
        ids << containerId;
//        if (DBusClient::StopContainerById(containerId)) {
//            DMessageManager::instance()->sendMessage(this, style()->standardIcon(QStyle::SP_MessageBoxWarning),"停止成功");
//        }
    }
    if (ids.isEmpty()) {
        DMessageManager::instance()->sendMessage(this, style()->standardIcon(QStyle::SP_MessageBoxWarning),"未选中容器");
    } else {
        // 传入一个容器id的列表，传给后端调用
        if (DBusClient::StopContainer(ids)) {
            DMessageManager::instance()->sendMessage(this, style()->standardIcon(QStyle::SP_MessageBoxWarning),"停止成功");
        }
    }
    ReInitContainerList();
}   

void Container::RestartContainer()
{
    qDebug() << "容器重启按钮被点击" ;
    QList<QString> ids;  // 存放被选中的容器的id,
    for(QCheckBox *checkBox : checkBoxBtnList)
    {
        QString containerId = checkBox->parent()->findChildren<DLabel*>().at(0)->text();
        qDebug() << containerId;
        ids << containerId;
    }
    if (ids.isEmpty()) {
        DMessageManager::instance()->sendMessage(this, style()->standardIcon(QStyle::SP_MessageBoxWarning),"未选中容器");
    } else {
        // 传入一个容器id的列表，传给后端调用
        if (DBusClient::RestartContainer(ids)) {
            DMessageManager::instance()->sendMessage(this, style()->standardIcon(QStyle::SP_MessageBoxWarning),"重启成功");
        }
    }
    ReInitContainerList();
}

void Container::RmContainer()
{
    qDebug() << "容器删除按钮被点击" ;
    for(QCheckBox *checkBox : checkBoxBtnList)
    {
        QString containerId = checkBox->parent()->findChildren<DLabel*>().at(0)->text();
        qDebug() << contaierId;
        if (DBusClient::RmContainerById(containerId)) {
            DMessageManager::instance()->sendMessage(this, style()->standardIcon(QStyle::SP_MessageBoxWarning),"删除成功");
        }
    }
    ReInitContainerList();
}

void Container::RmContainerById(QString containerId)
{
    qDebug() << "容器删除按钮被点击" ;
    if (DBusClient::RmContainerById(containerId)) {
        DMessageManager::instance()->sendMessage(this, style()->standardIcon(QStyle::SP_MessageBoxWarning),"删除成功");
    }
    ReInitContainerList();
}

void Container::SwitchContainer(DSwitchButton *btn,QString id)
{
    // 使用DSwitch开关控制容器
    qDebug() << "DSwitch开关被点击";
    QList<QString> ids;  // 存放被选中的容器的id,
    ids << id;
    if (btn->isChecked())  // 如果switch开关被打开
    {

        if (DBusClient::StartContainer(ids))  //  如果打开成功
        {
            DMessageManager::instance()->sendMessage(this, style()->standardIcon(QStyle::SP_MessageBoxWarning),"启动成功");
        } else {
            DMessageManager::instance()->sendMessage(this, style()->standardIcon(QStyle::SP_MessageBoxWarning),"启动失败");
        }
    } else {
        if (DBusClient::StopContainer(ids))
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
    QCheckBox *curBtn = (QCheckBox *) sender();// 槽函数中调用sender函数，返回指向发送信号的对象的指针
    int index = checkBoxBtnList.indexOf(curBtn);
    if (index == -1) // 等于-1代表没有被选中了，添加到QList中
    {
        qDebug() << "当前选中" << curBtn->parent()->findChildren<DLabel *>().at(0)->text();
        checkBoxBtnList.append(curBtn);
    } else {
        qDebug() << "当前取消" << curBtn->parent()->findChildren<DLabel *>().at(0)->text();
        checkBoxBtnList.removeAt(index);
    }
    if (checkBoxBtnList.count() == mlist->getListWidget()->count() && !checkAllBtn->isChecked()) // 所有数据都被选中 并且全选按钮未被选中
    {
        checkAllBtn->setChecked(true);
    } else if (checkBoxBtnList.count() != mlist->getListWidget()->count() && checkAllBtn->isChecked()){ // 所有数据未被选中 但是全选按钮被选中
        checkAllBtn->setChecked(false);
    }
}

void Container::CheckAllContainer()
{
    if (checkAllBtn->isChecked())
    {
        qDebug() << "全选按钮被点击";
        for(int i=0;i < mlist->getListWidget()->count();i++)
        {
            QWidget *curContaier = mlist->getListWidget()->itemWidget(mlist->getListWidget()->item(i));
            QCheckBox *checkBox = curContaier->findChildren<QCheckBox*>().at(0);
            if (checkBoxBtnList.indexOf(checkBox) == -1)  // 等于-1表示没被选中
            {
                checkBox->setChecked(true);
                checkBoxBtnList.append(checkBox);
            }

        }
    } else {
        qDebug() << "全选按钮取消";
        for(QCheckBox *checkBox: checkBoxBtnList)
        {
            checkBox->setChecked(false);
        }
        checkBoxBtnList.clear();
    }
}

void Container::SearchContainer()
{
    qDebug() << "搜索容器按钮被点击";
    QString keyword = searchEdit->text();
    qDebug() << "容器名" << keyword;
//    containerArray = DBusClient::SearchContainerByName(keyword);
    if (keyword == "") {
        qDebug() << "容器名为空";
        DMessageManager::instance()->sendMessage(this, style()->standardIcon(QStyle::SP_MessageBoxWarning),"容器名为空");
    } else {
        QMap<QString,QVariant> args;
        args.insert("name", keyword);
        containerArray = DBusClient::GetContainerList(args);  // 获取所有容器数据
        DMessageManager::instance()->sendMessage(this, style()->standardIcon(QStyle::SP_MessageBoxWarning),"搜索成功");
        ReInitContainerList();  // 重新生成列表数据
    }
//    ui->dockerListWdg->clear();    // 清除控件
//    initContainerListUI();       // 重新获取镜像数据

}

void Container::ReInitContainerList()
{
    mlist->getListWidget()->clear();                         // 清除控件
    checkBoxBtnList.clear();
    checkAllBtn->setChecked(false);
//    containerArray = DBusClient::GetContainerList(QString());    // 获取容器数据
    initContainerListUI();                              // 重新生成容器列表
}

void Container::OpenInfoDialog(QJsonObject containerJson)
{
    qDebug() << "打开容器信息窗口 " << containerJson.value("Id").toString();
    ContainerInfoDialog *infoDialog = new ContainerInfoDialog();
    infoDialog->SetContainerJson(containerJson);

    DDialog *dialog = new DDialog(this);
    dialog->setAttribute(Qt::WidgetAttribute::WA_DeleteOnClose); //将指针设置为窗口关闭即释放
    dialog->addContent(infoDialog);
    dialog->exec(); //显示对话框

    Dtk::Widget::moveToCenter(infoDialog);
}

void Container::OpenCreateConDialog()
{
    qDebug() << "打开创建容器窗口 " ;
    CreateContainerDialog *createConDialog = new CreateContainerDialog();

    DDialog *dialog = new DDialog(this);
    dialog->setAttribute(Qt::WidgetAttribute::WA_DeleteOnClose); //将指针设置为窗口关闭即释放
    dialog->addContent(createConDialog);
    dialog->exec(); //显示对话框

    connect(createConDialog,&CreateContainerDialog::create_finish,this,&Container::ReInitContainerList);
    Dtk::Widget::moveToCenter(createConDialog);
}
