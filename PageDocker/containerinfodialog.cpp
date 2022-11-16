#include <DPushButton>

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
    basicBtn->setStyleSheet("color: #252525; border-radius: 5; border: 0px;");
    basicBtn->setFixedSize(80,ui->topBtnFrm->height());
    topBtnWdgLayout->addWidget(basicBtn);

    netBtn = new QPushButton("网络信息");
    netBtn->setFixedSize(80,ui->topBtnFrm->height());
    topBtnWdgLayout->addWidget(netBtn);

    volumeBtn = new QPushButton("存储信息");
    volumeBtn->setFixedSize(80,ui->topBtnFrm->height());
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


