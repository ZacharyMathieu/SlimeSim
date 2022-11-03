#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "MainCanvas.h"

#include <QGridLayout>
#include <QTimer>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    MainCanvas *mainCanvas = new MainCanvas(this);

    setCentralWidget(mainCanvas);

    menuBar()->addAction("Start Display", this, &MainWindow::startDisplayLoop);
    menuBar()->addAction("Stop Display", this, &MainWindow::stopDisplayLoop);
    menuBar()->addAction("Start Physics", this, &MainWindow::startPhysicsLoop);
    menuBar()->addAction("Stop Physics", this, &MainWindow::stopPhysicsLoop);

    displayTimer = new QTimer(this);
    connect(displayTimer, &QTimer::timeout, mainCanvas, &MainCanvas::refresh);

    physicsTimer = new QTimer(this);
    connect(physicsTimer, &QTimer::timeout, mainCanvas, &MainCanvas::physics);

    startDisplayLoop();
    startPhysicsLoop();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startDisplayLoop() {
    displayTimer->start(DISPLAY_REFRESH_PERIOD_MS);
}

void MainWindow::stopDisplayLoop() {
    displayTimer->stop();
}

void MainWindow::startPhysicsLoop() {
    physicsTimer->start(PHYSICS_CALCULATION_PERIOD_MS);
}

void MainWindow::stopPhysicsLoop() {
    physicsTimer->stop();
}
