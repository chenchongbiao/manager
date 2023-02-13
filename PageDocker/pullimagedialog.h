#ifndef PULLIMAGEDIALOG_H
#define PULLIMAGEDIALOG_H

#include <QWidget>
#include <QHBoxLayout>
#include <DLineEdit>
#include <DPushButton>

#include "mlistwidget.h"

DWIDGET_USE_NAMESPACE

namespace Ui {
class PullImageDialog;
}

class PullImageDialog : public QWidget
{
    Q_OBJECT

public:
    explicit PullImageDialog(QWidget *parent = nullptr);
    ~PullImageDialog();

private:
    void initUI();                // 初始化UI

private:
    Ui::PullImageDialog *ui;
    QWidget *opWdg;               // 操作栏的widget
    QHBoxLayout *opWdgLayout;     // 操作栏的水平布局
    MListWidget *mlist;           // 通用界面组件

    DLineEdit *searchEdit;        // 搜索框
    DPushButton *searchBtn;       // 搜索按钮
};

#endif // PULLIMAGEDIALOG_H
