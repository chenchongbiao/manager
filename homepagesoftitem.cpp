#include <QListWidget>

#include "homepagesoftitem.h"
#include "ui_homepagesoftitem.h"

HomePageSoftItem::HomePageSoftItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomePageSoftItem)
{
    ui->setupUi(this);
}

HomePageSoftItem::~HomePageSoftItem()
{
    delete ui;
}

//HomePageSoftItem::setListWidget(QListWidget *listWidget)
//{
//    QListWidgetItem *WContainerItem=new QListWidgetItem(ui->homePageSoft);

//    WContainerItem->setSizeHint(QSize(40,40));
//    ui->homePageSoft->setItemWidget(WContainerItem,WContainer);  // 将WContainer赋予WContainerItem
//}
