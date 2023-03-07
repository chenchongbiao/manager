
#include "dbpage.h"

DBPage::DBPage(QWidget *parent) :
    QWidget (parent)
{
    this->resize(parent->size());
    initUI();
}

void DBPage::initUI()
{
    mainLayout = new QVBoxLayout(this);  // 主要布局 垂直布局
    DFrame *subFrame = new DFrame(this);  // 顶部菜单
    DHBoxWidget *subMenu = new DHBoxWidget(subFrame);

    subFrame->setFixedSize(this->width(), 45);

//    subMenu->addWidget(new DPushButton());
    subMenu->layout()->setContentsMargins(10, 0, 0, 0);

    mainLayout->addWidget(subFrame);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(5);
}
