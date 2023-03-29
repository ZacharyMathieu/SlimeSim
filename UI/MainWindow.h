#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "UI/Controller.h"
#include "UI/Widget.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Controller *controller;
    Ui::MainWindow *ui;
    QTimer *canvasTimer;
    QTimer *parameterUpdateTimer;

    void animate();
    void updateParameters();

    void startCanvasTimer();
    void stopCanvasTimer();
    void startParameterUpdateTimer();
    void stopParameterUpdateTimer();
};
#endif // MAINWINDOW_H
