#ifndef DOCKERPAGE_H
#define DOCKERPAGE_H

#include <QWidget>
#include <QSqlDatabase>

#include "dockerpagetopmenu.h"
#include "container.h"
#include "image.h"
#include "network.h"
#include "volume.h"
#include "warehouse.h"

namespace Ui {
class DockerPage;
}

class DockerPage : public QWidget
{
    Q_OBJECT

public:
    explicit DockerPage(QWidget *parent = nullptr);
    ~DockerPage();
    void chooseLeftMenu(int index);
    void initDB();

private:
    void initUI();
private:
    Ui::DockerPage *ui;
    DockerPageTopMenu *topMenu;
    Container *container;                // 容器页
    Image *image;                        // 镜像页
    Network *net;                        // 网络页
    Volume *vol;                         // 存储页
    WareHouse *ware;                     // 仓库
    int nowMenu;                         // 当前页数
    QSqlDatabase db;                     // 数据库
};

#endif // DOCKERPAGE_H
