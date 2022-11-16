#ifndef CONTAINERINFODIALOG_H
#define CONTAINERINFODIALOG_H

#include <QWidget>
#include <QHBoxLayout>
#include <DPushButton>

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

private:
    void initUI();

private:
    Ui::ContainerInfoDialog *ui;
    QWidget *topBtnWdg;                  // 顶部按钮的widget
    QHBoxLayout *topBtnWdgLayout;        // 顶部按钮水平布局
    DPushButton *basicBtn;               // 基本信息按钮
    DPushButton *netBtn;                 // 网络信息按钮
    DPushButton *volumeBtn;              // 存储信息按钮
    QList<DPushButton *> topBtnList;     // 顶部按钮列表
    int nowMenu;                         // 当前菜单
};

#endif // CONTAINERINFODIALOG_H
