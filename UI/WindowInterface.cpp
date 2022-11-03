//
// Created by zwazo on 2022-09-24.
//

#include "WindowInterface.h"

#include <QPainter>
#include <QTimer>
#include <iostream>

WindowInterface::WindowInterface() : UserInterface() {
}

WindowInterface::WindowInterface(MainCanvas *mc) : WindowInterface() {
    mainCanvas = mc;
    auto s = mc->size();
    canvasWidth = s.width();
    canvasHeight = s.height();
    pixelWidth = std::max(s.width() / readEnv->getWidth(), 1);
    pixelHeight = std::max(s.height() / readEnv->getHeight(), 1);
}

void WindowInterface::physics() {
    writeEnv->physics(readEnv);

    Environment *temp = readEnv;
    readEnv = writeEnv;
    writeEnv = temp;
}

void WindowInterface::displayEnvironment() {
    QPainter painter;
    painter.begin(mainCanvas);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(0, 0, canvasWidth, canvasHeight,DISPLAY_BACKGROUND_COLOR);

    int width = readEnv->getWidth();
    int height = readEnv->getHeight();

    auto pg = readEnv->getPheromoneGrid()->getGrid();

#ifdef DISPLAY_PHEROMONES
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            auto p = pg->at(y).at(x);
            double level = std::max(((double) p->level) / PHEROMONE_MAX_LEVEL, 0.0);
            QColor color;
            bool colorSet = false;

            if (p->lowlight()) {
                color = DISPLAY_HIGHLIGHT_PHEROMONE_COLOR;
                colorSet = true;
            }
            else if (!p->active) {
                color = DISPLAY_INACTIVE_PHEROMONE_COLOR;
                colorSet = true;
            }
            else if (level > 0) {
                color = DISPLAY_DEFAULT_PHEROMONE_COLOR(level);
                colorSet = true;
            }

            if (colorSet) painter.fillRect(x * pixelWidth, y * pixelHeight, pixelWidth, pixelHeight, color);
        }
    }
#endif

#ifdef DISPLAY_SLIME
    for (Slime *slime : *readEnv->getSlimeVector()) {
        painter.fillRect(slime->getX() * pixelWidth, slime->getY() * pixelHeight, DISPLAY_SLIME_SIZE, DISPLAY_SLIME_SIZE,
                         DISPLAY_SLIME_COLOR);
    }
#endif

    painter.end();
}

void WindowInterface::refresh() {
    displayEnvironment();
}
