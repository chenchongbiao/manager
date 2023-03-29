#include <DDialog>
#include <QFormLayout>
#include <DFileChooserEdit>
#include <dboxwidget.h>
#include <DLabel>

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
              << "可执行文件"
              << "执行命令"
              << "操作";
    multiSelectList->addOpLineEdit(lineEdit);
    multiSelectList->addOpButton(searchBtn);
    multiSelectList->addOpButton(addBtn);
    multiSelectList->addOpButton(delBtn);
    multiSelectList->setColumnCount(4);  // 设置列数
    multiSelectList->setHeaderLabels(labelList);

    query->exec("SELECT env_name, bin_path, cmd FROM program_env");
    // tableWidget需要设置setRowCount才能添加数据，但是query->next()执行完才能获取数据量
    int rowCount = 0;

    while (query->next()) {
        QString envName = query->value(0).toString();
        QString binPath = query->value(1).toString();
        QString cmd = query->value(2).toString();

        DHBoxWidget *boxWidget = new DHBoxWidget();
        QCheckBox *checkBox = new QCheckBox(boxWidget);
        QTableWidgetItem *envNameItem = new QTableWidgetItem(envName);
        QTableWidgetItem *binPathItem = new QTableWidgetItem(binPath);
        QTableWidgetItem *cmdItem = new QTableWidgetItem(cmd);

        DHBoxWidget *opWidget = new DHBoxWidget();
        DPushButton *infoBtn = new DPushButton("信息");
        DPushButton *subTashBtn = new DPushButton("子任务");
        DPushButton *delBtn = new DPushButton("删除");

        boxWidget->addWidget(checkBox);
        boxWidget->layout()->setMargin(0);
        boxWidget->layout()->setAlignment(checkBox, Qt::AlignCenter);

        envNameItem->setTextColor(Qt::black);
        binPathItem->setTextColor(Qt::black);
        cmdItem->setTextColor(Qt::black);

        infoBtn->setFixedSize(60,35);
        infoBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; font-size:15px;");
        subTashBtn->setFixedSize(60,35);
        subTashBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; font-size:15px;");
        delBtn->setFixedSize(60,35);
        delBtn->setStyleSheet("color: #FFFFFF; background-color: #F56C6C; border-radius: 5; border: 0px; font-size:15px;");
        opWidget->layout()->setSpacing(5);
        opWidget->addWidget(infoBtn);
        opWidget->addWidget(subTashBtn);
        opWidget->addWidget(delBtn);

        multiSelectList->setRowCount(rowCount+1);
        multiSelectList->getTable()->setCellWidget(rowCount, 0, boxWidget);
        multiSelectList->getTable()->setItem(rowCount, 1, envNameItem);
        multiSelectList->getTable()->setItem(rowCount, 2, binPathItem);
        multiSelectList->getTable()->setItem(rowCount, 3, cmdItem);
        multiSelectList->getTable()->setCellWidget(rowCount, 4, opWidget);
        multiSelectList->getTable()->setRowHeight(rowCount, 45);

        rowCount++;
    }
}

void EnvPage::addDialog()
{
    qDebug() << "[" << __FUNCTION__ <<__LINE__ << "] :"  <<  "打开添加环境的对话框";
    DDialog *dialog = new DDialog(this);
    DWidget *widget = new DWidget(dialog);
    QFormLayout *layout = new QFormLayout(widget);

    DLineEdit *envName = new DLineEdit(widget);
    DFileChooserEdit *chooserEdit = new DFileChooserEdit(widget);
    DLineEdit *cmd = new DLineEdit(widget);

    // 如果ftp用户的数据表不存在则创建。
    query->exec("CREATE TABLE IF NOT EXISTS program_env (id INTEGER PRIMARY KEY, env_name TEXT, bin_path TEXT, cmd TEXT)");

    layout->addRow("环境名", envName);
    layout->addRow("可执行文件", chooserEdit);
    layout->addRow("执行命令", cmd);
    layout->setContentsMargins(10, 5, 10, 5);
    layout->setSpacing(10);

    dialog->addButton("取消", false, DDialog::ButtonNormal);
    dialog->addButton("确定", true, DDialog::ButtonRecommend);
    connect(dialog->getButton(1), &DPushButton::clicked, this, [=](){

        // 在sqlite中插入数据
        query->prepare("INSERT INTO program_env (env_name, bin_path, cmd) VALUES (:env_name, :bin_path, :cmd)");
        query->bindValue(":env_name", envName->text());
        query->bindValue(":bin_path", chooserEdit->text());
        query->bindValue(":cmd", cmd->text());
        query->exec();
    });
    dialog->addContent(widget);
    dialog->exec(); //显示对话框
}
