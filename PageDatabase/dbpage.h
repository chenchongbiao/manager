#ifndef DBPAGE_H
#define DBPAGE_H

#include <QWidget>
#include <dboxwidget.h>
#include <DFrame>
#include <DPushButton>
#include <QVBoxLayout>

#include "common/multiselectlist.h"

DWIDGET_USE_NAMESPACE

class DBPage : public QWidget
{
    Q_OBJECT
public:
    explicit DBPage(QWidget *parent = nullptr);

private:
    void initUI();

private:
    QVBoxLayout *mainLayout;
    MultiSelectList *multiSelectList;  // 多选列表
};

#endif // DBPAGE_H
