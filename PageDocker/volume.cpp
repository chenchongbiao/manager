#include "volume.h"

Volume::Volume(QWidget *parent) :
    QWidget(parent)
{
    initUI();
}

void Volume::initUI()
{
    // 通用列表界面
    mlist = new MListWidget(this);

    // 初始化操作栏
    initOperationUI();
}

void Volume::initOperationUI()
{
    opWdg = new QWidget(mlist->getOpDrm());
    opWdg->resize(mlist->getOpDrm()->width(),mlist->getOpDrm()->height());
    opLayout = new QHBoxLayout(opWdg);
    opLayout->setSpacing(6);
    opLayout->setContentsMargins(10, 0, 0, 0);
    opLayout->setAlignment(Qt::AlignLeft);

    searchEdit = new DLineEdit();
    searchEdit->setFixedWidth(200);
    searchEdit->setPlaceholderText("请输入存储卷名");
    opLayout->addWidget(searchEdit);

    searchBtn = new DPushButton("搜索");
    searchBtn->setFixedSize(60, 35);
    searchBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; font-size:15px;");
    connect(searchBtn, &DPushButton::clicked, this, &Volume::SearchVolume);
    opLayout->addWidget(searchBtn);

    createBtn = new DPushButton("创建");
    createBtn->setFixedSize(60,35);
    createBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; font-size:15px;");
    connect(createBtn,&DPushButton::clicked,this,&Volume::OpenCreateVolDialog);
    opLayout->addWidget(createBtn);
}

void Volume::SearchVolume()
{

}

void Volume::OpenCreateVolDialog()
{

}
