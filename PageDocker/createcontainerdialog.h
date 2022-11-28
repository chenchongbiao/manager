#ifndef CREATECONTAINERDIALOG_H
#define CREATECONTAINERDIALOG_H

#include <QWidget>
#include <QFormLayout>
#include <DPushButton>
#include <QLineEdit>
#include <DLabel>
#include <DLineEdit>
#include <QMenu>
#include <QCheckBox>

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
    void SearchImage();                 // 搜索容器
    void initImageListUI(); 
    QList<QString> GetTagList();        // 获取标签列表

private:
    void initUI();
    void initLeftMenuUI();              // 初始化左侧菜单的UI
    void initCheckImgUI();              // 初始化选择镜像的UI
    void initConInfoUI();               // 初始化容器信息的UI

private slots:
    void CheckImage();

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

    QHBoxLayout *columnLayout;           // 列名的布局
    QWidget *columnWidget;               // 列名的widget
    DLabel *idLab;                       // 镜像id
    DLabel *tagsLab;                     // 标签
    DLabel *imageSizeLab;                // 镜像尺寸
    DLabel *createTimeLab;               // 创建时间

    DLineEdit *searchEdit;               // 镜像搜索框
    int searchEditWidth=200;             // 搜索框的宽度
    DPushButton *searchBtn;              // 搜索按钮
    int searchBtnWidth=60;               // 搜索按钮的宽度
    int searchBtnHeight=30;              // 搜索按钮的高度
    QWidget *searchWdg;                  // 搜索框区域的widget
    QHBoxLayout *searchWdgLayout;        // 搜索框区域的布局

    QByteArray imageArray;               // 从sessionbus中获取到的镜像数据

    QString checkImage;                  // 被选中的镜像

    QFormLayout *conInfoLayout;          // 容器信息布局
    QWidget *conInfoWdg;                 // 容器信息的Widget

    DLabel *nameLab;                     // 容器名label
    QLineEdit *nameEdit;                 // 容器名edit
    DLabel *imgLab;                      // 镜像名label
    QLineEdit *imgEdit;                  // 镜像名edit
    DLabel *tagInfoLab;                  // info页的tag标签
    DPushButton *tagInfoBtn;             // 镜像标签选择按钮
    QMenu *tagMenu;                      // 标签menu
    QList<QString> tagList;              // 标签列表
    QString tag;                         // 镜像的标签
    DLabel *cmdLab;                      // 启动命令label
    QLineEdit *cmdEdit;                  // 启动命令edit
    int labelWidth=60;                   // label的宽度
    int labelHeight=35;                  // label的高度
    int editWidth=250;                   // edit的宽度
    int editHeight=35;                   // edit的高度
    QCheckBox *ttyChBox;                 // 虚拟终端的checkbox
    DLabel *ttyLab;                      // 虚拟终端的label
    QCheckBox *openStdinChBox;           // 交互模式的checkbox
    DLabel *openStdinLab;                // 交互模式的label
    QHBoxLayout *checkBoxLayout;         // checkBox的布局
    DPushButton *confirmBtn;             // 确认按钮
    int confirmBtnWidth=80;              // 确认按钮的宽
    int confirmBtnHeight=35;             // 确认按钮的高
    QHBoxLayout *confirmBtnLayout;       // 确认按钮的布局
    QByteArray imgArray;                 // 选中的镜像信息
};

#endif // CREATECONTAINERDIALOG_H
