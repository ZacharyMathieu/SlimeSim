#include "UI/MainWindow.h"
#include "Constants.h"
#include "ui_mainwindow.h"
#include "UI/Widget.h"
#include "UI/Controller.h"

#include <QGridLayout>
#include <QTimer>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow) {
    Environment *env = new Environment();

    Widget *canvas = new Widget(this, env);

    controller = new Controller(canvas, env);
    updateParameters();

    setCentralWidget(canvas);

    startCanvasTimer();
    startParameterUpdateTimer();
}

MainWindow::~MainWindow()
{
    stopCanvasTimer();
    startParameterUpdateTimer();
    delete ui;
}

void MainWindow::animate() {
    controller->animate();
}

void MainWindow::updateParameters() {
    controller->updateParameters();
}

void MainWindow::startCanvasTimer() {
    canvasTimer = new QTimer(this);
    connect(canvasTimer, &QTimer::timeout, this, &MainWindow::animate);
    canvasTimer->start(50);
}

void MainWindow::stopCanvasTimer() {
    canvasTimer->stop();
}

void MainWindow::startParameterUpdateTimer() {
    parameterUpdateTimer = new QTimer(this);
    connect(parameterUpdateTimer, &QTimer::timeout, this, &MainWindow::updateParameters);
    parameterUpdateTimer->start(250);
}

void MainWindow::stopParameterUpdateTimer() {
    parameterUpdateTimer->stop();
}
