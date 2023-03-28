#include "UI/Widget.h"
#include "UI/Controller.h"

#include <iostream>

#include "Constants.h"

Widget::Widget(QWidget *parent, Environment *environment) : QWidget{parent} {
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    env = environment;
    canvasWidth = this->width();
    canvasHeight = this->height();
    pixelWidth = std::max(this->width() / env->getWidth(), 1);
    pixelHeight = std::max(this->height() / env->getHeight(), 1);
}

void Widget::paintEvent(QPaintEvent *event) {
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(0, 0, canvasWidth, canvasHeight, QColor(0, 0, 0));

    int envWidth = env->getWidth();
    int envHeight = env->getHeight();

    auto pg = env->getPheromoneGrid()->getGrid();

#ifdef DISPLAY_PHEROMONES
    for (int y = 0; y < envHeight; y++) {
        for (int x = 0; x < envWidth; x++) {
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
    for (Slime *slime : *env->getSlimeVector()) {
        painter.fillRect(slime->getX() * pixelWidth, slime->getY() * pixelHeight, DISPLAY_SLIME_SIZE, DISPLAY_SLIME_SIZE,
                         DISPLAY_SLIME_COLOR);
    }
#endif

    painter.end();
}
