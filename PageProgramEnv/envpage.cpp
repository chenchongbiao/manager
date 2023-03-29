#include <DDialog>
#include <QFormLayout>
#include <DFileChooserEdit>

#include "envpage.h"

EnvPage::EnvPage(QWidget *parent) : QWidget(parent)
{
    this->resize(parent->size());

    sqliteDB = new QSqlDatabase(QSqlDatabase::database("sqlite"));
    query = new QSqlQuery(*sqliteDB);

    initUI();
}

void EnvPage::initUI()
{
    QStringList labelList;  // 表头标签
    multiSelectList = new MultiSelectList(this);

    lineEdit = new DLineEdit();
    searchBtn = new DPushButton("搜索");
    addBtn = new DPushButton("添加");
    delBtn = new DPushButton("删除");

    lineEdit->setPlaceholderText("请输入环境名");
    lineEdit->setFixedWidth(200);

    searchBtn->setFixedSize(60,35);
    searchBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; font-size:15px;");
    //    connect(searchBtn,&QPushButton::clicked,this,&Container::SearchContainer);

    addBtn->setFixedSize(60,35);
    addBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; font-size:15px;");
    connect(addBtn, &DPushButton::clicked, this, &EnvPage::addDialog);

    delBtn->setFixedSize(60, 35);
    delBtn->setStyleSheet("color: #FFFFFF; background-color: #F56C6C; border-radius: 5; border: 0px; height: 30px; width: 30px; font-size:15px;");
    connect(delBtn, &DPushButton::clicked, this, [=](){

    });

    labelList << "环境名"
              << "安装路径"
              << "启动命令"
              << "操作";
    multiSelectList->addOpLineEdit(lineEdit);
    multiSelectList->addOpButton(searchBtn);
    multiSelectList->addOpButton(addBtn);
    multiSelectList->addOpButton(delBtn);
    multiSelectList->setColumnCount(4);  // 设置列数
    multiSelectList->setHeaderLabels(labelList);



}

void EnvPage::addDialog()
{
    qDebug() << "[" << __FUNCTION__ <<__LINE__ << "] :"  <<  "打开添加环境的对话框";
//    DDialog *dialog = new DDialog(this);
//    DWidget *widget = new DWidget(dialog);
//    QFormLayout *layout = new QFormLayout(widget);

//    DLineEdit *envName = new DLineEdit();
//    DFileChooserEdit *chooserEdit = new DFileChooserEdit();

//    dialog->exec(); //显示对话框
}
