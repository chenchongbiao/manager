#ifndef PULLIMAGEDIALOG_H
#define PULLIMAGEDIALOG_H

#include <QWidget>
#include <QHBoxLayout>
#include <DLineEdit>
#include <DPushButton>
#include <DLabel>
#include <DMessageManager>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>

#include "mlistwidget.h"
#include "dbusclient.h"

DWIDGET_USE_NAMESPACE

//namespace Ui {
//class PullImageDialog;
//}

class PullImageDialog : public QWidget
{
    Q_OBJECT

public:
    explicit PullImageDialog(QWidget *parent = nullptr);
    ~PullImageDialog();

private:
    void initUI();                // 初始化UI
    void initOperationUI();       // 初始化操作栏的UI
    void initColumnUI();          // 初始化列名的UI
    void initImageListUI();       // 初始化镜像列表
    void ReInitContainerList();   // 重新生成列表

public slots:
    void SearchImageFromHub();    // 从镜像仓库搜索镜像

private:
//    Ui::PullImageDialog *ui;
    QWidget *opWdg;               // 操作栏的widget
    QWidget *columnWdg;           // 列名的widget
    QHBoxLayout *opWdgLayout;     // 操作栏的水平布局
    QHBoxLayout *columnLayout;    // 列名的布局
    MListWidget *mlist;           // 通用界面组件

    DLineEdit *searchEdit;        // 搜索框
    DPushButton *searchBtn;       // 搜索按钮

    QByteArray imageArray;        // 从sessionbus中获取到的镜像数据
};

#endif // PULLIMAGEDIALOG_H
