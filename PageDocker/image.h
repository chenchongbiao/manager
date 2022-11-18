#ifndef IMAGE_H
#define IMAGE_H

#include <QWidget>
#include <QHBoxLayout>
#include <DLineEdit>
#include <DPushButton>
#include <QRadioButton>
#include <DLabel>

DWIDGET_USE_NAMESPACE

namespace Ui {
class Image;
}

class Image : public QWidget
{
    Q_OBJECT

public:
    explicit Image(QWidget *parent = nullptr);
    ~Image();
    void GetImageArrayFromSessionBus();  // 从sessionbus中获取镜像数据
    void GetImageListFromJson();

private:
    void initUI();
    QString formatImageSize(qint64 imgSize);
    void SearchImage();

private:
    Ui::Image *ui;
    QWidget *imgBtnWidget;                    // 镜像界面的操作按钮
    QWidget *columnWidget;                    // 列名
    QWidget *imageList;                       // 镜像列表
    QHBoxLayout *imgBtnLayout;                // 按钮的布局
    QHBoxLayout *columnLayout;                // 列名的布局
    DLineEdit *searchLine;                    // 搜索框
    DPushButton *searchBtn;                   // 搜索按钮
    DPushButton *refreshBtn;                  // 刷新按钮
    DPushButton *pullImageBtn;                // 拉取镜像按钮
    DPushButton *deleteBtn;                   // 删除按钮
    QRadioButton *checkAllBtn;                // 全选按钮
    DLabel *idLab;                            // id
    DLabel *tagsLab;                          // 标签
    DLabel *imageSizeLab;                     // 镜像尺寸
    DLabel *createTimeLab;                    // 创建时间
    DLabel *operationLab;                     // 操作
    QByteArray imageArray;                    // 从sessionbus中获取到的镜像数据
    QList<QRadioButton *> checkRadioBtnList;  // 被选中的镜像数据
};

#endif // IMAGE_H
