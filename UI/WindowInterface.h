//
// Created by zwazo on 2022-09-24.
//

#ifndef SLIMESIMAPP_WINDOWINTERFACE_H
#define SLIMESIMAPP_WINDOWINTERFACE_H

#include "UserInterface.h"
#include "MainCanvas.h"
#include "Constants.h"

class WindowInterface : public UserInterface, public QObject{
public:
    explicit WindowInterface();

    explicit WindowInterface(MainCanvas* mc);

    void refresh() override;
private:
    MainCanvas *mainCanvas;
    int canvasWidth, canvasHeight, pixelWidth, pixelHeight;

    void displayEnvironment();

    void physics();
};


#endif //SLIMESIMAPP_WINDOWINTERFACE_H
