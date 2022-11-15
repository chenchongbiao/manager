#include <QPushButton>
#include <QVBoxLayout>
#include <QGraphicsOpacityEffect>
#include <DFrame>
#include <QDir>

#include "dockerpage.h"
#include "ui_dockerpage.h"
#include "dockerpagetopmenu.h"
#include "container.h"
#include "Utils/utils.h"

DockerPage::DockerPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DockerPage)
{
    ui->setupUi(this);
    Utils::initDB(db);   // 初始化数据库
    initUI();

    connect(topMenu->getContainer(), &QPushButton::clicked, this, [=](){DockerPage::chooseLeftMenu(0);});
    connect(topMenu->getImages(), &QPushButton::clicked, this, [=](){DockerPage::chooseLeftMenu(1);});
}

DockerPage::~DockerPage()
{
    db.close();
    delete ui;
}

void DockerPage::initUI()
{
    topMenu = new DockerPageTopMenu(ui->top_menu);
    container = new Container(ui->containerWdg);
    image = new Image(ui->imagesWdg);
}

void DockerPage::chooseLeftMenu(int index)  // 左侧菜单切换逻辑
{
    nowMenu = index;
    ui->stackedWidget->setCurrentIndex(nowMenu);
}

void DockerPage::initDB()
{
    //检测已连接的方式 - 默认连接名
    QString dbusDockerDir = QDir::homePath()+"/.config/dbus-docker/data/db.sqlite";
    qDebug() <<dbusDockerDir;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else
        db = QSqlDatabase::addDatabase("QSQLITE");
    //设置数据库路径，不存在则创建
    db.setDatabaseName(dbusDockerDir);

    //打开数据库
    if(db.open()){
        qDebug()<<"数据库打开成功";
    }
}
