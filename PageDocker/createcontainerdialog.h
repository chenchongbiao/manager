#ifndef CREATECONTAINERDIALOG_H
#define CREATECONTAINERDIALOG_H

#include <QWidget>
#include <QVBoxLayout>
#include <DPushButton>

DWIDGET_USE_NAMESPACE

namespace Ui {
class CreateContainerDialog;
}

class CreateContainerDialog : public QWidget
{
    Q_OBJECT

public:
    explicit CreateContainerDialog(QWidget *parent = nullptr);
    ~CreateContainerDialog();
    void checkMenu(QPushButton *btn, bool isCheck);
    void chooseLeftMenu(int index);

private:
    void initUI();
    void initLeftMenuUI();

private:
    Ui::CreateContainerDialog *ui;
    QWidget *leftMenuWdg;                // 左侧菜单的widget
    QVBoxLayout *leftMenuWdgLayout;      // 左侧按钮的垂直布局
    DPushButton *checkImgBtn;            // 选择镜像按钮
    DPushButton *containerInfoBtn;       // 容器信息按钮
    DPushButton *portMappingBtn;         // 端口映射按钮
    DPushButton *volumeMountBtn;         // 存储挂载按钮
    QList<DPushButton *> leftBtnList;    // 顶部按钮列表
    int nowMenu;                         // 当前菜单
    int btnHeight=45;                    // 按钮宽度
};

#endif // CREATECONTAINERDIALOG_H
