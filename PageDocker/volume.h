#ifndef VOLUME_H
#define VOLUME_H

#include <QWidget>
#include <DLineEdit>
#include <DPushButton>
#include <QCheckBox>
#include <DLabel>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include <QMenu>

#include "mlistwidget.h"
#include "dbusclient.h"

DWIDGET_USE_NAMESPACE

class Volume : public QWidget
{
    Q_OBJECT

public:
    explicit Volume(QWidget *parent = nullptr);
    void initUI();

public slots:
    void SearchVolume();                      // 搜索存储卷的点击事件
    void OpenCreateVolDialog();               // 创建存储卷的Dialog
    void CheckAllVolume();                    // 选中所有存储卷
    void CheckVolume();                       // 选择存储卷

private:
    void initOperationUI();                   // 初始化操作栏的UI
    void initColumnUI();                      // 初始化列名的UI
    void initNetworkListUI();                 // 初始化存储器列表

private:
    MListWidget *mlist;                       // 通用界面的组件

    QWidget *opWdg;                           // 操作栏部分的widget
    QWidget *colWdg;                          // 列名的widget
    QHBoxLayout *opLayout;                    // 操作栏的布局
    QHBoxLayout *colLayout;                   // 列名的布局

    DLineEdit *searchEdit;                    // 搜索框
    DPushButton *searchBtn;                   // 搜索按钮
    DPushButton *createBtn;                   // 创建存储卷按钮

    QByteArray volumeArray;                   // 从sessionbus中获取到的存储卷数据
    QCheckBox *checkAllBtn;                   // 全选按钮
    QList<QCheckBox *> checkBoxBtnList;       // 被选中的存储卷数据对应的按钮列表
};

#endif // VOLUME_H
