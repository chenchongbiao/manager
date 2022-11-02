#include <QDebug>

#include "leftmenu.h"

LeftMenu::LeftMenu(QWidget *parent): QWidget (parent)
{
    initUI(parent);
}

void LeftMenu::initUI(QWidget *parent)
{
    int leftMenuBtnWidth = parent->width();
    int leftMenuBtnheight = 45;

    QFont font;
    font.setFamily(QString::fromUtf8("Zeniq"));
    font.setPointSize(11);
    font.setBold(false);
    font.setItalic(false);
    font.setWeight(50);

    leftMenuWidget = new QWidget(parent);
    leftMenuWidget->resize(parent->width(),parent->height());

    leftMenuWidgetLayout = new QVBoxLayout(leftMenuWidget);
    leftMenuWidgetLayout->setSpacing(0);
    leftMenuWidgetLayout->setContentsMargins(0, 0, 0, 0);
    leftMenuWidgetLayout->insertSpacing(0, -12);

    menuHome = new QPushButton(leftMenuWidget);
    menuHome->setText("首页");
    leftMenuWidgetLayout->addWidget(menuHome);

    menuDocker = new QPushButton(leftMenuWidget);
    menuDocker->setText("Docker");
    leftMenuWidgetLayout->addWidget(menuDocker);

    menuFtp = new QPushButton(leftMenuWidget);
    menuFtp->setText("Ftp");
    leftMenuWidgetLayout->addWidget(menuFtp);

    menuSql = new QPushButton(leftMenuWidget);
    menuSql->setText("数据库");
    leftMenuWidgetLayout->addWidget(menuSql);

    menuProgram = new QPushButton(leftMenuWidget);
    menuProgram->setText("编程环境");
    leftMenuWidgetLayout->addWidget(menuProgram);

    menuSoftware = new QPushButton(leftMenuWidget);
    menuSoftware->setText("软件安装");
    leftMenuWidgetLayout->addWidget(menuSoftware);

    menuSetting = new QPushButton(leftMenuWidget);
    menuSetting->setText("设置");
    leftMenuWidgetLayout->addWidget(menuSetting);

    leftMenuList << menuHome << menuDocker << menuFtp << menuSql << menuProgram << menuSoftware << menuSetting;
    for (int i=0;i < leftMenuList.count();i++)
    {
        QPushButton *btn = leftMenuList.at(i);
        checkMenu(btn,false);
        btn->setFont(font);

        connect(btn, &QPushButton::clicked, this, [=](){
            QPushButton *curBtn = (QPushButton *)sender();  // 槽函数中调用sender函数，返回指向发送信号的对象的指针
            qDebug() << "当前按下" << curBtn->text();
            for (int i = 0; i < leftMenuList.count(); i++)
            {
                QPushButton *btn = leftMenuList.at(i);
                checkMenu(btn,curBtn == btn);
            }
        });
    }
    checkMenu(menuHome,true);  // 默认选中首页
}

void LeftMenu::checkMenu(QPushButton *btn,bool isCheck)
{
    if (isCheck)
    {
        btn->setStyleSheet("color: #FFFFFF;  background-color: #0081ff; border-radius: 8; border: 0px;height: 45px;");
    } else {
        btn->setStyleSheet("color: #252525; border-radius: 8; border: 0px; height: 45px;");
    }
}

QPushButton* LeftMenu::getMenuHome()
{
    return this->menuHome;
}

QPushButton* LeftMenu::getMenuDocker()
{
    return this->menuDocker;
}

QPushButton* LeftMenu::getMenuFtp()
{
    return this->menuFtp;
}

QPushButton* LeftMenu::getMenuSql()
{
    return this->menuSql;
}

QPushButton* LeftMenu::getMenuProgram()
{
    return this->menuProgram;
}

QPushButton* LeftMenu::getMenuSoftware()
{
    return this->menuSoftware;
}

QPushButton* LeftMenu::getMenuSetting()
{
    return this->menuSetting;
}

