#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    void startDisplayLoop();
    void stopDisplayLoop();
    void startPhysicsLoop();
    void stopPhysicsLoop();
private:
    Ui::MainWindow *ui;
    QTimer *displayTimer;
    QTimer *physicsTimer;
};
#endif // MAINWINDOW_H
