#ifndef WIDGET_H
#define WIDGET_H

#include "UI/UserInterface.h"

#include <QWidget>
#include <QPainter>

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = nullptr);
    void animate();
private:
    UserInterface* interface;

    void paintEvent(QPaintEvent *event) override;
};

#endif // WIDGET_H
