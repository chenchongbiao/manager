#include "tableview.h"

#include <QWidget>

TableView::TableView(const int columnCount, QStringList labelList, const int rowCount, QWidget *parent) :
    QWidget(parent),
    table(new QTableWidget(parent))
{
    // 初始化一个复选框表头  参数依次为复选框坐标位置 控件大小 方向以及父控件
    headerView = new CheckBoxHeaderView(QPoint(10, 5), QSize(20, 20), Qt::Horizontal, table);

    table->setColumnCount(columnCount);  // 设置列数
    labelList.insert(0, "");  // 在第一个位置插入空字符串给复选框占位置，否则第一个标签会和复选框重叠
    table->setHorizontalHeaderLabels(labelList);  // 设置标签
    table->setColumnWidth(0, 20);  // 设置第0列，复选框的宽度
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);  // 设置第0列，复选框的宽度固定
    table->setRowCount(rowCount);  // 设置数据条数
}
