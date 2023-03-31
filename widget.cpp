#include <QListWidgetItem>
#include <QLabel>
#include <QGraphicsOpacityEffect>
#include <QAction>
#include <DDialog>
#include <QtConcurrent>
#include <QSqlDatabase>
#include <QDir>

#include "widget.h"
#include "ui_widget.h"
#include "PageHome/homepagesoftitem.h"

Widget::Widget(QWidget *parent) :
    DBlurEffectWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    initDB();
    initUI();
    connect(leftMenu->getMenuHome(), &QPushButton::clicked, this, [=](){Widget::chooseLeftMenu(0);});
    connect(leftMenu->getMenuDocker(), &QPushButton::clicked, this, [=](){Widget::chooseLeftMenu(1);});
    connect(leftMenu->getMenuFtp(), &QPushButton::clicked, this, [=](){Widget::chooseLeftMenu(2);});
    connect(leftMenu->getMenuSql(), &QPushButton::clicked, this, [=](){Widget::chooseLeftMenu(3);});
    connect(leftMenu->getMenuProgram(), &QPushButton::clicked, this, [=](){Widget::chooseLeftMenu(4);});
    connect(leftMenu->getMenuSoftware(), &QPushButton::clicked, this, [=](){Widget::chooseLeftMenu(5);});
    connect(leftMenu->getMenuSetting(), &QPushButton::clicked, this, [=](){Widget::chooseLeftMenu(6);});
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initUI()
{

    // ui初始化
    setMaskAlpha(200);  // 设置模糊窗口的不透明度，数值越低越通透
    ui->stackedWidget->setCurrentIndex(0);  // 设置首页


    titlebar = getTitlebar();
    // titlebar->setIcon(QIcon::fromTheme(""));
    titlebar->setSeparatorVisible(false);
    // 添加菜单项
    QAction *menuItem = new QAction(tr("添加菜单)"), this);
    QMenu *menu = new QMenu;
    menu->addAction(menuItem);

    titlebar->setMenu(menu);

    sytemInfo = new SystemInfo(ui->system_info);  // 系统消息

    homePageStatus = new HomePageStatus(ui->statusDfrm);  // 状态栏

    leftMenu = new LeftMenu(ui->left_menu);  // 左侧菜单
    // 加载锁定在首页的软件
//    for (int i=0;i<6;i++) {
//        HomePageSoftItem *homePageSoftItem = new HomePageSoftItem(ui->homePageSoft);  // 主页软件单条数据控件
//        QListWidgetItem *WContainerItem=new QListWidgetItem(ui->homePageSoft);
//        WContainerItem->setSizeHint(QSize(40,40));
////        WContainerItem->setToolTip(); // 提示框
//        WContainerItem->setFlags(Qt::ItemIsSelectable); // 取消选择项
//        ui->homePageSoft->setItemWidget(WContainerItem,homePageSoftItem);  // 将homePageSoftItem赋予WContainerItem
//    }
    query->exec("SELECT soft_name FROM software");
    while (query->next()) {
        QString softName = query->value(0).toString();
        HomePageSoftItem *homePageSoftItem = new HomePageSoftItem(ui->homePageSoft);  // 主页软件单条数据控件
        homePageSoftItem->setSoftName(softName);
        QListWidgetItem *WContainerItem=new QListWidgetItem(ui->homePageSoft);
        WContainerItem->setSizeHint(QSize(40,40));
        WContainerItem->setFlags(Qt::ItemIsSelectable); // 取消选择项
            ui->homePageSoft->setItemWidget(WContainerItem,homePageSoftItem);  // 将homePageSoftItem赋予WContainerItem
    }
//    chooseLeftMenu(0);  // 选择首页

    // 添加Docker页面
    dockerPage = new DockerPage(ui->page_2);

    // 添加Ftp页面
    ui->page_3->resize(740, 550);
    ftpPage = new FtpPage(ui->page_3);
//    qDebug() << "[" << __FUNCTION__ <<__LINE__ << "] :" <<  width <<  ui->page_3->height();

    ui->page_4->resize(740, 550);
    dbPage = new DBPage(ui->page_4);

    ui->page_5->resize(740, 550);
    envPage = new EnvPage(ui->page_5);

    ui->page_6->resize(740, 550);
    softPage = new SoftPage(ui->page_6);

    ui->page_7->resize(740, 550);
    settingsPage = new SettingsPage(ui->page_7);

}

void Widget::chooseLeftMenu(int index)  // 左侧菜单切换逻辑
{
    nowMenu = index;
    ui->stackedWidget->setCurrentIndex(nowMenu);
}

DTitlebar* Widget::getTitlebar()
{
    return ui->titlebar;
}


void Widget::initDB()
{
    //检测已连接的方式 - 默认连接名
    qDebug() << "[" << __FUNCTION__ <<__LINE__ << "] :" << "初始化sqlite";
    QString managerDir = QDir::homePath()+"/.config/manager/data";
    QString sqlitePath = managerDir + "/db.sqlite";
    QDir dir(managerDir);
    qDebug() << "[" << __FUNCTION__ <<__LINE__ << "] :" << "文件夹路径" << dir.dirName();

    if(!dir.exists()){ // 如果文件夹不存在，就创建它
        dir.mkpath(".");
        qDebug() << "[" << __FUNCTION__ <<__LINE__ << "] :" << "文件夹不存在，创建";
    }

    if(QSqlDatabase::contains("sqlite"))
        sqliteDB = new QSqlDatabase(QSqlDatabase::database("sqlite"));
    else
        sqliteDB = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE", "sqlite"));
    //设置数据库路径，不存在则创建
    sqliteDB->setDatabaseName(sqlitePath);

    //打开数据库
    if(sqliteDB->open()){
        qDebug() << "[" << __FUNCTION__ <<__LINE__ << "] :" << "sqlite数据库打开成功";
        query = new QSqlQuery(*sqliteDB);
    }
}
