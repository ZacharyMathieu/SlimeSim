#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "widget.h"

#include <QGridLayout>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    Widget *canvas = new Widget(this);

    setCentralWidget(canvas);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, canvas, &Widget::animate);
    timer->start(50);
}

MainWindow::~MainWindow()
{
    delete ui;
}

