#ifndef VOLUME_H
#define VOLUME_H

#include <QWidget>
#include <DLineEdit>
#include <DPushButton>

#include "mlistwidget.h"

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

private:
    void initOperationUI();                   // 初始化操作栏的UI
    void initColumnUI();                      // 初始化列名的UI

private:
    MListWidget *mlist;                       // 通用界面的组件

    QWidget *opWdg;                           // 操作栏部分的widget
    QWidget *colWdg;                          // 列名的widget
    QHBoxLayout *opLayout;                    // 操作栏的布局
    QHBoxLayout *colLayout;                   // 列名的布局

    DLineEdit *searchEdit;                    // 搜索框
    DPushButton *searchBtn;                   // 搜索按钮
    DPushButton *createBtn;                   // 创建存储卷按钮

};

#endif // VOLUME_H
