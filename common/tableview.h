#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QWidget>
#include <QTableWidget>
#include <dboxwidget.h>

#include "checkboxheaderview.h"

DWIDGET_USE_NAMESPACE

class TableView : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief 构造一个带CheckBox的表格
     * @param columnCount 列数
     * @param labelList 标签的列表
     * @param parent 父控件指针
     */
    explicit TableView(int columnCount, QStringList labelList, const int rowCount, QWidget *parent = nullptr);

    virtual void init();             // 初始化函数

private:
    DBoxWidget *opWidget;            // 操作栏用于添加搜索以及按钮控件
    CheckBoxHeaderView *headerView;  // 带复选框的表头
    QTableWidget *table;             // 表格控件
};

#endif // TABLEVIEW_H
