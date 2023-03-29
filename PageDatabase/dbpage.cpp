#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <dboxwidget.h>
#include <DLabel>
#include <DDialog>
#include <QFormLayout>
#include <DPasswordEdit>
#include <QMenu>

#include "dbpage.h"

DBPage::DBPage(QWidget *parent) :
    QWidget (parent)
{
    this->resize(parent->size());
    initDB();
    initUI();
}

void DBPage::initUI()
{
    mainLayout = new QVBoxLayout(this);  // 主要布局 垂直布局
    stackedWidget = new QStackedWidget();
    stackedWidget->resize(this->width(), 500);
    mysqlList = new MultiSelectList(stackedWidget);  // mysql的多选列表
    mongodbList = new Mongodb(stackedWidget);
    DFrame *subFrame = new DFrame(this);
    subMenu = new DHBoxWidget(subFrame);  // 水平的子菜单
    QStringList labelList;  // 表头标签

    DLineEdit *lineEdit = new DLineEdit();
    DPushButton *searchBtn = new DPushButton("搜索");
    DPushButton *addFtpBtn = new DPushButton("添加");
    DPushButton *delFtpBtn = new DPushButton("删除");

    subFrame->setFixedSize(this->width(), 45);

//    subMenu->addWidget(new DPushButton());
    subMenu->layout()->setContentsMargins(10, 0, 0, 0);
    auto addMenu = [this](const QString name, const int index){
        DPushButton *btn = new DPushButton();

        btn->setText(name);
        btn->setFocusPolicy(Qt::NoFocus);  // 去掉虚线框
        btn->setStyleSheet("color: #252525; border-radius: 5; border: 0px; font-size: 15px;");
        btn->setFixedSize(80, 45);

        connect(btn, &DPushButton::clicked, this, [=](){
            onMenuCheck((DPushButton *)sender());
            chooseMenu(index);
        });

        subMenu->addWidget(btn);
        topMenuList << btn;
    };

    addMenu("MySQL", 0);
    addMenu("MongoDB", 1);
    addMenu("Redis", 2);
//    addMenu("SQLite", 3);
    onMenuCheck(topMenuList.at(0));

    lineEdit->setPlaceholderText("请输入数据库名");
    lineEdit->setFixedWidth(200);

    searchBtn->setFixedSize(60,35);
    searchBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; font-size:15px;");
    //    connect(searchBtn,&QPushButton::clicked,this,&Container::SearchContainer);

    addFtpBtn->setFixedSize(60,35);
    addFtpBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; font-size:15px;");
    connect(addFtpBtn, &DPushButton::clicked, this, &DBPage::addMySQLDialog);

    delFtpBtn->setFixedSize(60, 35);
    delFtpBtn->setStyleSheet("color: #FFFFFF; background-color: #F56C6C; border-radius: 5; border: 0px; height: 30px; width: 30px; font-size:15px;");
    connect(delFtpBtn, &DPushButton::clicked, this, [=](){

    });

    labelList << "数据库名"
              << "编码"
              << "用户名"
              << "密码"  
              << "操作";
    stackedWidget->addWidget(mysqlList);
    stackedWidget->addWidget(mongodbList);

    mysqlList->addOpLineEdit(lineEdit);
    mysqlList->addOpButton(searchBtn);
    mysqlList->addOpButton(addFtpBtn);
    mysqlList->addOpButton(delFtpBtn);
    mysqlList->resize(stackedWidget->size());
    mysqlList->setColumnCount(5);  // 设置列数
    mysqlList->setHeaderLabels(labelList);  // 设置标签
//    mysql->setHeader(mysql->getHeader());  // 设置表头

    sqliteQuery->exec("SELECT db_name, encode, user_name, passwd FROM mysql_list;");
    int rowCount = 0;

    while(sqliteQuery->next())
    {
        QString dbName = sqliteQuery->value(0).toString();
        QString encode = sqliteQuery->value(1).toString();
        QString userName = sqliteQuery->value(2).toString();
        QString passwd = sqliteQuery->value(3).toString();

        // 添加复选框控件
        DHBoxWidget *boxWidget = new DHBoxWidget();
        QCheckBox *checkBox = new QCheckBox(boxWidget);
        DLabel *dbNameLabel = new DLabel();
        DLabel *encodeLabel = new DLabel();
        DLabel *userNameLabel = new DLabel();
        DLineEdit *passwdEdit = new DLineEdit();
        DHBoxWidget *opWidget = new DHBoxWidget();
        DPushButton *updatePasswdBtn = new DPushButton("改密");
        DPushButton *delDBBtn = new DPushButton("删除");

        boxWidget->addWidget(checkBox);
        boxWidget->layout()->setAlignment(checkBox, Qt::AlignCenter);
        boxWidget->layout()->setMargin(0);

        dbNameLabel->setText(dbName);
        encodeLabel->setText(encode);
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

        mysqlList->setRowCount(rowCount+1);
        mysqlList->getTable()->setCellWidget(rowCount, 0, checkBox);
        mysqlList->getTable()->setCellWidget(rowCount, 1, dbNameLabel);
        mysqlList->getTable()->setCellWidget(rowCount, 2, encodeLabel);
        mysqlList->getTable()->setCellWidget(rowCount, 3, userNameLabel);
        mysqlList->getTable()->setCellWidget(rowCount, 4, passwdEdit);
        mysqlList->getTable()->setCellWidget(rowCount, 5, opWidget);
        mysqlList->getTable()->setRowHeight(rowCount, 45);

        rowCount++;
    }

    mainLayout->addWidget(subFrame);
    mainLayout->addWidget(stackedWidget);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(5);
}

void DBPage::chooseMenu(int index)  // 菜单切换逻辑
{
    nowMenu = index;
    stackedWidget->setCurrentIndex(index);
}

void DBPage::onMenuCheck(DPushButton *curBtn)
{
    qDebug() << "当前按下" << curBtn->text();
    for (int i = 0; i < topMenuList.count(); i++)
    {
        QPushButton *btn = topMenuList.at(i);
        if (btn == curBtn)
        {
            btn->setStyleSheet("color: #FFFFFF;  background-color: #0081ff; border-radius: 5; border: 0px; font-size: 15px;");
        } else {
            btn->setStyleSheet("color: #252525; border-radius: 5; border: 0px; font-size: 15px;");
        }
    }
}

void DBPage::initDB()
{
    /**
      QtSql数据库的三种创建方式 https://blog.csdn.net/zjjsd195/article/details/124602708
      C++Qt开发——操作MySQL数据库 https://blog.csdn.net/m0_60259116/article/details/127854225
      Linux系统下安装MySQL及QT数据库编程 https://blog.csdn.net/weixin_45457363/article/details/127645570
      这里会addDatabase会添加多个数据库 需要使用第二个参数 加上自定义连接名
    */
    qDebug() << "[" << __FUNCTION__ <<__LINE__ << "] :" << "初始化数据库";

    sqliteDB = new QSqlDatabase(QSqlDatabase::database("sqlite"));
    sqliteQuery = new QSqlQuery(*sqliteDB);

    mysqlDB = new QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL", "mysql"));
    mysqlDB->setHostName("127.0.0.1");  //连接本地主机
    mysqlDB->setPort(3306);
//    mysql->setDatabaseName("mysql");  // 指定数据库
    mysqlDB->setUserName("root");
    mysqlDB->setPassword("123456");
    mysqlQuery = new QSqlQuery(*mysqlDB); // 需要在构造函数里指定我们上边的数据库变量

//    mongoc_init(); // 初始化客户端
//    mongoc_uri_t *uri = nullptr;

//    uri = mongoc_uri_new ("mongodb://localhost:27017");
//    client = mongoc_client_new_from_uri (uri);

//    database =  mongoc_client_get_database(client, "bluesky");  // 获取数据库，如果不存在则创建

//    bson_t *create_user_cmd;
//    create_user_cmd = bson_new();
//    BSON_APPEND_UTF8(create_user_cmd, "createUser", "bluesky");
//    BSON_APPEND_UTF8(create_user_cmd, "pwd", "123456");
//    BSON_APPEND_ARR(create_user_cmd, "roles", "[{role:'readWrite', db:'bluesky'}]");

//    bson_error_t error;
//    bool success = mongoc_database_command_simple (database, create_user_cmd, nullptr, nullptr, &error);

//    if (!success) {
//        qDebug() << error.message;
//    }

//    mongoc_database_destroy (database);
//    mongoc_uri_destroy (uri);
//    mongoc_client_destroy (client);

//-------------------------------------------------------------------------------------
//    mongoc_collection_t *coll;
//    bson_t *command, reply, *insert;
//    bson_error_t error;
//    const char *uri_string = "mongodb://admin:123456@localhost:27017/?authSource=admin";
//    const char *database_name = "bluesky";
//    const char *collection_name = "users";
//    const char *username = "bluesky";
//    const char *password = "123456";
//    const char *roles[] = {"readWrite"};

//    mongoc_init();
//    /* Connect to MongoDB */
//    client = mongoc_client_new(uri_string);

//    /* Get the database and collection */
//    database = mongoc_client_get_database(client, database_name);
//    coll = mongoc_client_get_collection(client, database_name, collection_name);

//    /* Create the command to create a new user */
//    command = BCON_NEW("createUser", BCON_UTF8(username), "pwd", BCON_UTF8(password), "roles", "[", BCON_UTF8(roles[0]), "]");

//    /* Execute the command */
//    if (!mongoc_database_command_simple(database, command, nullptr, &reply, &error)) {
//        qDebug () << "Error creating user: %s\n" << error.message;
//    } else {
//        qDebug () << "User created successfully!\n";
//    }

//    /* Clean up */
//    bson_destroy(command);
//    bson_destroy(&reply);
//    mongoc_collection_destroy(coll);
//    mongoc_database_destroy(database);
//    mongoc_client_destroy(client);
//    mongoc_cleanup();

//-------------------------------------------------------------------------------------

//    mongoc_uri_destroy(uri);
//    bson_destroy(command);
//    mongoc_database_destroy(database);
//    mongoc_client_destroy(client);  // 释放资源
//    mongoc_cleanup();

//    mongoc_database_drop(database, nullptr);  // 删除数据库

//        QString sql = "SHOW DATABASES WHERE `Database` NOT LIKE 'information_schema' AND `Database` NOT LIKE 'performance_schema' AND `Database` NOT LIKE 'sys';";
        // 这里过滤一下自带的数据库
//    QString sql = QLatin1String("SHOW DATABASES "\
//                   "WHERE "\
//                   "`Database` NOT LIKE 'information_schema' "\
//                  "AND "\
//                   "`Database` NOT LIKE 'performance_schema' "\
//                  "AND "\
//                   "`Database` NOT LIKE 'sys' "\
//                  "AND "\
//                   "`Database` NOT LIKE 'mysql';");
//        qDebug() << "sql :" << sql;
    // tableWidget需要设置setRowCount才能添加数据，但是query->next()执行完才能获取数据量

}

void DBPage::initMysql()
{

}

void DBPage::addMySQLDialog()
{
    qDebug() << "[" << __FUNCTION__ <<__LINE__ << "] :"  <<  "打开添加MySQL的对话框";
    DDialog *dialog = new DDialog(this);
    DWidget *widget = new DWidget(dialog);

    QFormLayout *layout = new QFormLayout(widget);

    DLineEdit *dbName = new DLineEdit();
    DPushButton *encodeBtn = new DPushButton();
    DLineEdit *userName = new DLineEdit();
    DPasswordEdit *passwd = new DPasswordEdit();
    QMenu *encodeMenu = new QMenu(this);

    // 如果mysql_list的数据表不存在则创建。
    sqliteQuery->exec("CREATE TABLE IF NOT EXISTS mysql_list (id INTEGER PRIMARY KEY, db_name TEXT, encode TEXT, user_name TEXT, passwd TEXT)");


    connect(dbName, &DLineEdit::textChanged, this, [=](const QString &arg1){
        userName->setText(arg1);
    });

    encodeMenu->addAction("utf8mb4");
    encodeMenu->addAction("utf8");
    encodeMenu->addAction("gbk");
    encodeMenu->addAction("big5");

    encodeBtn->setText("utf8mb4");
    encodeBtn->setMenu(encodeMenu);

    for(QAction *action: encodeMenu->actions()){ // 进行槽函数连接 点击时设置按钮的文本
        connect(action, &QAction::triggered, this, [=](){
            encodeBtn->setText(action->text());
        });
    }

    layout->addRow("数据库名", dbName);
    layout->addRow("字符编码", encodeBtn);
    layout->addRow("用户名", userName);
    layout->addRow("密码", passwd);
    layout->setContentsMargins(10, 5, 10, 5);
    layout->setSpacing(10);

    dialog->addContent(widget);
    dialog->addButton("取消", false, DDialog::ButtonNormal);
    dialog->addButton("确定", true, DDialog::ButtonRecommend);

    connect(dialog->getButton(1), &DPushButton::clicked, this, [=, this](){
        // 在sqlite中插入数据
        sqliteQuery->prepare("INSERT INTO mysql_list (db_name, encode, user_name, passwd) VALUES (:db_name, :encode, :user_name, :passwd)");
        sqliteQuery->bindValue(":db_name", dbName->text());
        sqliteQuery->bindValue(":encode", encodeBtn->text());
        sqliteQuery->bindValue(":user_name", userName->text());
        sqliteQuery->bindValue(":passwd", passwd->text());
        sqliteQuery->exec();

        mysqlQuery->exec(QString("CREATE DATABASE IF NOT EXISTS %1 CHARACTER SET %2;"  // 创建了一个数据库，并指定了编码,如果该数据库已经存在，则忽略这个命令。
                         "CREATE USER '%1'@'localhost' IDENTIFIED BY '%4';"   // 创建了一个名为test，密码为123456的用户。
                         "GRANT ALL PRIVILEGES ON %3.* TO '%3'@'localhost';"  // 授予test用户对test数据库的所有权限。
                         "FLUSH PRIVILEGES;")  // 刷新了MySQL的权限缓存，以确保新的权限设置立即生效。
                         .arg(dbName->text()).arg(encodeBtn->text()).arg(userName->text()).arg(passwd->text()));
    });

    dialog->exec(); //显示对话框
}

