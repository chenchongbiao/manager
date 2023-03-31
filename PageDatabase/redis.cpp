#include <QTableWidgetItem>
#include <dboxwidget.h>
#include "redis.h"

Redis::Redis(QWidget *parent) : QWidget(parent)
{
    this->resize(parent->size());
    initUI();
}

void Redis::initUI()
{
    QStringList labelList;  // 表头标签
    list = new MultiSelectList(this);

    lineEdit = new DLineEdit();
    searchBtn = new DPushButton("搜索");
    addBtn = new DPushButton("添加");
    delBtn = new DPushButton("删除");

    lineEdit->setPlaceholderText("请输入数据库名");
    lineEdit->setFixedWidth(200);

    searchBtn->setFixedSize(60,35);
    searchBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; font-size:15px;");
    //    connect(searchBtn,&QPushButton::clicked,this,&Container::SearchContainer);

    addBtn->setFixedSize(60,35);
    addBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; font-size:15px;");
    connect(addBtn, &DPushButton::clicked, this, [=](){

    });

    delBtn->setFixedSize(60, 35);
    delBtn->setStyleSheet("color: #FFFFFF; background-color: #F56C6C; border-radius: 5; border: 0px; height: 30px; width: 30px; font-size:15px;");
    connect(delBtn, &DPushButton::clicked, this, [=](){

    });

    labelList << "键"
              << "值"
              << "数据类型"
              << "数据长度"
              << "有效期"
              << "操作";

    list->addOpLineEdit(lineEdit);
    list->addOpButton(searchBtn);
    list->addOpButton(addBtn);
    list->addOpButton(delBtn);
    list->setColumnCount(6);  // 设置列数
    list->setHeaderLabels(labelList);

    int rowCount = 0;
    QString key = "name";
    QString value = "bluesky";
    QString dataType = "123456";
    int datalen = 7;
    QString validPeriod = "永久";

    // 添加复选框控件
    DHBoxWidget *boxWidget = new DHBoxWidget();
    QCheckBox *checkBox = new QCheckBox(boxWidget);
    QTableWidgetItem *keyItem = new QTableWidgetItem(key);
    QTableWidgetItem *valueItem = new QTableWidgetItem(value);
    QTableWidgetItem *dataTypeItem = new QTableWidgetItem(dataType);
    QTableWidgetItem *datalenItem = new QTableWidgetItem(datalen);
    QTableWidgetItem *validItem = new QTableWidgetItem(validPeriod);

    DHBoxWidget *opWidget = new DHBoxWidget();
    DPushButton *editBtn = new DPushButton("编辑");
    DPushButton *delKeyBtn = new DPushButton("删除");

    boxWidget->addWidget(checkBox);
    boxWidget->layout()->setMargin(0);
    boxWidget->layout()->setAlignment(checkBox, Qt::AlignCenter);

    keyItem->setTextColor(Qt::black);
    valueItem->setTextColor(Qt::black);
    dataTypeItem->setTextColor(Qt::black);
    datalenItem->setTextColor(Qt::black);
    validItem->setTextColor(Qt::black);

    editBtn->setFixedSize(60,35);
    editBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; font-size:15px;");
    delKeyBtn->setFixedSize(60,35);
    delKeyBtn->setStyleSheet("color: #FFFFFF; background-color: #F56C6C; border-radius: 5; border: 0px; font-size:15px;");
    opWidget->layout()->setSpacing(5);
    opWidget->addWidget(editBtn);
    opWidget->addWidget(delKeyBtn);

    list->setRowCount(rowCount+1);
    list->getTable()->setCellWidget(rowCount, 0, boxWidget);
    list->getTable()->setItem(rowCount, 1, keyItem);
    list->getTable()->setItem(rowCount, 2, valueItem);
    list->getTable()->setItem(rowCount, 3, dataTypeItem);
    list->getTable()->setItem(rowCount, 4, datalenItem);
    list->getTable()->setItem(rowCount, 5, validItem);
    list->getTable()->setCellWidget(rowCount, 6, opWidget);
    list->getTable()->setRowHeight(rowCount, 45);

    rowCount++;
}
