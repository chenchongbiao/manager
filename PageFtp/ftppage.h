#ifndef FTPPAGE_H
#define FTPPAGE_H

#include <QWidget>
#include <QPushButton>
#include <DDialog>
#include <DFileDialog>
#include <DWidgetUtil>
#include <QFormLayout>
#include <DFileChooserEdit>
#include <QSqlDatabase>

#include "PageDocker/mlistwidget.h"
#include "common/checkboxheaderview.h"
#include "common/multiselectlist.h"

//namespace Ui {
//class FtpPage;
//}

class FtpPage : public QWidget
{
    Q_OBJECT

public:
    explicit FtpPage(QWidget *parent = nullptr);
    ~FtpPage();
                                   
public slots:
    void addUserDialog();  // 添加Ftp用户

private:
    void initOperationUI();                        // 初始化操作栏
    void initUI();  // 初始化UI

private:
//    Ui::FtpPage *ui;
    MListWidget *mlist;             // 通用界面组件
    QWidget *opWdg;                 // 操作部分的容器
    QHBoxLayout *opLayout;          // 操作部分的布局

//    QTableWidget *tableWidget;      // 表格控件
    QSqlDatabase *sqliteDB;           // mysql的数据库连接
    QSqlQuery *query;                 // 执行语句
    QString sqlitePath;               // sqlite存储路径
};

#endif // FTPPAGE_H
