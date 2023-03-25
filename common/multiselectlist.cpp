#include "multiselectlist.h"

MultiSelectList::MultiSelectList(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(parent->width(), parent->height());
    initUI();
}

void MultiSelectList::initUI()
{
    mainLayout = new QVBoxLayout(this);  // 主要布局 垂直布局
    DFrame *opFrame = new DFrame(this);  // 操作栏部分

    table = new QTableWidget(this);

    opLayout = new QHBoxLayout(opFrame);

    // 初始化一个复选框表头  参数依次为复选框坐标位置 控件大小 方向以及父控件
    header = new CheckBoxHeaderView(QPoint(10, 5), QSize(20, 20), Qt::Horizontal, table);
    table->setSelectionBehavior(QAbstractItemView::SelectRows); // 设置整行选中
//    table->horizontalHeader()->setStretchLastSection(true); //设置最后一栏自适应长度
    table->setFocusPolicy(Qt::NoFocus);  // 去除选中虚线框
    table->verticalHeader()->setVisible(false);  // 无边框
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);  // 设置表格不可编辑
    table->setColumnCount(1);  // 设置列数
//    labelList.insert(0, "");  // 在第一个位置插入空字符串给复选框占位置，否则第一个标签会和复选框重叠
    table->setHorizontalHeaderLabels(QStringList() << "");  // 设置标签
    table->setHorizontalHeader(header);
    table->setColumnWidth(0, 20);  // 设置第0列，复选框的宽度
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);  // 设置第0列，复选框的宽度固定
//    table->setRowCount(1);  // 设置数据条数

    opFrame->setFixedSize(this->width(), 45);

    table->setFixedSize(this->width(), 500);

    opLayout->setAlignment(Qt::AlignLeft);
    opLayout->setContentsMargins(10, 0, 0, 0);
    opLayout->setSpacing(5);

    mainLayout->addWidget(opFrame);
    mainLayout->addWidget(table);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(5);
}

QTableWidget* MultiSelectList::getTable()
{
    return table;
}

CheckBoxHeaderView* MultiSelectList::getHeader()
{
    return header;
}

void MultiSelectList::addOpLineEdit(DLineEdit *lineEdit)
{
    opLayout->addWidget(lineEdit);
}

void MultiSelectList::addOpButton(DPushButton *button)
{
    opLayout->addWidget(button);
}

void MultiSelectList::setColumnCount(int count)
{
    table->setColumnCount(count + 1);  // 设置列数
    table->horizontalHeader()->setStretchLastSection(true); //设置最后一栏自适应长度
}

void MultiSelectList::setHeaderLabels(QStringList labelList)
{
    labelList.insert(0, "");  // 在第一个位置插入空字符串给复选框占位置，否则第一个标签会和复选框重叠
    table->setHorizontalHeaderLabels(labelList);  // 设置标签
}

void MultiSelectList::setHeader(QHeaderView *header)
{
    table->setHorizontalHeader(header);
}

void MultiSelectList::setRowCount(int count)
{
    table->setRowCount(count);  // 设置数据条数
}
