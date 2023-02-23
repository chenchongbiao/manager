#ifndef FTPPAGE_H
#define FTPPAGE_H

#include <QWidget>

#include "PageDocker/mlistwidget.h"

namespace Ui {
class FtpPage;
}

class FtpPage : public QWidget
{
    Q_OBJECT

public:
    explicit FtpPage(QWidget *parent = nullptr);
    ~FtpPage();
    void initUI();                                 // 初始化UI
private:
    void initOperationUI();                        // 初始化操作栏

private:
    Ui::FtpPage *ui;
    MListWidget *mlist;             // 通用界面组件
    QWidget *opWdg;                 // 操作部分的容器
    QHBoxLayout *opLayout;          // 操作部分的布局
};

#endif // FTPPAGE_H
