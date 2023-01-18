#include <DPushButton>
#include <QJsonArray>
#include <QDateTime>

#include "containerinfodialog.h"
#include "ui_containerinfodialog.h"

ContainerInfoDialog::ContainerInfoDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContainerInfoDialog)
{
    ui->setupUi(this);
    initUI();

    connect(basicBtn, &DPushButton::clicked, this, [=](){ContainerInfoDialog::chooseLeftMenu(0);});
    connect(netBtn, &DPushButton::clicked, this, [=](){ContainerInfoDialog::chooseLeftMenu(1);});
    connect(volumeBtn, &DPushButton::clicked, this, [=](){ContainerInfoDialog::chooseLeftMenu(2);});
}

ContainerInfoDialog::~ContainerInfoDialog()
{
    delete ui;
}

void ContainerInfoDialog::initUI()
{
    topBtnWdg = new QWidget(ui->topBtnFrm);
    topBtnWdgLayout = new QHBoxLayout(topBtnWdg);
    topBtnWdgLayout->setSpacing(6);
    topBtnWdgLayout->setContentsMargins(0, 0, 0, 0);

    basicBtn = new DPushButton("基本信息");
    basicBtn->setFixedSize(btnWidth,ui->topBtnFrm->height());
    topBtnWdgLayout->addWidget(basicBtn);

    netBtn = new QPushButton("网络信息");
    netBtn->setFixedSize(btnWidth,ui->topBtnFrm->height());
    topBtnWdgLayout->addWidget(netBtn);

    volumeBtn = new QPushButton("存储信息");
    volumeBtn->setFixedSize(btnWidth,ui->topBtnFrm->height());
    topBtnWdgLayout->addWidget(volumeBtn);

    topBtnList << basicBtn
               << netBtn
               << volumeBtn;

    for(int i=0;i < topBtnList.count();i++) {
        DPushButton *btn = topBtnList.at(i);
        checkMenu(btn,false);

        connect(btn,&DPushButton::clicked,this,[=](){
           DPushButton *curBtn = (DPushButton *) sender();
           qDebug() << "当前按下" << curBtn->text();
           for(int i=0;i < topBtnList.count();i++) {
               DPushButton *btn = topBtnList.at(i);
               checkMenu(btn,curBtn==btn);
           }
        });
    }

    checkMenu(basicBtn,true);  // 默认选中基本信息按钮

    initBasicInfoUI();   // 初始化基本信息UI
}

void ContainerInfoDialog::checkMenu(QPushButton *btn,bool isCheck)
{
    if (isCheck)
    {
        btn->setStyleSheet("color: #409EFF; border-radius: 5; border: 1px solid rgb(64,158,255); font-size:15px;");
    } else {
        btn->setStyleSheet("color: #252525; border-radius: 5; border: 0px;");
    }
}

void ContainerInfoDialog::chooseLeftMenu(int index)  // 菜单切换逻辑
{
    nowMenu = index;
    ui->stackedWidget->setCurrentIndex(nowMenu);
}

void ContainerInfoDialog::initBasicInfoUI()
{
//    basicInfoWdgLayout = new QVBoxLayout(ui->basicInfoWdg);
    basicInfoWdgLayout = new QGridLayout(ui->basicInfoFrm);
//    basicInfoWdgLayout->setSpacing(6); //设置间距
    basicInfoWdgLayout->setContentsMargins(50, 0, 0, 0); //  设置左侧、顶部、右侧和底部边距，
    //设置行列比例系数
//    basicInfoWdgLayout->setRowStretch(0, 1);  // 第一个参数是行数，其最大值表示这个布局有几行；第二个参数是该行的长度比例
//    basicInfoWdgLayout->setRowStretch(1, 3);
//    basicInfoWdgLayout->setColumnStretch(0, 1); // 第一个参数是行数，其最大值表示这个布局有几列；第二个参数是该列的长度比例
//    basicInfoWdgLayout->setColumnStretch(1, 3);

    idLab = new DLabel("容器ID");
    idLab->setFixedSize(labelWidth,labelHeight);
    idLab->setAlignment(Qt::AlignRight);  // 水平靠右
    idLab->setAlignment(Qt::AlignVCenter); // 垂直居中
    idEdit = new QLineEdit();
    idEdit->setFixedSize(editWidth,editHeight);
    idEdit->setAlignment(Qt::AlignLeft);  // 水平靠左
    idEdit->setEnabled(false);
    idEdit->setStyleSheet("background-color: #FFFFFF; border-radius: 5; border: 1px solid #E6E6E6; font-size:15px;");
    basicInfoWdgLayout->addWidget(idLab, 0, 0 , 1 , 1);
    basicInfoWdgLayout->addWidget(idEdit, 0, 1 ,1 , 3);

    nameLab = new DLabel("容器名称");
    nameLab->setFixedSize(labelWidth,labelHeight);
    nameEdit = new QLineEdit();
    nameEdit->setFixedSize(editWidth,editHeight);
    nameEdit->setStyleSheet("background-color: #FFFFFF; border-radius: 5; border: 1px solid #E6E6E6; font-size:15px;");
    basicInfoWdgLayout->addWidget(nameLab, 1, 0, 1 , 1);
    basicInfoWdgLayout->addWidget(nameEdit, 1, 1, 1 , 1);

    updateNameBtn = new DPushButton("修改");
    updateNameBtn->setFixedSize(60,labelHeight);
    updateNameBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; font-size:15px;");
    basicInfoWdgLayout->addWidget(updateNameBtn, 1, 2);

    imgIdLab = new DLabel("镜像ID");
    imgIdLab->setFixedSize(labelWidth,labelHeight);
    imgIdEdit = new QLineEdit();
    imgIdEdit->setFixedSize(editWidth,editHeight);
    imgIdEdit->setEnabled(false);
    imgIdEdit->setStyleSheet("background-color: #FFFFFF; border-radius: 5; border: 1px solid #E6E6E6; font-size:15px;");
    basicInfoWdgLayout->addWidget(imgIdLab, 2, 0, 1 , 1);
    basicInfoWdgLayout->addWidget(imgIdEdit, 2, 1, 1 , 3);

    cmdLab = new DLabel("启动命令");
    cmdLab->setFixedSize(labelWidth,labelHeight);
    cmdEdit = new QLineEdit();
    cmdEdit->setFixedSize(editWidth,editHeight);
    cmdEdit->setEnabled(false);
    cmdEdit->setStyleSheet("background-color: #FFFFFF; border-radius: 5; border: 1px solid #E6E6E6; font-size:15px;");
    basicInfoWdgLayout->addWidget(cmdLab, 3, 0, 1 , 1);
    basicInfoWdgLayout->addWidget(cmdEdit, 3, 1, 1 , 3);

    createTimeLab = new DLabel("创建时间");
    createTimeLab->setFixedSize(labelWidth,labelHeight);
    createTimeEdit = new QLineEdit();
    createTimeEdit->setFixedSize(editWidth,editHeight);
    createTimeEdit->setEnabled(false);
    createTimeEdit->setStyleSheet("background-color: #FFFFFF; border-radius: 5; border: 1px solid #E6E6E6; font-size:15px;");
    basicInfoWdgLayout->addWidget(createTimeLab, 4, 0, 1 , 1);
    basicInfoWdgLayout->addWidget(createTimeEdit, 4, 1, 1 , 3);

    stateLab = new DLabel("状态");
    stateLab->setFixedSize(labelWidth,labelHeight);
    stateEdit = new QLineEdit();
    stateEdit->setFixedSize(editWidth,editHeight);
    stateEdit->setEnabled(false);
    stateEdit->setStyleSheet("background-color: #FFFFFF; border-radius: 5; border: 1px solid #E6E6E6; font-size:15px;");
    basicInfoWdgLayout->addWidget(stateLab, 5, 0, 1 , 1);
    basicInfoWdgLayout->addWidget(stateEdit, 5, 1, 1 , 3);
}

void ContainerInfoDialog::SetContainerJson(QJsonObject containerJson)
{
    this->containerJson = containerJson;
    idEdit->setText(containerJson.value("id").toString().left(12));

    QString name = containerJson.value("name").toArray().at(0).toString();
    name = name.mid(1,name.size()-1);
    nameEdit->setText(name);

    QJsonObject imgObj = containerJson.value("image").toObject();
    QString imgId = imgObj.value("id").toString().left(12);
    imgIdEdit->setText(imgId);

    QString cmd;
    QJsonArray cmdArr = containerJson.value("cmd").toArray();
    for (int i=0;i<cmdArr.size();i++) {
        cmd += " " + cmdArr[i].toString();
    }
    cmd.remove(QRegExp("^ +\\s*"));
    cmdEdit->setText(cmd);

    qint64 createTime = containerJson.value("create_time").toInt();
    QString dateTime = QDateTime::fromSecsSinceEpoch(createTime).toString("yyyy-MM-dd hh:mm:ss");
    createTimeEdit->setText(dateTime);

    QString state = containerJson.value("state").toString();
    if (state == "running"){
        stateEdit->setText("运行中");
    } else {
        stateEdit->setText("已退出");
    }
}


