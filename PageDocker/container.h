#ifndef CONTAINER_H
#define CONTAINER_H

#include <QWidget>
#include <QHBoxLayout>
#include <DLabel>
#include <DPushButton>
#include <QRadioButton>
#include <QSqlDatabase>
#include <DLineEdit>

#include "mapper/containermapper.h"

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

public slots:
    void StartContainer();      // 启动容器
    void StopContainer();       // 停止容器
    void SearchContainer();     // 搜索容器

private:
    void initUI();
    void GetContainerArrayFromSessionBus(); // 从json数据中提取容器数据
    void GetContainerListFromJson();        // 从ContainerList字符串中提取数据

private:
    Ui::Container *ui;
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
    QRadioButton *checkAllBtn;                 // 全选按钮
    DLineEdit *searchLine;                     // 搜索框
    DPushButton *searchBtn;                    // 搜索按钮
    DLabel *name;                              // 容器名称
    DLabel *status;                            // 容器状态
    DLabel *operation;                         // 容器操作
    DLabel *image;                             // 容器镜像
//    DLabel *port;                              // 容器端口
    DLabel *contaierId;                        // 容器id
    QSqlDatabase db;                           // 数据库
    ContainerMapper containerMapper;           // container数据表操作
    QByteArray contaierArray;                  // 从sessionbus中获取到的容器数据
    QList<QRadioButton *> checkRadioBtnList;   // 被选中的容器数据
};

#endif // CONTAINER_H
