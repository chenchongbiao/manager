#ifndef NETWORK_H
#define NETWORK_H

#include <QWidget>
#include <QHBoxLayout>
#include <DLineEdit>
#include <DPushButton>
#include <QDebug>
#include <DDialog>

#include "mlistwidget.h"

//DWIDGET_USE_NAMESPACE
//namespace Ui {
//class Network;
//}

class Network : public QWidget
{
    Q_OBJECT

public:
    explicit Network(QWidget *parent = nullptr);
    ~Network();
    void initUI();

public slots:
    void SearchContainer();                   // 搜索网络的点击事件
    void OpenCreateNetDialog();               // 创建网络的窗口

private:
//    Ui::Network *ui;
    QWidget *netBtnWidget;                    // 网络界面的操作按钮widget
    QHBoxLayout *netBtnLayout;                // 按钮的布局
    MListWidget *mlist;                       // 通用界面的组件
    DLineEdit *searchEdit;                    // 搜索框
    DPushButton *searchBtn;                   // 搜索按钮
    DPushButton *createBtn;                   // 创建网络按钮
    QByteArray containerArray;                // 从sessionbus中获取到的网络数据
};

#endif // NETWORK_H
