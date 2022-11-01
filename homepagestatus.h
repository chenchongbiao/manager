#ifndef HOMEPAGESTATUS_H
#define HOMEPAGESTATUS_H

#include <QWidget>

namespace Ui {
class HomePageStatus;
}

class HomePageStatus : public QWidget
{
    Q_OBJECT

public:
    explicit HomePageStatus(QWidget *parent = nullptr);
    ~HomePageStatus();

private:
    void initUI();  // 初始化界面

private:
    Ui::HomePageStatus *ui;
};

#endif // HOMEPAGESTATUS_H
