//
// Created by zwazo on 2022-09-24.
//

#ifndef SLIMESIMAPP_PHEROMONEGRID_H
#define SLIMESIMAPP_PHEROMONEGRID_H

#include "Pheromone.h"

#include <vector>
#include <string>

class PheromoneGrid {
private:
    std::vector<std::vector<Pheromone*>> *grid;
public:
    explicit PheromoneGrid(int width, int height);

    void update();

    void addSlimeLevel(int x, int y);

    void setSlimeId(int x, int y, long id);

    std::vector<std::vector<Pheromone*>> *getGrid();
};


#endif //SLIMESIMAPP_PHEROMONEGRID_H
