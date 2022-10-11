//
// Created by zwazo on 2022-09-24.
//

#ifndef SLIMESIM_ENVIRONMENT_H
#define SLIMESIM_ENVIRONMENT_H

#include <vector>
#include <string>

#include "Slime.h"
#include "EnvironmentData.h"
#include "PheromoneGrid.h"

class Environment {
private:
    EnvironmentData environmentData{};
    std::vector<Slime*> *slimeVector;
    PheromoneGrid *pheromoneGrid;
    long seekPheromoneTimer = 0;
public:
    explicit Environment();

    explicit Environment(int slimeCount);

    int getWidth() const;

    int getHeight() const;

    std::size_t getSlimeCount();

    std::vector<Slime*> *getSlimeVector();

    PheromoneGrid *getPheromoneGrid();

    void moveAllSlime();

    void updatePheromones();

    void physics();

    void generateRandomSlime(int slimeCount);

    std::string getInfoString(int spacingCount);
};

#endif //SLIMESIM_ENVIRONMENT_H
