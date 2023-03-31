#include <dboxwidget.h>

#include "warehouse.h"

WareHouse::WareHouse(QWidget *parent) : QWidget(parent)
{
    this->resize(740, 490);

    sqliteDB = new QSqlDatabase(QSqlDatabase::database("sqlite"));
    query = new QSqlQuery(*sqliteDB);

    initUI();
}

void WareHouse::initUI()
{
    QStringList labelList;  // 表头标签
    multiSelectList = new MultiSelectList(this);

    addBtn = new DPushButton("添加");
    delBtn = new DPushButton("删除");

    addBtn->setFixedSize(60,35);
    addBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; font-size:15px;");
    connect(addBtn, &DPushButton::clicked, this, [=](){
//        query->exec("CREATE TABLE IF NOT EXISTS ware_house (id INTEGER PRIMARY KEY, url TEXT, ware_house_name TEXT, user_name TEXT, passwd TEXT, namespace TEXT, remarks TEXT)");
    });

    delBtn->setFixedSize(60, 35);
    delBtn->setStyleSheet("color: #FFFFFF; background-color: #F56C6C; border-radius: 5; border: 0px; height: 30px; width: 30px; font-size:15px;");
    connect(delBtn, &DPushButton::clicked, this, [=](){

    });

    labelList << "URL"
              << "用户"
              << "仓库名"
              << "描述"
              << "操作";
    multiSelectList->addOpButton(addBtn);
    multiSelectList->addOpButton(delBtn);
    multiSelectList->setColumnCount(5);  // 设置列数
    multiSelectList->setHeaderLabels(labelList);

    query->exec("SELECT url, ware_house_name, user_name, remarks FROM ware_house");

    int rowCount = 0;

    while (query->next()) {
        QString url = query->value(0).toString();
        QString wareHouseName = query->value(1).toString();
        QString userName = query->value(2).toString();
        QString remarks = query->value(3).toString();
        qDebug() << query->value(3).toString();

        DHBoxWidget *boxWidget = new DHBoxWidget();
        QCheckBox *checkBox = new QCheckBox(boxWidget);
        QTableWidgetItem *urlItem = new QTableWidgetItem(url);
        QTableWidgetItem *userNameItem = new QTableWidgetItem(userName);
        QTableWidgetItem *wareHouseNameItem = new QTableWidgetItem(wareHouseName);
        QTableWidgetItem *remarksItem = new QTableWidgetItem(remarks);

        DHBoxWidget *opWidget = new DHBoxWidget();
        DPushButton *editBtn = new DPushButton("编辑");
        DPushButton *delBtn = new DPushButton("删除");

        boxWidget->addWidget(checkBox);
        boxWidget->layout()->setMargin(0);
        boxWidget->layout()->setAlignment(checkBox, Qt::AlignCenter);

        urlItem->setTextColor(Qt::black);
        wareHouseNameItem->setTextColor(Qt::black);
        userNameItem->setTextColor(Qt::black);
        remarksItem->setTextColor(Qt::black);

        editBtn->setFixedSize(60,35);
        editBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; font-size:15px;");
        delBtn->setFixedSize(60,35);
        delBtn->setStyleSheet("color: #FFFFFF; background-color: #F56C6C; border-radius: 5; border: 0px; font-size:15px;");
        opWidget->layout()->setSpacing(5);
        opWidget->addWidget(editBtn);
        opWidget->addWidget(delBtn);

        multiSelectList->setRowCount(rowCount+1);
        multiSelectList->getTable()->setCellWidget(rowCount, 0, boxWidget);
        multiSelectList->getTable()->setItem(rowCount, 1, urlItem);
        multiSelectList->getTable()->setItem(rowCount, 2, userNameItem);
        multiSelectList->getTable()->setItem(rowCount, 3, wareHouseNameItem);
        multiSelectList->getTable()->setItem(rowCount, 4, remarksItem);
        multiSelectList->getTable()->setCellWidget(rowCount, 5, opWidget);
        multiSelectList->getTable()->setRowHeight(rowCount, 45);

        rowCount++;
    }
}
