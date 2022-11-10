#ifndef CONTAINER_H
#define CONTAINER_H

#include <QWidget>
#include <QHBoxLayout>
#include <DLabel>
#include <DPushButton>
#include <QRadioButton>
#include <DLabel>

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
    void initUI();

private:
    Ui::Container *ui;
    QWidget *conBtnWidget;               // 容器界面的操作按钮
    QWidget *columnWidget;               // 列名
    QWidget *dockerList;                 // 容器列表
    QHBoxLayout *conBtnLayout;           // 按钮的布局
    QHBoxLayout *columnLayout;           // 列名的布局
    DPushButton *startBtn;               // 启动容器
    DPushButton *stopBtn;                // 停止容器
    DPushButton *restartBtn;             // 重启容器
    DPushButton *deleteBtn;              // 删除容器
    DPushButton *createBtn;              // 创建容器
    QRadioButton *checkAllBtn;           // 全选按钮
    DLabel *name;                        // 容器名称
    DLabel *status;                      // 容器状态
    DLabel *address;                     // 容器监控
    DLabel *image;                       // 容器镜像
    DLabel *port;                        // 容器端口
    DLabel *contaierId;                  // 容器id
};

#endif // CONTAINER_H
