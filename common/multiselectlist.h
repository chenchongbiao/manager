#ifndef MULTISELECTLIST_H
#define MULTISELECTLIST_H

#include <QWidget>
#include <DLineEdit>
#include <QVBoxLayout>
#include <DFrame>
#include <QTableWidget>
#include <QPoint>

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

private:
    void initUI();            // 初始化UI

private:
    DLineEdit *searchEdit;       // 搜索框
    CheckBoxHeaderView *header;  // 带复选框的表头
    QTableWidget *table;         // 表格
};

#endif // MULTISELECTLIST_H
