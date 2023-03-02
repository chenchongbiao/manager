#include "tableview.h"

#include <QWidget>
#include <QPushButton>

TableView::TableView(int columnCount, QStringList labelList, const int rowCount, QWidget *parent) :
    QWidget(parent),
    table(new QTableWidget(this))
{

    table->setFixedSize(parent->width(), parent->height());
    // 初始化一个复选框表头  参数依次为复选框坐标位置 控件大小 方向以及父控件
    headerView = new CheckBoxHeaderView(QPoint(10, 5), QSize(20, 20), Qt::Horizontal, table);

    table->setColumnCount(columnCount + 1);  // 设置列数
    labelList.insert(0, "");  // 在第一个位置插入空字符串给复选框占位置，否则第一个标签会和复选框重叠
    table->setHorizontalHeaderLabels(labelList);  // 设置标签
    table->setHorizontalHeader(headerView);
    table->setColumnWidth(0, 20);  // 设置第0列，复选框的宽度
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);  // 设置第0列，复选框的宽度固定
    table->setRowCount(rowCount);  // 设置数据条数

//    QCheckBox *box = new QCheckBox();
//    QWidget *widget = new QWidget;
//    QHBoxLayout *layout = new QHBoxLayout;
//    layout->addWidget(box);
//    layout->setMargin(0);
//    // 设置水平居中
//    layout->setAlignment(box, Qt::AlignCenter);
//    // 设置部件边距
//    layout->setMargin(0);
//    // 添加布局
//    widget->setLayout(layout);

//    table->setCellWidget(0, 0, widget);
//    table->setCellWidget(0, 1, new QPushButton("测试"));

}

void TableView::init()
{

}
