#include <DDialog>
#include <QFormLayout>
#include <DPasswordEdit>
#include <QMenu>
#include <dboxwidget.h>
#include <DLabel>

#include "mongodb.h"

Mongodb::Mongodb(QWidget *parent) : QWidget(parent)
{
    this->resize(parent->size());
    initUI();
}

void Mongodb::initUI()
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
    connect(addBtn, &DPushButton::clicked, this, &Mongodb::addDBDialog);

    delBtn->setFixedSize(60, 35);
    delBtn->setStyleSheet("color: #FFFFFF; background-color: #F56C6C; border-radius: 5; border: 0px; height: 30px; width: 30px; font-size:15px;");
    connect(delBtn, &DPushButton::clicked, this, [=](){

    });

    labelList << "数据库名"
              << "用户名"
              << "密码"
              << "操作";

    list->addOpLineEdit(lineEdit);
    list->addOpButton(searchBtn);
    list->addOpButton(addBtn);
    list->addOpButton(delBtn);
    list->setColumnCount(4);  // 设置列数
    list->setHeaderLabels(labelList);

    int rowCount = 0;
    QString dbName = "bluesky";// sqliteQuery->value(0).toString();
    QString userName = "bluesky"; //sqliteQuery->value(2).toString();
    QString passwd = "123456"; // sqliteQuery->value(3).toString();
    // 添加复选框控件
    DHBoxWidget *boxWidget = new DHBoxWidget();
    QCheckBox *checkBox = new QCheckBox(boxWidget);
    DLabel *dbNameLabel = new DLabel();
    DLabel *userNameLabel = new DLabel();
    DLineEdit *passwdEdit = new DLineEdit();
    DHBoxWidget *opWidget = new DHBoxWidget();
    DPushButton *updatePasswdBtn = new DPushButton("改密");
    DPushButton *delDBBtn = new DPushButton("删除");

    boxWidget->addWidget(checkBox);
    boxWidget->layout()->setAlignment(checkBox, Qt::AlignCenter);
    boxWidget->layout()->setMargin(0);

    dbNameLabel->setText(dbName);
    userNameLabel->setText(userName);
    passwdEdit->setText(passwd);
    passwdEdit->setEchoMode(QLineEdit::Password);
    passwdEdit->setPlaceholderText(passwd);

    updatePasswdBtn->setFixedSize(60,35);
    updatePasswdBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; font-size:15px;");

    delDBBtn->setFixedSize(60,35);
    delDBBtn->setStyleSheet("color: #FFFFFF; background-color: #F56C6C; border-radius: 5; border: 0px; font-size:15px;");

    opWidget->layout()->setSpacing(5);
    opWidget->addWidget(updatePasswdBtn);
    opWidget->addWidget(delDBBtn);

    list->setRowCount(rowCount+1);
    list->getTable()->setCellWidget(rowCount, 0, checkBox);
    list->getTable()->setCellWidget(rowCount, 1, dbNameLabel);
    list->getTable()->setCellWidget(rowCount, 2, userNameLabel);
    list->getTable()->setCellWidget(rowCount, 3, passwdEdit);
    list->getTable()->setCellWidget(rowCount, 4, opWidget);
    list->getTable()->setRowHeight(rowCount, 45);
}

void Mongodb::addDBDialog()
{
    qDebug() << "[" << __FUNCTION__ <<__LINE__ << "] :"  <<  "打开添加MongoDB的对话框";
    DDialog *dialog = new DDialog(this);
    DWidget *widget = new DWidget(dialog);

    QFormLayout *layout = new QFormLayout(widget);

    DLineEdit *dbName = new DLineEdit();
    DLineEdit *userName = new DLineEdit();
    DPasswordEdit *passwd = new DPasswordEdit();
//    QMenu *encodeMenu = new QMenu(this);

    layout->addRow("数据库名", dbName);
    layout->addRow("用户名", userName);
    layout->addRow("密码", passwd);
    layout->setContentsMargins(10, 5, 10, 5);
    layout->setSpacing(10);

    dialog->addContent(widget);
    dialog->addButton("取消", false, DDialog::ButtonNormal);
    dialog->addButton("确定", true, DDialog::ButtonRecommend);
    dialog->exec(); //显示对话框
}
