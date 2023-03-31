#ifndef DBPAGE_H
#define DBPAGE_H

#include <QWidget>
#include <dboxwidget.h>
#include <DFrame>
#include <DPushButton>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QSqlDatabase>
#include <mongoc.h>
#include <bson.h>

#include "common/multiselectlist.h"
#include "mongodb.h"
#include "redis.h"

DWIDGET_USE_NAMESPACE

class DBPage : public QWidget
{
    Q_OBJECT
public:
    explicit DBPage(QWidget *parent = nullptr);

private:
    void initUI();
    void chooseMenu(int index);         // 菜单切换
    void onMenuCheck(DPushButton *curBtn);  // 当菜单按钮被选中
    void initDB();  // 初始化数据库
    void initMysql();  // 初始化mysql
    void addMySQLDialog();  // 添加MySQL数据库

private:
    QVBoxLayout *mainLayout;
    MultiSelectList *mysqlList;
    QStackedWidget *stackedWidget;  // 存放多页面
    DHBoxWidget *subMenu;  // 顶部的菜单的容器
    QList<DPushButton *> topMenuList;  // 顶部菜单列表
    int nowMenu;  // 当前菜单

    QSqlDatabase *mysqlDB;            // mysql的数据库连接
    QSqlQuery *mysqlQuery;            // mysql执行语句
    QSqlDatabase *sqliteDB;           // sqlite的数据库连接
    QSqlQuery *sqliteQuery;           // sqlite执行语句
    QString sqlitePath;               // sqlite存储路径
    QSqlDatabase *mongoDB;            // mongodb的数据库连接
    QSqlQuery *mongoQuery;            // mongodb执行语句

    mongoc_client_t *client;          // mongodb客户端对象
    mongoc_database_t *database;      // 创建的数据库对象

    Mongodb *mongodbList;             // mongodb的列表
    Redis *redisList;                 // redis列表

};

#endif // DBPAGE_H
