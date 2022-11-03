//
// Created by zwazo on 2022-09-24.
//

#include "PheromoneGrid.h"
#include "Random.h"
#include "Constants.h"

#include <iostream>

PheromoneGrid::PheromoneGrid(int width, int height) {
    grid = new std::vector<std::vector<Pheromone*>>();

    for (int y = 0; y < height; y++) {
        std::vector<Pheromone*> v = std::vector<Pheromone*>();
        for (int x = 0; x < width; x++) {
            v.push_back(new Pheromone());
        }
        grid->push_back(v);
    }

    for (int i = 0; i < RANDOM_NATURAL_PHEROMONES_COUNT; i++) {
        int x = (int) (Random::getRandomDouble() * width);
        int y = (int) (Random::getRandomDouble() * height);

        grid->at(y).at(x)->deactivate();
        grid->at(y).at(x)->level = NATURAL_PHEROMONES_STRENGTH;
    }
}

void PheromoneGrid::update() {
    for (std::vector<Pheromone*> &line: *grid) {
        for (Pheromone *pheromone: line) {
            pheromone->diffuse();
        }
    }
}

void PheromoneGrid::setSlimeLevel(int x, int y, int level) {
    grid->at(y).at(x)->setSlimeLevel(level);
}

int PheromoneGrid::getSlimeLevel(int x, int y) {
    return grid->at(y).at(x)->level;
}

void PheromoneGrid::setSlimeId(int x, int y, long id) {
    grid->at(y).at(x)->slimeId = id;
}

std::vector<std::vector<Pheromone*>> *PheromoneGrid::getGrid() {
    return grid;
}
