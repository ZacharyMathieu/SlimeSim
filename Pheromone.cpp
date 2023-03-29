//
// Created by zwazo on 2022-09-24.
//

#include "Pheromone.h"

Pheromone::Pheromone(EnvironmentData *data) {
    envData = data;
}

void Pheromone::addSlimeLevel() {
    if (active) {
        level += SLIME_PHEROMONE_LEVEL;
        if (level > PHEROMONE_MAX_LEVEL) level = PHEROMONE_MAX_LEVEL;
    }
}

void Pheromone::diffuse() {
    if (active && level > 0) {
        if (PHEROMONE_MAX_LEVEL < level) level = PHEROMONE_MAX_LEVEL_RESET_VALUE;
        level -= PHEROMONE_LOW_LEVEL_DIFFUSION_MULTIPLIER * ((1 / (level + 1)) - (1 / (PHEROMONE_LOW_LEVEL_DIFFUSION_MULTIPLIER + 1)));
        level -= (PHEROMONE_HIGH_LEVEL_DIFFUSION_MULTIPLIER * (level / PHEROMONE_MAX_LEVEL)) / PHEROMONE_MAX_LEVEL;
        level -= PHEROMONE_DIFFUSION_CONSTANT;
        if (level < 0) level = 0;
    }
}

void Pheromone::highlight() {
    needHighlight = true;
}

bool Pheromone::lowlight() {
    if (needHighlight) {
        needHighlight = false;
        return true;
    }
    return false;
}

void Pheromone::deactivate() {
    active = false;
}
