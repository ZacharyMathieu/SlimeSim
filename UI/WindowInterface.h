//
// Created by zwazo on 2022-09-24.
//

#ifndef SLIMESIMAPP_WINDOWINTERFACE_H
#define SLIMESIMAPP_WINDOWINTERFACE_H

#include "UserInterface.h"
#include "widget.h"
#include "Constants.h"

class WindowInterface : public UserInterface {
public:
    explicit WindowInterface();

    explicit WindowInterface(Widget* w);

    void displayEnvironment() override;

    void physics() override;
private:
    Widget* widget;
    int canvasWidth, canvasHeight, pixelWidth, pixelHeight;
//    QColor* backgroud;
};


#endif //SLIMESIMAPP_WINDOWINTERFACE_H
