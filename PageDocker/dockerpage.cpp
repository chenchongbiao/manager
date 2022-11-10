#include <QPushButton>
#include <QVBoxLayout>
#include <QGraphicsOpacityEffect>
#include <DFrame>

#include "dockerpage.h"
#include "ui_dockerpage.h"
#include "dockerpagetopmenu.h"
#include "container.h"

DockerPage::DockerPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DockerPage)
{
    ui->setupUi(this);
    initUI();
}

DockerPage::~DockerPage()
{
    delete ui;
}

void DockerPage::initUI()
{
    topMenu = new DockerPageTopMenu(ui->top_menu);
    container = new Container(ui->containerWdg);
}

void DockerPage::chooseLeftMenu(int index)  // 左侧菜单切换逻辑
{
    nowMenu = index;
    ui->stackedWidget->setCurrentIndex(nowMenu);
}
