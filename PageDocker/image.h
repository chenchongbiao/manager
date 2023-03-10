#ifndef IMAGE_H
#define IMAGE_H

#include <QWidget>
#include <QHBoxLayout>
#include <DLineEdit>
#include <DPushButton>
#include <QCheckBox>
#include <DLabel>
#include <DDialog>
#include <DWidgetUtil>

#include "mlistwidget.h"
#include "pullimagedialog.h"

DWIDGET_USE_NAMESPACE

//namespace Ui {
//class Image;
//}

class Image : public QWidget
{
    Q_OBJECT

public:
    explicit Image(QWidget *parent = nullptr);
    ~Image();
    void initImageListUI();              // 初始化镜像列表
    void CheckAllImage();
    QString formatImageSize(qint64 imgSize);
    void SearchImage();
    void CheckImage();
    void initUI();

private:
    void initOperationUI();                  // 初始化操作栏
    void initColumnUI();                     // 初始化列名
    void ReInitImageList();                  // 初始化镜像列表

public slots:
    void OpenSearchImageFromHubDialog();     // 打开从docker仓库搜索镜像的对话框
    void RmImageById(const QString id);      // 根据id删除镜像
    void RmImageList();                      // 删除镜像列表

private:
//    Ui::Image *ui;
    MListWidget *mlist;                       // 通用界面组件
    QWidget *imgBtnWidget;                    // 镜像界面的操作按钮
    QWidget *columnWidget;                    // 列名
    QWidget *imageList;                       // 镜像列表
    QHBoxLayout *imgBtnLayout;                // 按钮的布局
    QHBoxLayout *columnLayout;                // 列名的布局
    DLineEdit *searchEdit;                    // 搜索框
    DPushButton *searchBtn;                   // 搜索按钮
    DPushButton *refreshBtn;                  // 刷新按钮
    DPushButton *pullImageBtn;                // 拉取镜像按钮
    DPushButton *deleteBtn;                   // 删除按钮
    QCheckBox *checkAllBtn;                   // 全选按钮
    DLabel *idLab;                            // id
    DLabel *tagsLab;                          // 标签
    DLabel *imageSizeLab;                     // 镜像尺寸
    DLabel *createTimeLab;                    // 创建时间
    DLabel *operationLab;                     // 操作
    QByteArray imageArray;                    // 从sessionbus中获取到的镜像数据
    QList<QCheckBox *> checkBoxBtnList;       // 被选中的镜像数据
};

#endif // IMAGE_H
