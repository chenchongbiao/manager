#ifndef HOMEPAGESOFTITEM_H
#define HOMEPAGESOFTITEM_H

#include <QWidget>

namespace Ui {
class HomePageSoftItem;
}

class HomePageSoftItem : public QWidget
{
    Q_OBJECT

public:
    explicit HomePageSoftItem(QWidget *parent = nullptr);
    ~HomePageSoftItem();

private:
    Ui::HomePageSoftItem *ui;
};

#endif // HOMEPAGESOFTITEM_H
