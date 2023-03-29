#include "UI/Widget.h"
#include "Constants.h"

#include <iostream>

Widget::Widget(QWidget *parent, Environment *environment) : QWidget{parent} {
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    env = environment;
    envData = env->getEnvironmentData();
    updatePixelSize();
}

void Widget::updatePixelSize() {
    gridWidth = env->getWidth();
    gridHeight = env->getHeight();
    pixelWidth = std::max(WINDOW_WIDTH / gridWidth, 1);
    pixelHeight = std::max(WINDOW_HEIGHT / gridHeight, 1);
//    pixelWidth = 1;
//    pixelHeight = 1;
}

void Widget::paintEvent(QPaintEvent *event) {
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(0, 0, this->width(), this->height(), QColor(0, 0, 0));

    int envWidth = env->getWidth();
    int envHeight = env->getHeight();

    auto pg = env->getPheromoneGrid()->getGrid();

    if (envData->display_pheromones) {
        for (int y = 0; y < envHeight; y++) {
            for (int x = 0; x < envWidth; x++) {
                auto p = pg->at(y).at(x);
                double level = std::max(((double) p->level) / envData->pheromone_max_level, 0.0);
                QColor color;
                bool colorSet = false;

                if (p->lowlight()) {
                    color = COLOR_FROM_ARRAY(envData->display_highlight_pheromone_color);
                    colorSet = true;
                }
                else if (!p->active) {
                    color = COLOR_FROM_ARRAY(envData->display_inactive_pheromone_color);
                    colorSet = true;
                }
                else if (level > 0) {
                    color = DISPLAY_DEFAULT_PHEROMONE_COLOR(level);
                    colorSet = true;
                }

                if (colorSet) painter.fillRect(x * pixelWidth, y * pixelHeight, pixelWidth, pixelHeight, color);
            }
        }
    }

    if (envData->display_slime) {
        for (Slime *slime : *env->getSlimeVector()) {
            painter.fillRect(slime->getX() * pixelWidth, slime->getY() * pixelHeight,
                             envData->display_slime_size,
                             envData->display_slime_size,
                             COLOR_FROM_ARRAY(envData->display_slime_color));
        }
    }

    painter.end();
}
