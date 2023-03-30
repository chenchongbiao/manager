#include <dboxwidget.h>
#include <DPasswordEdit>
#include <DPushButton>
#include <DLabel>
#include <DFileChooserEdit>

#include "settingspage.h"

SettingsPage::SettingsPage(QWidget *parent) : DFrame(parent)
{
    this->resize(parent->size());

    sqliteDB = new QSqlDatabase(QSqlDatabase::database("sqlite"));
    query = new QSqlQuery(*sqliteDB);

    initUI();
}

void SettingsPage::initUI()
{
    mainLayout = new QFormLayout(this);

    DHBoxWidget *passwdWidget = new DHBoxWidget(this);
    DPasswordEdit *passwdEdit = new DPasswordEdit(passwdWidget);
    DPushButton *passwdSaveButton = new DPushButton(passwdWidget);

    DHBoxWidget *installPathdWidget = new DHBoxWidget(this);
    DFileChooserEdit *chooserEdit = new DFileChooserEdit(installPathdWidget);
    DPushButton *installPathSaveButton = new DPushButton(installPathdWidget);

    passwdEdit->setToolTip("请输入密码");
    passwdSaveButton->setText("保存");
    passwdWidget->layout()->addWidget(passwdEdit);
    passwdWidget->layout()->addWidget(passwdSaveButton);
    passwdWidget->layout()->setSpacing(5);

    chooserEdit->setToolTip("请输入路径");
    installPathSaveButton->setText("保存");
    installPathdWidget->layout()->addWidget(chooserEdit);
    installPathdWidget->layout()->addWidget(installPathSaveButton);
    installPathdWidget->layout()->setSpacing(5);

    mainLayout->addRow(new DLabel("用户密码"), passwdWidget);
    mainLayout->addRow(new DLabel("软件安装路径"), installPathdWidget);


    query->exec("SELECT key, value FROM config");

    while (query->next()) {
        QString key = query->value(0).toString();
        QString value = query->value(1).toString();
        if (key == "user_passwd") {
            passwdEdit->setText(value);
        } else if (key == "install_path") {
            chooserEdit->setText(value);
        }
    }
//    QString sqlFilePath = QDir::homePath()+"/.config/manager/data/settings.sql";
//    // 从SQL文件中读取数据表并创建
//    QFile file(sqlFilePath);
//    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//        qDebug() << "settings.sql文件打开错误!";
//    } else {
//        QString sql = file.readAll();
//        // 分行运行
//        QStringList sqlStatements = sql.split(";");
//        foreach (QString sqlStatement, sqlStatements) {
//            sqlStatement = sqlStatement.trimmed();
//            qDebug() << sqlStatement;
//            if (!sqlStatement.isEmpty()) {
//                query->exec(sqlStatement);
//            }
//        }
//    }
}
