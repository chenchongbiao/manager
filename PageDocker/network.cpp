#include "network.h"
#include "ui_network.h"

Network::Network(QWidget *parent) :
    QWidget(parent)
//    ui(new Ui::Network)
{
//    ui->setupUi(this);
    initUI();
}

Network::~Network()
{
//    delete ui;
}

void Network::initUI()
{
    // 通过界面
    mlist = new MListWidget(this);
    /*
        操作栏
    */
    netBtnWidget = new QWidget(mlist->getBtnDrm());
    netBtnWidget->resize(mlist->getBtnDrm()->width(),mlist->getBtnDrm()->height());
    netBtnLayout = new QHBoxLayout(netBtnWidget);
    netBtnLayout->setSpacing(6); // 部件之间的间距
    netBtnLayout->setMargin(0);  // 设置上下左右的间距
    netBtnLayout->setAlignment(Qt::AlignLeft);

    searchEdit = new DLineEdit();
    searchEdit->setFixedWidth(200);
    searchEdit->setPlaceholderText("请输入容器名");
    netBtnLayout->addWidget(searchEdit);

    searchBtn = new DPushButton("搜索");
    searchBtn->setFixedSize(60,35);
    searchBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; width: 60px; font-size:15px;");
    connect(searchBtn, &QPushButton::clicked, this, &Network::SearchContainer);
    netBtnLayout->addWidget(searchBtn);


}

void Network::SearchContainer()
{
    qDebug() << "搜索网络按钮被点击";
    QString keyword = searchEdit->text();
}
