#ifndef CONTAINERINFODIALOG_H
#define CONTAINERINFODIALOG_H

#include <QWidget>
#include <QHBoxLayout>
#include <DPushButton>
#include <QVBoxLayout>
#include <DLabel>
#include <QLineEdit>
#include <QJsonObject>

DWIDGET_USE_NAMESPACE

namespace Ui {
class ContainerInfoDialog;
}

class ContainerInfoDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ContainerInfoDialog(QWidget *parent = nullptr);
    ~ContainerInfoDialog();
    void checkMenu(QPushButton *btn, bool isCheck);
    void chooseLeftMenu(int index);
    void SetContainerJson(QJsonObject containerjson);              // 设置传递过来的json数据

private:
    void initUI();
    void initBasicInfoUI();             // 初始化基本信息的UI

private:
    Ui::ContainerInfoDialog *ui;
    QWidget *topBtnWdg;                  // 顶部按钮的widget
    QHBoxLayout *topBtnWdgLayout;        // 顶部按钮水平布局
    DPushButton *basicBtn;               // 基本信息按钮
    DPushButton *netBtn;                 // 网络信息按钮
    DPushButton *volumeBtn;              // 存储信息按钮
    QList<DPushButton *> topBtnList;     // 顶部按钮列表
    int nowMenu;                         // 当前菜单
//    QWidget *basicInfoWdg;               // 基本信息的widget
//    QVBoxLayout *basicInfoWdgLayout;     // 基本信息的垂直布局
    QGridLayout  *basicInfoWdgLayout;    // 基本信息的网格布局
    DLabel *idLab;                       // 容器id的label
    QLineEdit *idEdit;                   // 容器id的edit
    DLabel *nameLab;                     // 容器名的label
    QLineEdit *nameEdit;                 // 容器名的edit
    DLabel *imgIdLab;                    // 镜像id的label
    QLineEdit *imgIdEdit;                // 镜像id的edit
    DLabel *cmdLab;                      // 启动命令的label
    QLineEdit *cmdEdit;                  // 启动命令的edit
    DLabel *createTimeLab;               // 创建时间的label
    QLineEdit *createTimeEdit;           // 创建时间的edit
    DLabel *stateLab;                    // 容器状态的label
    QLineEdit *stateEdit;                // 容器状态的edit
    DPushButton *updateNameBtn;          // 修改容器名的按钮
    int labelWidth=60;                   // label的宽度
    int labelHeight=35;                  // label的高度
    int editWidth=250;                   // edit的宽度
    int editHeight=35;                   // edit的高度
    int btnWidth=80;                     // 按钮宽度
    QJsonObject containerJson;           // 传递过来的json数据
};

#endif // CONTAINERINFODIALOG_H
