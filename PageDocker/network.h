#ifndef NETWORK_H
#define NETWORK_H

#include <QWidget>

//DWIDGET_USE_NAMESPACE
//namespace Ui {
//class Network;
//}

class Network : public QWidget
{
    Q_OBJECT

public:
    explicit Network(QWidget *parent = nullptr);
    ~Network();
    void initUI();

private:
//    Ui::Network *ui;
};

#endif // NETWORK_H
