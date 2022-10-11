#include "widget.h"
#include "UI/WindowInterface.h"

#include <iostream>

#include "Constants.h"

Widget::Widget(QWidget *parent)
    : QWidget{parent}
{
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    interface = new WindowInterface(this);
}

void Widget::animate()
{
    update();
}

void Widget::paintEvent(QPaintEvent *event)
{
    interface->physics();

    interface->displayEnvironment();
}
