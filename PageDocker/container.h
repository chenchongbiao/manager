#ifndef CONTAINER_H
#define CONTAINER_H

#include <QWidget>
#include <QHBoxLayout>
#include <DLabel>
#include <DPushButton>
#include <QRadioButton>
#include <QSqlDatabase>
#include <DLineEdit>
#include <DSwitchButton>
#include <DDialog>

#include "mlistwidget.h"

DWIDGET_USE_NAMESPACE

namespace Ui {
class Container;
}

class Container : public QWidget
{
    Q_OBJECT
public:
    explicit Container(QWidget *parent = nullptr);
    ~Container();
    void OpenInfoDialog(QJsonObject obj);   // 打开信息窗口
    void OpenCreateConDialog();             // 打开创建容器的窗口
    void SwitchContainer(DSwitchButton *btn,QString id);       // DSwitch开关容器
    void initUI();

public slots:
    void StartContainer();                                // 启动容器
    void StopContainer();                                 // 停止容器
    void SearchContainer();                               // 搜索容器
    void RestartContainer();                              // 重启容器
    void CheckContainer();                                // 选中容器
    void CheckAllContainer();                             // 选中所有容器
    void RmContainer();                                   // 删除容器
    void RmContainerById(QString containerId);            // 根据id删除容器

private:   
    void initOperationUI();                 // 初始化搜索等操作部分
    void initContainerListUI();             // 初始化容器列表
    void ReInitContainerList();             // 清除列表数据，数据 重新初始化容器列表
    void initColumnUI();                    // 初始化列表的列名

private:
    Ui::Container *ui;
    MListWidget *mlist;                        // 通用界面组件
    QWidget *conBtnWidget;                     // 容器界面的操作按钮
    QWidget *columnWidget;                     // 列名
    QWidget *dockerList;                       // 容器列表
    QHBoxLayout *conBtnLayout;                 // 按钮的布局
    QHBoxLayout *columnLayout;                 // 列名的布局
    DPushButton *startBtn;                     // 启动容器
    DPushButton *stopBtn;                      // 停止容器
    DPushButton *restartBtn;                   // 重启容器
    DPushButton *deleteBtn;                    // 删除容器
    DPushButton *createBtn;                    // 创建容器
    QCheckBox *checkAllBtn;                    // 全选按钮
    DLineEdit *searchEdit;                     // 搜索框
    DPushButton *searchBtn;                    // 搜索按钮
    DLabel *name;                              // 容器名称
    DLabel *status;                            // 容器状态
    DLabel *operation;                         // 容器操作
    DLabel *image;                             // 容器镜像
//    DLabel *port;                              // 容器端口
    DLabel *contaierId;                        // 容器id
    QSqlDatabase db;                           // 数据库
    QByteArray containerArray;                 // 从sessionbus中获取到的容器数据
    QList<QCheckBox *> checkBoxBtnList;        // 被选中的容器数据
};

#endif // CONTAINER_H
