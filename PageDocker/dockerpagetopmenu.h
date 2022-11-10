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
    void chooseLeftMenu(int index);          // 菜单切换

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
