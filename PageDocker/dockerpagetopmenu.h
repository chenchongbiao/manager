#ifndef DOCKERPAGETOPMENU_H
#define DOCKERPAGETOPMENU_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>

class DockerPageTopMenu : public QWidget
{
    Q_OBJECT
public:
    explicit DockerPageTopMenu(QWidget *parent = nullptr);

    void checkMenu(QPushButton *btn,bool isCheck);
    void chooseLeftMenu(int index);         // 菜单切换
    QPushButton* getContainer();            // 获取容器按钮
    QPushButton* getImages();               // 获取镜像按钮
    QPushButton* getNet();                  // 获取网络按钮
    QPushButton* getVolume();               // 获取存储卷按钮
    QPushButton* getWareHouse();            // 获取仓库按钮
    QPushButton* getSetting();              // 获取设置按钮


private:
    void initUI(QWidget *parent = nullptr);

private:
    QWidget *topMenuWidget;
    QList<QPushButton *> topMenuList;        // 顶部菜单列表
    QPushButton *container;                  // 容器
    QPushButton *images;                     // 镜像
    QPushButton *net;                        // 网络
    QPushButton *volume;                     // 存储卷
    QPushButton *wareHouse;                  // 仓库
    QPushButton *setting;                    // 设置
    QHBoxLayout *topMenuWidgetLayout;        // 垂直布局
};

#endif // DOCKERPAGETOPMENU_H
