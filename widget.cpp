#include <QListWidgetItem>
#include <QLabel>
#include <QGraphicsOpacityEffect>
#include <QAction>
#include <DDialog>

#include "widget.h"
#include "ui_widget.h"
#include "homepagesoftitem.h"
#include "homepagestatus.h"
#include "systeminfo.h"

Widget::Widget(QWidget *parent) :
    DBlurEffectWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    initUI();

    connect(ui->menu_home, &QPushButton::clicked, this, [=](){Widget::chooseLeftMenu(0);});
    connect(ui->menu_docker, &QPushButton::clicked, this, [=](){Widget::chooseLeftMenu(1);});
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

    SystemInfo *sytemInfo = new SystemInfo(ui->system_info);

    HomePageStatus *homePageStatus = new HomePageStatus(ui->statusDfrm);

    // 加载锁定在首页的软件
    for (int i=0;i<6;i++) {
        HomePageSoftItem *homePageSoftItem = new HomePageSoftItem(ui->homePageSoft);  // 主页软件单条数据控件
        QListWidgetItem *WContainerItem=new QListWidgetItem(ui->homePageSoft);
        WContainerItem->setSizeHint(QSize(40,40));
//        WContainerItem->setToolTip(); // 提示框
        WContainerItem->setFlags(Qt::ItemIsSelectable); // 取消选择项
        ui->homePageSoft->setItemWidget(WContainerItem,homePageSoftItem);  // 将homePageSoftItem赋予WContainerItem
    }

    // 左侧菜单加载
    left_list[0] = ui->menu_home;
    left_list[1] = ui->menu_docker;
    left_list[2] = ui->menu_ftp;
    left_list[3] = ui->menu_sql;
    left_list[4] = ui->menu_programming;
    left_list[5] = ui->menu_software;
    left_list[6] = ui->menu_setting;

    chooseLeftMenu(0);  // 选择首页
}

void Widget::reDrawUI()  // 重新构造UI
{
    for(int i = 0;i < LEFT_MENU_NUM;i++)
    {
        left_list[i]->setFixedHeight(38);
        left_list[i]->setStyleSheet("color: #252525; border: 0px; border-radius: 8; border: 0px;");
    }
    left_list[nowMenu]->setStyleSheet("color: #FFFFFF;  background-color: #0081ff; border-radius: 8; border: 0px;");
}

void Widget::chooseLeftMenu(int index)  // 左侧菜单切换逻辑
{
    nowMenu = index;
    reDrawUI();
    ui->stackedWidget->setCurrentIndex(nowMenu);
}

DTitlebar* Widget::getTitlebar()
{
    return ui->titlebar;
}

