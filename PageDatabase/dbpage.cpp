#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>

#include "dbpage.h"

DBPage::DBPage(QWidget *parent) :
    QWidget (parent)
{
    this->resize(parent->size());
    initUI();
    initDB();
}

void DBPage::initUI()
{
    mainLayout = new QVBoxLayout(this);  // 主要布局 垂直布局
    stackedWidget = new QStackedWidget();
    stackedWidget->resize(this->width(), 500);
    mysql = new MultiSelectList(stackedWidget);  // mysql的多选列表
    mongodb = new MultiSelectList(stackedWidget);
    DFrame *subFrame = new DFrame(this);
    subMenu = new DHBoxWidget(subFrame);  // 水平的子菜单
    QStringList labelList;  // 表头标签

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
            DBPage::chooseMenu(index);
        });

        subMenu->addWidget(btn);
        topMenuList << btn;
    };

    addMenu("MySQL", 0);
    addMenu("MongoDB", 1);
    addMenu("Redis", 2);
    addMenu("SQLite", 3);
    onMenuCheck(topMenuList.at(0));

    labelList << "数据库名"
              << "用户名"
              << "密码"
              << "备份"
              << "操作";
    stackedWidget->addWidget(mysql);
    stackedWidget->addWidget(mongodb);

    mysql->resize(stackedWidget->size());
    mysql->setColumnCount(5);  // 设置列数
    mysql->setHeaderLabels(labelList);  // 设置标签
//    mysql->setHeader(mysql->getHeader());  // 设置表头

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
    // 先连接mysql
    // 这里会addDatabase会添加多个数据库 需要使用第二个参数 加上自定义连接名
    qDebug() << "[" << __FUNCTION__ <<__LINE__ << "] :" << "初始化数据库";
    QSqlDatabase mysqlDB = QSqlDatabase::addDatabase("QMYSQL", "mysql");
    mysqlDB.setHostName("127.0.0.1");  //连接本地主机
    mysqlDB.setPort(3306);
    mysqlDB.setDatabaseName("mysql");
    mysqlDB.setUserName("root");
    mysqlDB.setPassword("123456");

    bool ok = mysqlDB.open();
    if (ok){
        qDebug()<<"数据库打开成功：";
        // 读取数据库中刚才创建的数据
        QSqlQuery query(mysqlDB); //需要在构造函数里指定我们上边的数据库变量。
//        QString sql = "SHOW DATABASES WHERE `Database` NOT LIKE 'information_schema' AND `Database` NOT LIKE 'performance_schema' AND `Database` NOT LIKE 'sys';";
        // 这里过滤一下自带的数据库
        QString sql = QLatin1String("SHOW DATABASES "\
                       "WHERE "\
                       "`Database` NOT LIKE 'information_schema' "\
                      "AND "\
                       "`Database` NOT LIKE 'performance_schema' "\
                      "AND "\
                       "`Database` NOT LIKE 'sys' "\
                      "AND "\
                       "`Database` NOT LIKE 'mysql';");
//        qDebug() << "sql :" << sql;

        query.exec(sql);
        while(query.next())
        {
            qDebug() << query.value("Database").toString();

        }
    }
    else {
        qDebug() <<"数据库打开错误：" << mysqlDB.lastError().text();
    }
}

