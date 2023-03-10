#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include <QDateTime>
#include <QListWidget>

#include "createcontainerdialog.h"
#include "ui_createcontainerdialog.h"
#include "dbusclient.h"
#include "Utils/utils.h"

CreateContainerDialog::CreateContainerDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateContainerDialog)
{
    ui->setupUi(this);
    initUI();

    connect(checkImgBtn, &DPushButton::clicked, this, [=](){CreateContainerDialog::chooseLeftMenu(0);});
    connect(containerInfoBtn, &DPushButton::clicked, this, [=](){CreateContainerDialog::chooseLeftMenu(1);});
    connect(portMapBtn,&DPushButton::clicked,this,[=](){CreateContainerDialog::chooseLeftMenu(2);});
}

CreateContainerDialog::~CreateContainerDialog()
{
    delete ui;
}

void CreateContainerDialog::initUI()
{
    initLeftMenuUI();
    initCheckImgUI();
    initConInfoUI();
    initPortMapUI();
}

void CreateContainerDialog::initLeftMenuUI()
{
    leftMenuWdg = new QWidget(ui->leftBtnFrm);
    leftMenuWdgLayout = new QVBoxLayout(leftMenuWdg);
    leftMenuWdgLayout->setSpacing(6);  //设置间距
    leftMenuWdgLayout->setContentsMargins(0, 0, 0, 0); //  设置左侧、顶部、右侧和底部边距

    checkImgBtn = new DPushButton("选择镜像");
    checkImgBtn->setFixedSize(ui->leftBtnFrm->width(),btnHeight);
    connect(checkImgBtn,&DPushButton::clicked,this,[=](){chooseLeftMenu(0);});
    leftMenuWdgLayout->addWidget(checkImgBtn);

    containerInfoBtn = new DPushButton("容器信息");
    containerInfoBtn->setFixedSize(ui->leftBtnFrm->width(),btnHeight);
    leftMenuWdgLayout->addWidget(containerInfoBtn);

    portMapBtn = new DPushButton("端口映射");
    portMapBtn->setFixedSize(ui->leftBtnFrm->width(),btnHeight);
    leftMenuWdgLayout->addWidget(portMapBtn);

    volumeMountBtn = new DPushButton("存储挂载");
    volumeMountBtn->setFixedSize(ui->leftBtnFrm->width(),btnHeight);
    leftMenuWdgLayout->addWidget(volumeMountBtn);

    leftBtnList << checkImgBtn
                << containerInfoBtn
                << portMapBtn
                << volumeMountBtn;

    for(int i=0;i < leftBtnList.count();i++) {
        DPushButton *btn = leftBtnList.at(i);
        checkMenu(btn,false);

        connect(btn,&DPushButton::clicked,this,[=](){
           DPushButton *curBtn = (DPushButton *) sender();
           qDebug() << "当前按下" << curBtn->text();
           for(int i=0;i < leftBtnList.count();i++) {
               DPushButton *btn = leftBtnList.at(i);
               checkMenu(btn,curBtn==btn);
           }
        });
    }

    checkMenu(checkImgBtn,true);  // 默认选中选择镜像按钮
}

void CreateContainerDialog::initCheckImgUI()
{
    searchWdg = new QWidget(ui->searchDfrm);
    searchWdgLayout = new QHBoxLayout(searchWdg);
    searchWdgLayout->setSpacing(6);            // 设置控件间距
    searchWdgLayout->setContentsMargins(6, 0, 0, 0); //  设置左侧、顶部、右侧和底部边距

    searchEdit = new DLineEdit();
    searchEdit->setFixedSize(searchEditWidth,45);
    searchEdit->setStyleSheet("background-color: #FFFFFF; border-radius: 5; border: 1px solid #E6E6E6; font-size:15px;");
    searchWdgLayout->addWidget(searchEdit);

    searchBtn = new DPushButton("搜索");
    searchBtn->setFixedSize(searchBtnWidth,ui->searchDfrm->height()-15);
    searchBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; font-size:15px;");
    connect(searchBtn,&DPushButton::clicked,this,&CreateContainerDialog::SearchImage);
    searchWdgLayout->addWidget(searchBtn);

    columnWidget = new QWidget(ui->columnDfrm);
    columnWidget->resize(ui->columnDfrm->width(),ui->columnDfrm->height());
    columnLayout = new QHBoxLayout(columnWidget);
    columnLayout->setContentsMargins(0, 0, 0, 0);  //  设置左侧、顶部、右侧和底部边距，
    columnLayout->setSpacing(0);  // 部件之间的间距

    idLab = new DLabel("ID");
    idLab->setAlignment(Qt::AlignCenter);
    idLab->setFixedSize(100,ui->columnDfrm->height());
    columnLayout->addWidget(idLab);

    tagsLab = new DLabel("标签");
    tagsLab->setAlignment(Qt::AlignCenter);
    tagsLab->setFixedSize(200,ui->columnDfrm->height());
    columnLayout->addWidget(tagsLab);

    imageSizeLab = new DLabel("镜像尺寸");
    imageSizeLab->setAlignment(Qt::AlignCenter);
    imageSizeLab->setFixedSize(80,ui->columnDfrm->height());
    columnLayout->addWidget(imageSizeLab);

    createTimeLab = new DLabel("创建时间");
    createTimeLab->setAlignment(Qt::AlignCenter);
    createTimeLab->setFixedSize(110,ui->columnDfrm->height());
    columnLayout->addWidget(createTimeLab);

    imageArray = DBusClient::GetImageList();
    initImageListUI();

}

void CreateContainerDialog::initImageListUI()
{
    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(imageArray,&jsonError);   // 转化为 JSON 文档
    if (!document.isNull() && (jsonError.error == QJsonParseError::NoError)) { // 解析未发生错误
        if (document.isObject()) {  // JSON 文档为对象
            QJsonObject object = document.object();  // 转化为对象
            if (object.contains("data")) {  // 包含指定的 key
            QJsonValue dataValue = object.value("data");  // 获取指定 key 对应的 value

                if (dataValue.isArray()) { // JSON 文档为数组
                    QJsonArray imageArray = dataValue.toArray();
                    int imgSize = imageArray.size();
                    for(int i=0;i < imgSize;i++) {
                        QJsonValue value = imageArray.at(i);
                        QJsonObject obj = value.toObject();

                        QWidget *imgWidget = new QWidget(ui->ListWdg);  // 主页软件单条数据的widget
                        imgWidget->resize(ui->ListWdg->width(),ui->ListWdg->height());

                        QHBoxLayout *layout = new QHBoxLayout(imgWidget);
                        layout->setContentsMargins(0, 0, 0, 0);  //  设置左侧、顶部、右侧和底部边距，

        //                QRadioButton *checkBtn = new QRadioButton(ui->ListWdg);
        //                checkBtn->setFixedSize(ui->imgDfrm->height()-20,ui->imgDfrm->height());
        //                layout->addWidget(checkBtn);
                        QString id = obj.value("id").toString().left(12);
                        DLabel *imgId = new DLabel(id);
                        imgId->setAlignment(Qt::AlignCenter);
                        imgId->setFixedWidth(110);
                        layout->addWidget(imgId);

//                        QString RepoTags = "";
//                        QJsonArray repoTagsArray = obj.value("RepoTags").toArray();
//                        for(int i=0;i<repoTagsArray.size();i++) {
//                            RepoTags += QString("%1 ").arg(repoTagsArray.at(i).toString());
//                        }
//                        RepoTags.chop(1);  // 删除字符串右边n个字符
                        QString RepoTags = obj.value("tags").toArray().at(0).toString();
                        DLabel *tags = new DLabel(RepoTags);
                        tags->setFixedWidth(200);
                        layout->addWidget(tags);



                        qint64 size = obj.value("size").toInt();
                        DLabel *imgSize = new DLabel(QString("%1").arg(Utils::formatSize(size)));
                        imgSize->setFixedWidth(80);
                        layout->addWidget(imgSize);

                        qint64 createTime = obj.value("create_time").toInt();
                        QString dateTime = QDateTime::fromSecsSinceEpoch(createTime).toString("yyyy-MM-dd hh:mm:ss");
                        DLabel *dockerName = new DLabel(dateTime);
                        dockerName->setFixedWidth(120);
                        layout->addWidget(dockerName);

                        QListWidgetItem *containerItem=new QListWidgetItem(ui->ListWdg);
                        containerItem->setSizeHint(QSize(40,40));
                        //  containerItem->setToolTip(); // 提示框
        //                  containerItem->setFlags(Qt::ItemIsSelectable); // 取消选择项
                        ui->ListWdg->setItemWidget(containerItem,imgWidget);  // 将dockerWidgetr赋予containerItem
                    }
                    connect(ui->ListWdg,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(CheckImage()));
                    ui->ListWdg->setStyleSheet("QListWidget::Item:selected{border: 1px solid rgb(64,158,255);background-color: #ECF5FF;}");
                }
            }
        }
    }
}

void CreateContainerDialog::initConInfoUI()
{
    conInfoWdg = new QWidget(ui->conInfoDfrm);
    conInfoLayout = new QFormLayout(conInfoWdg);
    conInfoLayout->setContentsMargins(50,30,0,0);  //  设置左侧、顶部、右侧和底部边距
    conInfoLayout->setSpacing(30);

    nameLab = new DLabel("容器名");
    nameLab->setFixedSize(labelWidth,labelHeight);
    nameLab->setStyleSheet("font-size:15px;");
    nameEdit = new QLineEdit();
    nameEdit->setFixedSize(editWidth,editHeight);
    nameEdit->setStyleSheet("background-color: #FFFFFF; border-radius: 5; border: 1px solid #E6E6E6; font-size:15px;");
    conInfoLayout->addRow(nameLab,nameEdit);

    imgLab = new DLabel("镜像名");
    imgLab->setFixedSize(labelWidth,labelHeight);
    imgEdit = new QLineEdit();
    imgEdit->setFixedSize(editWidth,editHeight);
    imgEdit->setStyleSheet("background-color: #FFFFFF; border-radius: 5; border: 1px solid #E6E6E6; font-size:15px;");
    imgEdit->setEnabled(false);
    conInfoLayout->addRow(imgLab,imgEdit);

    tagInfoLab = new DLabel("镜像标签");
    tagInfoLab->setFixedSize(labelWidth,labelHeight);
    tagInfoBtn = new DPushButton();
    tagInfoBtn->setFixedSize(editWidth,editHeight);
    tagInfoBtn->setCheckable(true);
    tagMenu = new QMenu(this);
    tagMenu->setFixedWidth(editWidth);
    tagInfoBtn->setMenu(tagMenu);
    conInfoLayout->addRow(tagInfoLab,tagInfoBtn);

    cmdLab = new DLabel("启动命令");
    cmdLab->setFixedSize(labelWidth,labelHeight);
    cmdEdit = new QLineEdit();
    cmdEdit->setFixedSize(editWidth,editHeight);
    cmdEdit->setStyleSheet("background-color: #FFFFFF; border-radius: 5; border: 1px solid #E6E6E6; font-size:15px;");
    conInfoLayout->addRow(cmdLab,cmdEdit);

    checkBoxLayout = new QHBoxLayout();
    checkBoxLayout->setMargin(0);
    checkBoxLayout->setSpacing(0);
    ttyChBox = new QCheckBox();
    ttyChBox->setFixedWidth(editHeight);
    checkBoxLayout->addWidget(ttyChBox);
    ttyLab = new DLabel("虚拟终端");
    checkBoxLayout->addWidget(ttyLab);
    openStdinChBox = new QCheckBox();
    openStdinChBox->setFixedWidth(editHeight);
    checkBoxLayout->addWidget(openStdinChBox);
    openStdinLab = new DLabel("交互模式");
    checkBoxLayout->addWidget(openStdinLab);
    conInfoLayout->addRow(checkBoxLayout);

    confirmBtnLayout = new QHBoxLayout();
    confirmBtnLayout->setContentsMargins(editWidth,confirmBtnHeight,0,0);
    confirmBtn = new DPushButton("确定");
    confirmBtn->setFixedSize(confirmBtnWidth,confirmBtnHeight);
    confirmBtn->setStyleSheet("color: #FFFFFF; background-color: #1E90FF; border-radius: 5; border: 0px; font-size:15px;");
    connect(confirmBtn,&DPushButton::clicked,this,[=](){
        qDebug() << "创建容器";
        QString name = nameEdit->text();
        QString image = QString("%1:%2").arg(imgEdit->text()).arg(tag);
        QList<QString> cmd;
        cmd = cmdEdit->text().split(" ");
        QList<QString> ports;
        cmd << "";
        ports << "8081:tcp:0.0.0.0:8080" << "8082:udp:0.0.0.0:8082";
        bool tty;
        if (ttyChBox->isCheckable()) {
            tty = true;
        } else {
            tty = false;
        }
        bool openStdin;
        if (openStdinChBox->isChecked()) {
            openStdin = true;
        } else {
            openStdin = false;
        }
        QMap<QString,QVariant> volume;
        volume.insert("/home/bluesky/Desktop/name","/home/bluesky/Desktop/name2");
        if(DBusClient::CreateContainer(name,image,cmd,ports,volume,tty,openStdin)) {
            qDebug() << "创建成功";
            this->hide();
            emit create_finish();
        }
    });
    confirmBtnLayout->addWidget(confirmBtn);
    conInfoLayout->addRow(confirmBtnLayout);

}

void CreateContainerDialog::initPortMapUI()
{
    portMapWdg = new QWidget(ui->portMapDfrm);
    portMapLayout = new QFormLayout(portMapWdg);
    portMapLayout->setMargin(0);
    portMapLayout->setSpacing(10);

    int labWidth = 130, lalHeight = 35;
    portColumnLayout = new QHBoxLayout(portMapWdg);
    portColumnLayout->setMargin(0);
    portColumnLayout->setSpacing(0);

    portLab = new DLabel("内部端口");
    portLab->setAlignment(Qt::AlignCenter);
//    portLab->setFixedWidth(130);
    portLab->setFixedSize(labWidth, lalHeight);
    portColumnLayout->addWidget(portLab);

    protocolLab = new DLabel("协议");
    protocolLab->setAlignment(Qt::AlignCenter);
//    protocolLab->setFixedWidth(130);
    protocolLab->setFixedSize(labWidth, lalHeight);
    portColumnLayout->addWidget(protocolLab);

    listenIpLab = new DLabel("监听地址");
    listenIpLab->setAlignment(Qt::AlignCenter);
//    listenIpLab->setFixedWidth(130);
    listenIpLab->setFixedSize(labWidth, lalHeight);
    portColumnLayout->addWidget(listenIpLab);

    listenPortLab = new DLabel("监听端口");
    listenPortLab->setAlignment(Qt::AlignCenter);
//    listenPortLab->setFixedWidth(130);
    listenPortLab->setFixedSize(labWidth, lalHeight);
    portColumnLayout->addWidget(listenPortLab);

    operationLab = new DLabel("操作");
    operationLab->setAlignment(Qt::AlignCenter);
//    operationLab->setFixedWidth(130);
    operationLab->setFixedSize(labWidth, lalHeight);
    portColumnLayout->addWidget(operationLab);

    portMapLayout->addRow(portColumnLayout);

    // 端口映射列表
    portMapListWdg = new QListWidget();
    portMapListWdg->setFixedWidth(730);

    QWidget *portMapWidget = new QWidget(portMapListWdg);
    portMapWidget->setFixedSize(portMapListWdg->width(),35);
    QHBoxLayout *layout = new QHBoxLayout(portMapWidget);
    layout->setMargin(0);

    DLineEdit *portEdit = new DLineEdit();
    portEdit->setText("1111111");
    layout->addWidget(portEdit);

    DLineEdit *protocolEdit = new DLineEdit();
    protocolEdit->setText("111111");
    layout->addWidget(protocolEdit);

    QListWidgetItem *containerItem=new QListWidgetItem(portMapListWdg);
    containerItem->setSizeHint(QSize(40,40));
//   containerItem->setToolTip(); // 提示框
    containerItem->setFlags(Qt::ItemIsSelectable); // 取消选择项
    portMapListWdg->setItemWidget(containerItem,portMapWidget);  // 将portMapWidget赋予containerItem
    portMapLayout->addRow(portMapListWdg);

}

void CreateContainerDialog::CheckImage()
{
    QWidget *item = ui->ListWdg->itemWidget(ui->ListWdg->currentItem());
    checkImage = item->findChildren<DLabel *>().at(1)->text();
    for(int i=0;i < leftBtnList.count();i++) {  // 选中镜像后跳转到容器信息页
        DPushButton *btn = leftBtnList.at(i);
        checkMenu(btn,containerInfoBtn==btn);
    }
    imgEdit->setText(checkImage.split(":").at(0));
    tagList = checkImage.split(" ");
    tag = tagList.at(0).split(":").at(1);
    tagInfoBtn->setText(tag);
    if (!tagMenu->isEmpty()) {   // 清空数据
        tagMenu->clear();
    }
    for(int i=0;i<tagList.size();i++)
    {
        qDebug() << "标签" << tagList.at(i);
        QAction *action = tagMenu->addAction(tagList.at(i).split(":").at(1));
        connect(action ,&QAction::triggered ,this ,[=](){
            tag = action->text();
            tagInfoBtn->setText(tag);
        });
    }
    chooseLeftMenu(1);
}

void CreateContainerDialog::SearchImage()
{
    qDebug() << "搜索镜像按钮被点击";
    QString keyword = searchEdit->text();
    qDebug() << "镜像名" << keyword;
    imageArray = DBusClient::SearchImageByName(keyword);
    if (imageArray.isEmpty()) {
        qDebug() << "镜像数据为空";
        imageArray = DBusClient::GetImageList();
    }
    ui->ListWdg->clear();    // 清除控件
    initImageListUI();       // 重新获取镜像数据
}

void CreateContainerDialog::checkMenu(QPushButton *btn,bool isCheck)
{
    if (isCheck)
    {
        btn->setStyleSheet("color: #409EFF; border-radius: 5; border: 1px solid rgb(64,158,255); font-size:15px;");
    } else {
        btn->setStyleSheet("color: #252525; border-radius: 5; border: 0px;");
    }
}

void CreateContainerDialog::chooseLeftMenu(int index)  // 菜单切换逻辑
{
    nowMenu = index;
    ui->stackedWidget->setCurrentIndex(nowMenu);
}

QList<QString> CreateContainerDialog::GetTagList()
{
//    imageArray = DBusClient::SearchImageByName(checkImage);
//    return tagList;
}

