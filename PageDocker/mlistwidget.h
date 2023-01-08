#ifndef MLISTWIDGET_H
#define MLISTWIDGET_H

#include <DFrame>

#include <QWidget>
#include <QFormLayout>
#include <QListWidget>

DWIDGET_USE_NAMESPACE

/*!
 *  整个docker管理的部分各界面基本类似 故封装一个类做好基本布局 其他对应位置传入widget进来
 */
namespace Ui {
class MListWidget;
}

class MListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MListWidget(QWidget *parent = nullptr);
    ~MListWidget();
    void initUI();
    DFrame* getBtnDrm();           // 返回顶部搜索栏和按钮容器的指针
    DFrame* getColDrm();           // 返回列名容器的指针
    QListWidget* getListWidget();  // 返回列表容器的指针



private:
    Ui::MListWidget *ui;
//    QFormLayout *layout;         // 界面的整体布局 使用表单布局 不同部分嵌入水平布局
};

#endif // MLISTWIDGET_H
