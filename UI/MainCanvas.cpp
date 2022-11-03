#include "MainCanvas.h"
#include "UI/WindowInterface.h"

#include <QTimer>
#include <iostream>

#include "Constants.h"

MainCanvas::MainCanvas(QWidget *parent)
    : QWidget{parent}
{
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    interface = new WindowInterface(this);
}

void MainCanvas::paintEvent(QPaintEvent *event) {
    interface->refresh();
}

void MainCanvas::refresh() {
    update();
}

void MainCanvas::physics() {
    interface->physics();
}
