#ifndef MULTISELECTLIST_H
#define MULTISELECTLIST_H

#include <QWidget>
#include <DLineEdit>
#include <QVBoxLayout>
#include <DFrame>
#include <QTableWidget>
#include <QPoint>
#include <DPushButton>

#include "checkboxheaderview.h"

DWIDGET_USE_NAMESPACE

class MultiSelectList : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief 构造一个多选择列表 带有操作框 可以添加搜索等按钮
     * @param parent 父控件指针
     */
    explicit MultiSelectList(QWidget *parent = nullptr);

    QTableWidget* getTable();  // 获取表格控件的指针
    CheckBoxHeaderView* getHeader();    // 获取表头指针
    void addOpLineEdit(DLineEdit *lineEdit);   // 在操作栏添加一个DLineEdit控件
    void addOpButton(DPushButton *button);  // 在操作栏添加一个按钮

    void setColumnCount(int count);  // 设置列数
    void setHeaderLabels(QStringList labelList);  // 设置标签
    void setHeader(QHeaderView *header);  // 设置表头
    void setRowCount(int count);          // 设置数据条数

private:
    void initUI();            // 初始化UI

private:
    CheckBoxHeaderView *header;  // 带复选框的表头
    QTableWidget *table;         // 表格

    QVBoxLayout *mainLayout;     // 界面的主要布局
    QHBoxLayout *opLayout;       // 操作栏的布局
};

#endif // MULTISELECTLIST_H
