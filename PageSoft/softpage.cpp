#include <dboxwidget.h>
#include <DSwitchButton>

#include "softpage.h"

SoftPage::SoftPage(QWidget *parent) : QWidget(parent)
{
    this->resize(parent->size());

    sqliteDB = new QSqlDatabase(QSqlDatabase::database("sqlite"));
    query = new QSqlQuery(*sqliteDB);

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

    labelList << "软件名称"
              << "说明"
              << "首页显示"
              << "操作";
    multiSelectList->addOpLineEdit(lineEdit);
    multiSelectList->addOpButton(searchBtn);
    multiSelectList->setColumnCount(4);  // 设置列数
    multiSelectList->setHeaderLabels(labelList);

//    query->exec("CREATE TABLE IF NOT EXISTS software (id INTEGER PRIMARY KEY, soft_name TEXT, description TEXT, is_installed INTEGER)");

//    QString sqlFilePath = QDir::homePath()+"/.config/manager/data/software.sql";
//    // 从SQL文件中读取数据表并创建
//    QFile file(sqlFilePath);
//    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//        qDebug() << "software.sql文件打开错误!";
//    } else {
//        QString sql = file.readAll();
//        // 分行运行
//        QStringList sqlStatements = sql.split(";");
//        foreach (QString sqlStatement, sqlStatements) {
//            sqlStatement = sqlStatement.trimmed();
//            if (!sqlStatement.isEmpty()) {
//                query->exec(sqlStatement);
//            }
//        }
//    }

    query->exec("SELECT soft_name, description, is_lock, is_installed FROM software");
    int rowCount = 0;

    while (query->next()) {
        QString softName = query->value(0).toString();
        QString descrip = query->value(1).toString();
        int isLock = query->value(2).toInt();
        int isInstalled = query->value(3).toInt();

        DHBoxWidget *boxWidget = new DHBoxWidget();
        QCheckBox *checkBox = new QCheckBox(boxWidget);
        QTableWidgetItem *softNameItem = new QTableWidgetItem(softName);
        QTableWidgetItem *descripItem = new QTableWidgetItem(descrip);
//        DSwitchButton *lockBtn = new DSwitchButton();
        DHBoxWidget *lockBtnWidget = new DHBoxWidget();
        DPushButton *lockBtn = new DPushButton();

        DHBoxWidget *opWidget = new DHBoxWidget();
        DPushButton *settingBtn = new DPushButton("设置");

        boxWidget->addWidget(checkBox);
        boxWidget->layout()->setMargin(0);
        boxWidget->layout()->setAlignment(checkBox, Qt::AlignCenter);

        softNameItem->setTextColor(Qt::black);
        descripItem->setTextColor(Qt::black);

        settingBtn->setFixedSize(60,35);
        settingBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; font-size:15px;");
        opWidget->addWidget(settingBtn);

        lockBtn->setFixedSize(60,35);
        if (isLock) {
            lockBtn->setChecked(true);
            lockBtn->setText("是");
            lockBtn->setStyleSheet("color: #FFFFFF; background-color: #1E90FF; border-radius: 5; border: 0px; font-size:15px;");
        } else {
            lockBtn->setText("否");
            lockBtn->setStyleSheet("color: #FFFFFF; background-color: #F56C6C; border-radius: 5; border: 0px; font-size:15px;");
        }
        lockBtnWidget->addWidget(lockBtn);
        lockBtnWidget->layout()->setMargin(0);
        lockBtnWidget->layout()->setAlignment(checkBox, Qt::AlignCenter);

        multiSelectList->setRowCount(rowCount+1);
        multiSelectList->getTable()->setCellWidget(rowCount, 0, boxWidget);
        multiSelectList->getTable()->setItem(rowCount, 1, softNameItem);
        multiSelectList->getTable()->setItem(rowCount, 2, descripItem);
        multiSelectList->getTable()->setCellWidget(rowCount, 3, lockBtnWidget);
        multiSelectList->getTable()->setCellWidget(rowCount, 4, opWidget);
        multiSelectList->getTable()->setRowHeight(rowCount, 45);

        rowCount++;
    }
}
