#include <QPushButton>
#include <QVBoxLayout>
#include <QGraphicsOpacityEffect>
#include <QListWidgetItem>

#include "dockerpage.h"
#include "ui_dockerpage.h"

DockerPage::DockerPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DockerPage)
{
    ui->setupUi(this);
    initUI();
}

DockerPage::~DockerPage()
{
    delete ui;
}

void DockerPage::initUI()
{
    QPushButton *btn = new QPushButton("测试");  // 主页软件单条数据控件
    btn->resize(100,50);
    QListWidgetItem *WContainerItem=new QListWidgetItem(ui->listWidget);
    WContainerItem->setSizeHint(QSize(40,40));
//        WContainerItem->setToolTip(); // 提示框
//    WContainerItem->setFlags(Qt::ItemIsSelectable); // 取消选择项
    ui->listWidget->setItemWidget(WContainerItem,btn);  // 将homePageSoftItem赋予WContainerItem
//    QVBoxLayout *pVBoxLayout = new QVBoxLayout(ui->menuDfrm);
//    pVBoxLayout->setMargin(0);
//    pVBoxLayout->setSpacing(0);

//    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;
//    opacityEffect->setOpacity(0.6);
//    pToolBar->setStyleSheet("background-color: #252525; border: 0px; border-radius: 8; border: 0px;");
//    pToolBar->setGraphicsEffect(opacityEffect);
//    pToolBar->addWidget(new QPushButton("测试"));
//    QPushButton *btn = new QPushButton("测试");
//    btn->resize(100,50);
//    btn->setStyleSheet("color: #FFFFFF;  background-color: #0081ff; border-radius: 8; border: 0px;");
//    pToolBar->addWidget(btn);
//    pVBoxLayout->addWidget(pToolBar);
}
