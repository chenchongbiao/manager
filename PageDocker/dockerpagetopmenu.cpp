#include <QDebug>

#include "dockerpagetopmenu.h"

DockerPageTopMenu::DockerPageTopMenu(QWidget *parent) : QWidget(parent)
{
    initUI(parent);
}

void DockerPageTopMenu::initUI(QWidget *parent)
{
    QFont font;
    font.setFamily(QString::fromUtf8("Zeniq"));
    font.setPointSize(11);
    font.setBold(false);
    font.setItalic(false);
    font.setWeight(50);

    topMenuWidget = new QWidget(parent);
    topMenuWidget->resize(parent->width(),parent->height());

    topMenuWidgetLayout = new QHBoxLayout(topMenuWidget);
    topMenuWidgetLayout->setSpacing(6);
    topMenuWidgetLayout->setContentsMargins(0, 0, 0, 0);
//    topMenuWidgetLayout->insertSpacing(0, -12);

    container = new QPushButton(topMenuWidget);
    container->setText("容器");
    topMenuWidgetLayout->addWidget(container);

    images = new QPushButton(topMenuWidget);
    images->setText("镜像");
    topMenuWidgetLayout->addWidget(images);

    net = new QPushButton(topMenuWidget);
    net->setText("网络");
    topMenuWidgetLayout->addWidget(net);

    volume = new QPushButton(topMenuWidget);
    volume->setText("存储卷");
    topMenuWidgetLayout->addWidget(volume);

    wareHouse = new QPushButton(topMenuWidget);
    wareHouse->setText("仓库");
    topMenuWidgetLayout->addWidget(wareHouse);

    setting = new QPushButton(topMenuWidget);
    setting->setText("设置");
    topMenuWidgetLayout->addWidget(setting);

    topMenuList << container
                << images
                << net
                << volume
                << wareHouse
                << setting;

    for (int i=0;i < topMenuList.count();i++)
    {
        QPushButton *btn = topMenuList.at(i);
        btn->setFont(font);
        btn->setFocusPolicy(Qt::NoFocus);  // 去掉虚线框
        checkMenu(btn,false);

        connect(btn, &QPushButton::clicked, this, [=](){
            QPushButton *curBtn = (QPushButton *)sender();  // 槽函数中调用sender函数，返回指向发送信号的对象的指针
            qDebug() << "当前按下" << curBtn->text();
            for (int i = 0; i < topMenuList.count(); i++)
            {
                QPushButton *btn = topMenuList.at(i);
                checkMenu(btn,curBtn == btn);
            }
        });
    }
    checkMenu(container,true);  // 默认选中容器
}

void DockerPageTopMenu::checkMenu(QPushButton *btn,bool isCheck)
{
    if (isCheck)
    {
        btn->setStyleSheet("color: #FFFFFF;  background-color: #0081ff; border-radius: 5; border: 0px; height: 45px;");
    } else {
        btn->setStyleSheet("color: #252525; border-radius: 5; border: 0px; height: 45px;");
    }
}

QPushButton* DockerPageTopMenu::getContainer()
{
    return this->container;
}

QPushButton* DockerPageTopMenu::getImages()
{
    return this->images;
}

QPushButton* DockerPageTopMenu::getNet()
{
    return this->net;
}

QPushButton* DockerPageTopMenu::getVolume()
{
    return this->volume;
}

QPushButton* DockerPageTopMenu::getWareHouse()
{
    return this->wareHouse;
}

QPushButton* DockerPageTopMenu::getSetting()
{
    return this->setting;
}
