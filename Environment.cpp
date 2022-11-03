//
// Created by zwazo on 2022-09-24.
//

#include <sstream>
#include <iostream>

#include "Environment.h"
#include "Constants.h"
#include "Slime.h"

Environment::Environment() {
    slimeVector = new std::vector<Slime*>();
    pheromoneGrid = new PheromoneGrid(GRID_WIDTH, GRID_HEIGHT);

    environmentData = {
            .width=GRID_WIDTH,
            .height=GRID_HEIGHT
    };
}

Environment::Environment(int slimeCount) : Environment() {
    generateRandomSlime(slimeCount);
}

Environment::Environment(Environment *base) {
    slimeVector = new std::vector<Slime*>();
    pheromoneGrid = new PheromoneGrid(GRID_WIDTH, GRID_HEIGHT);

    for (Slime *s : *base->getSlimeVector()) {
        slimeVector->push_back(s->copy());
    }
}

int Environment::getWidth() const {
    return environmentData.width;
}

int Environment::getHeight() const {
    return environmentData.height;
}

std::size_t Environment::getSlimeCount() {
    return slimeVector->size();
}

std::vector<Slime*> *Environment::getSlimeVector() {
    return slimeVector;
}

PheromoneGrid *Environment::getPheromoneGrid() {
    return pheromoneGrid;
}

void Environment::moveAllSlime(Environment *e) {
    bool seekPheromones = false;

    seekPheromoneTimer = (e->seekPheromoneTimer) + 1;

    if (seekPheromoneTimer % SLIME_SEEK_PHEROMONE_PERIOD == 0) {
        seekPheromones = true;
        seekPheromoneTimer = 0;
    }

    std::vector<Slime*> *newSlimeVector = e->getSlimeVector();
    PheromoneGrid *newPheromoneGrid = e->getPheromoneGrid();

    for (int i = 0; i < slimeVector->size(); i++) {
        slimeVector->at(i)->copyValues(newSlimeVector->at(i));
        slimeVector->at(i)->moveForward(&environmentData, newPheromoneGrid, newSlimeVector, seekPheromones);
    }
}

void Environment::updatePheromones(Environment *e) {
    std::vector<Slime*> *newSlimeVector = e->getSlimeVector();
    PheromoneGrid *newPheromoneGrid = e->getPheromoneGrid();

    for (Slime *slime: *newSlimeVector) {
        pheromoneGrid->setSlimeLevel((int) slime->getX(), (int) slime->getY(),
                                     newPheromoneGrid->getSlimeLevel((int) slime->getX(), (int) slime->getY())
                                     + SLIME_PHEROMONE_LEVEL);
        pheromoneGrid->setSlimeId((int) slime->getX(), (int) slime->getY(), slime->getId());
    }

    pheromoneGrid->update();
}

void Environment::physics(Environment *e) {
    // TODO Fix this bitch
    moveAllSlime(e);
//    updatePheromones(e);
}

void Environment::generateRandomSlime(int slimeCount) {
    for (long i = 0; i < slimeCount; i++) {
        slimeVector->push_back(Slime::generateRandom(&environmentData, i));
    }
}

std::string Environment::getInfoString(int spacingCount) {
    std::string spacing = std::string(spacingCount, ' ');

    std::stringstream s = std::stringstream();
    s << spacing << "Environment info:" << std::endl
      << spacing << " Width: " << environmentData.width << std::endl
      << spacing << " Height: " << environmentData.height << std::endl
      << spacing << " Slime count: " << getSlimeCount() << std::endl
      << spacing << " Slime list:" << std::endl << std::endl;

    for (Slime *slime : *slimeVector) {
        s << spacing << slime->getInfoString(spacingCount + 2) << std::endl;
    }

    return s.str();
}
