#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "MainCanvas.h"

#include <QGridLayout>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    MainCanvas *mainCanvas = new MainCanvas(this);

    setCentralWidget(mainCanvas);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, mainCanvas, &MainCanvas::refresh);

    startLoop();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startLoop() {
    timer->start(DISPLAY_REFRESH_PERIOD_MS);
}

void MainWindow::stopLoop() {
    timer->stop();
}

