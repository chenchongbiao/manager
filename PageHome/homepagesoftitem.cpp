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

void HomePageSoftItem::setSoftName(const QString name)
{
    ui->softWareName->setText(name);
}
