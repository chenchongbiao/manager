#include "multiselectlist.h"

MultiSelectList::MultiSelectList(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(parent->width(), parent->height());
    initUI();
}

void MultiSelectList::initUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);  // 主要布局 垂直布局
    DFrame *opFrame = new DFrame(this);  // 操作栏部分

    searchEdit = new DLineEdit();
    table = new QTableWidget(this);

    QHBoxLayout *opLayout = new QHBoxLayout(opFrame);

    searchEdit->setPlaceholderText("请输入容器名");
    searchEdit->setFixedWidth(200);
    // 初始化一个复选框表头  参数依次为复选框坐标位置 控件大小 方向以及父控件
    header = new CheckBoxHeaderView(QPoint(10, 5), QSize(20, 20), Qt::Horizontal, table);
//    table->setColumnCount(2);  // 设置列数
//    labelList.insert(0, "");  // 在第一个位置插入空字符串给复选框占位置，否则第一个标签会和复选框重叠
//    table->setHorizontalHeaderLabels(QStringList() << "" << "测试");  // 设置标签
    table->setHorizontalHeader(header);
    table->setColumnWidth(0, 20);  // 设置第0列，复选框的宽度
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);  // 设置第0列，复选框的宽度固定
//    table->setRowCount(1);  // 设置数据条数

    opFrame->setFixedSize(this->width(), 45);

    table->setFixedSize(this->width(), 500);

    opLayout->addWidget(searchEdit);
    opLayout->setAlignment(Qt::AlignLeft);
    opLayout->setContentsMargins(10, 0, 0, 0);

    mainLayout->addWidget(opFrame);
    mainLayout->addWidget(table);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(5);
}

QTableWidget* MultiSelectList::getTable()
{
    return table;
}
