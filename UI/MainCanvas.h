#ifndef WIDGET_H
#define WIDGET_H

#include "UI/UserInterface.h"

#include <QWidget>
#include <QPainter>

class MainCanvas : public QWidget
{
    Q_OBJECT
public:
    explicit MainCanvas(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;

    void refresh();
private:
    UserInterface *interface;
    QTimer *timer;
};

#endif // WIDGET_H
