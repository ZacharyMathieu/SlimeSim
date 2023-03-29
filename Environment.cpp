//
// Created by zwazo on 2022-09-24.
//

#include <list>
#include <sstream>
#include <iostream>

#include "Environment.h"
#include "Constants.h"
#include "ParameterReader.h"
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

void Environment::moveAllSlime() {
    bool seekPheromones = false;

    seekPheromoneTimer++;

    if (seekPheromoneTimer % SLIME_SEEK_PHEROMONE_PERIOD == 0) {
        seekPheromones = true;
        seekPheromoneTimer = 0;
    }

    for (Slime *slime: *slimeVector) {
        slime->moveForward(&environmentData, pheromoneGrid, getSlimeVector(), seekPheromones);
    }
}

void Environment::updatePheromones() {
    for (Slime *slime: *slimeVector) {
        pheromoneGrid->addSlimeLevel((int) slime->getX(), (int) slime->getY());
        pheromoneGrid->setSlimeId((int) slime->getX(), (int) slime->getY(), slime->getId());
    }

    pheromoneGrid->update();
}

void Environment::physics() {
    moveAllSlime();
    updatePheromones();
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

void Environment::updateParameters() {
    std::list<InputParam> params = ParameterReader::read(PARAMETER_FILE_NAME);
}
