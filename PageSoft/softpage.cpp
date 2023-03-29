#include "softpage.h"

SoftPage::SoftPage(QWidget *parent) : QWidget(parent)
{
    this->resize(parent->size());
    initUI();
}

void SoftPage::initUI()
{
    QStringList labelList;  // 表头标签
    multiSelectList = new MultiSelectList(this);

    lineEdit = new DLineEdit();
    searchBtn = new DPushButton("搜索");

    lineEdit->setPlaceholderText("请输入软件名");
    lineEdit->setFixedWidth(200);

    searchBtn->setFixedSize(60,35);
    searchBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; font-size:15px;");

}
