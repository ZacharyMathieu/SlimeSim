#ifndef WIDGET_H
#define WIDGET_H

#include "Environment.h"

#include <QWidget>
#include <QPainter>

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr, Environment *environment = nullptr);
private:
    Environment *env;
    EnvironmentData *envData;
    int gridWidth, gridHeight, pixelWidth, pixelHeight;

    void paintEvent(QPaintEvent *event) override;

    void updatePixelSize();
};

#endif // WIDGET_H
