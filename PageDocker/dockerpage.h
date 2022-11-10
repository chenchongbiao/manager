#ifndef DOCKERPAGE_H
#define DOCKERPAGE_H

#include <QWidget>
#include "dockerpagetopmenu.h"
#include "container.h"

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

private:
    void initUI();
private:
    Ui::DockerPage *ui;
    DockerPageTopMenu *topMenu;
    Container *container;
    int nowMenu;                             // 当前页数
};

#endif // DOCKERPAGE_H
