#ifndef NETWORK_H
#define NETWORK_H

#include <QWidget>
#include <QHBoxLayout>
#include <DLineEdit>
#include <DPushButton>
#include <QDebug>
#include <DDialog>
#include <QCheckBox>
#include <DLabel>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include <QMenu>
#include <DMessageManager>

#include "mlistwidget.h"
#include "dbusclient.h"

DWIDGET_USE_NAMESPACE
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
    void SearchNetwork();                     // 搜索网络的点击事件
    void OpenCreateNetDialog();               // 创建网络的窗口
    void CheckAllNetwork();                   // 选中所有网络
    void CheckNetwork();                      // 选中单条网络

private:
    void initOperationUI();                   // 初始化操作界面
    void initColumnUI();                      // 初始化列名
    void initNetworkListUI();                 // 初始化网络列表
    void ReInitNetworkList();                 // 重新生成列表

private:
//    Ui::Network *ui;
    QWidget *netBtnWidget;                    // 网络界面的操作按钮widget
    QWidget *columnWidget;                    // 列名
    QHBoxLayout *netBtnLayout;                // 按钮的布局
    QHBoxLayout *columnLayout;                // 列名的布局
    MListWidget *mlist;                       // 通用界面的组件
    DLineEdit *searchEdit;                    // 搜索框
    DPushButton *searchBtn;                   // 搜索按钮
    DPushButton *createBtn;                   // 创建网络按钮

    QByteArray networkArray;                  // 从sessionbus中获取到的网络数据
    QCheckBox *checkAllBtn;                   // 全选按钮
    QList<QCheckBox *> checkBoxBtnList;       // 被选中的网络数据对应的按钮列表
};

#endif // NETWORK_H
