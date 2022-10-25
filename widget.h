#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <DBlurEffectWidget>
DWIDGET_USE_NAMESPACE

namespace Ui {
class Widget;
}

class Widget : public DBlurEffectWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
