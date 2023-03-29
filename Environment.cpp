//
// Created by zwazo on 2022-09-24.
//

#include "Environment.h"
#include "ParameterReader.h"
#include "Slime.h"

#include <map>
#include <vector>
#include <sstream>
#include <iostream>

Environment::Environment() {
    slimeVector = new std::vector<Slime*>();

    envData = {};

    pheromoneGrid = new PheromoneGrid(envData.grid_width, envData.grid_height, &envData);

    generateRandomSlime(envData.slime_count);
}

int Environment::getWidth() const {
    return envData.grid_width;
}

int Environment::getHeight() const {
    return envData.grid_height;
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

    if (seekPheromoneTimer % envData.slime_seek_pheromones_period == 0) {
        seekPheromones = true;
        seekPheromoneTimer = 0;
    }

    for (Slime *slime: *slimeVector) {
        slime->moveForward(pheromoneGrid, getSlimeVector(), seekPheromones);
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
        slimeVector->push_back(Slime::generateRandom(i, &envData));
    }
}

std::string Environment::getInfoString(int spacingCount) {
    std::string spacing = std::string(spacingCount, ' ');

    std::stringstream s = std::stringstream();
    s << spacing << "Environment info:" << std::endl
      << spacing << " Width: " << envData.grid_width << std::endl
      << spacing << " Height: " << envData.grid_height << std::endl
      << spacing << " Slime count: " << getSlimeCount() << std::endl
      << spacing << " Slime list:" << std::endl << std::endl;

    for (Slime *slime : *slimeVector) {
        s << spacing << slime->getInfoString(spacingCount + 2) << std::endl;
    }

    return s.str();
}

void Environment::updateParam(InputParam param) {
    if (param.name == "grid_width") {
        if (envData.grid_width != param.valueNumber) {
            std::cout << "Width set to : [" << param.valueNumber << "]" << std::endl;
            envData.grid_width = param.valueNumber;
        }
    } else if (param.name == "grid_height") {
        if (envData.grid_height != param.valueNumber) {
            std::cout << "Height set to : [" << param.valueNumber << "]" << std::endl;
            envData.grid_height = param.valueNumber;
        }
    } else {
        std::cout << "UNRECOGNIZED PARAMETER: [" << param.name << "]" << std::endl;
    }
}

void Environment::updateParameters() {
    std::vector<InputParam> params = ParameterReader::read(PARAMETER_FILE_NAME);
    for (int i = 0; i < params.size(); i++) {
        updateParam(params[i]);
    }
}

EnvironmentData *Environment::getEnvironmentData() {
    return &envData;
}
