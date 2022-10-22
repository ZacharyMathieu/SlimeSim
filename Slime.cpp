//
// Created by zwazo on 2022-09-24.
//
#include <iostream>
#include <sstream>
#include <cmath>

#include "Slime.h"
#include "Random.h"
#include "Constants.h"

Slime::Slime(long _id) {
    id = _id;

    x = 0;
    y = 0;
    angle = 0;
    speed = SLIME_SPEED;

    lastSlimeAligned = nullptr;
}

double Slime::getX() const { return x; }

double Slime::getY() const { return y; }

long Slime::getId() const { return id; }

Slime *Slime::generateRandom(EnvironmentData* environmentData, long _id) {
    Slime *s = new Slime(_id);
    s->setRandomValues(environmentData);
    return s;
}

void Slime::setRandomValues(EnvironmentData* environmentData) {
    x = Random::getRandomDouble() * (environmentData->width - 1);
    y = Random::getRandomDouble() * (environmentData->height - 1);
    angle = Random::getRandomDouble() * (2 * M_PI);
}

void Slime::moveForward(EnvironmentData* environmentData, PheromoneGrid* grid, std::vector<Slime*> *slimes, bool _seekPheromones) {
    double xSpeed = speed * cos(angle);
    double ySpeed = speed * sin(angle);

    x += xSpeed;
    y += ySpeed;

    if (x < 0) {
#ifdef LOOP_GRID
        x += environmentData->width;
#else
        x = 0;
#endif
    } else if (x >= environmentData->width) {
#ifdef LOOP_GRID
        x -= environmentData->width;
#else
        x = environmentData->width - 1;
#endif
    }

    if (y < 0) {
#ifdef LOOP_GRID
        y += environmentData->height;
#else
        y = 0;
#endif
    } else if (y >= environmentData->height) {
#ifdef LOOP_GRID
        y -= environmentData->height;
#else
        y = environmentData->height - 1;
#endif
    }

    bool decisionDone = false;

#ifdef SLIME_AVOID_WALLS
    decisionDone = avoidWalls(xSpeed, ySpeed, environmentData);
#endif

#ifdef SLIME_SEEK_PHEROMONES
    if (_seekPheromones) {
        decisionDone = seekPheromones(environmentData, grid);
    }
#endif

#ifdef SLIME_ALIGN_DIRECTION
    if (!decisionDone) {
        decisionDone = alignDirectionWithNearbySlime(slimes);
    }
#endif

#ifdef SLIME_BIAS_DIRECTION
    if (!decisionDone) {
        turnTorwards(SLIME_BIAS_DIRECTION_X, SLIME_BIAS_DIRECTION_Y, SLIME_BIAS_ROTATION_ANGLE);
    }
#endif
}

bool Slime::avoidWalls(double xSpeed, double ySpeed, EnvironmentData *environmentData) {
    bool madeTurn = false;

    if (x < SLIME_WALL_DETECTION_RANGE) {
        madeTurn = true;
        if (ySpeed >= 0) turn(false, -SLIME_WALL_TURN_ANGLE);
        else turn(false, SLIME_WALL_TURN_ANGLE);
    } else if (x > environmentData->width - SLIME_WALL_DETECTION_RANGE) {
        madeTurn = true;
        if (ySpeed >= 0) turn(false, SLIME_WALL_TURN_ANGLE);
        else turn(false, -SLIME_WALL_TURN_ANGLE);
    } else if (y < SLIME_WALL_DETECTION_RANGE) {
        madeTurn = true;
        if (xSpeed >= 0) turn(false, SLIME_WALL_TURN_ANGLE);
        else turn(false, -SLIME_WALL_TURN_ANGLE);
    } else if (y > environmentData->height - SLIME_WALL_DETECTION_RANGE) {
        madeTurn = true;
        if (xSpeed >= 0) turn(false, -SLIME_WALL_TURN_ANGLE);
        else turn(false, SLIME_WALL_TURN_ANGLE);
    }

    return madeTurn;
}

bool Slime::seekPheromones(EnvironmentData *environmentData, PheromoneGrid *pheromoneGrid) {
    int roundedX = round(x);
    int minX = std::max(roundedX - SLIME_PHEROMONE_DETECTION_RANGE, 0);
    int maxX = std::min(roundedX + SLIME_PHEROMONE_DETECTION_RANGE, environmentData->width - 1);

    int roundedY = floor(y);
    int minY = std::max(roundedY - SLIME_PHEROMONE_DETECTION_RANGE, 0);
    int maxY = std::min(roundedY + SLIME_PHEROMONE_DETECTION_RANGE, environmentData->height - 1);

    if (M_PI / 4 <= angle && angle < 3 * M_PI / 4) {
        minY = roundedY;
    } else if (3 * M_PI / 4 <= angle && angle < 5 * M_PI / 4) {
        maxX = roundedX;
    } else if (5 * M_PI / 4 <= angle && angle < 7 * M_PI / 4) {
        maxY = roundedY;
    } else {
        minX = roundedX;
    }

    auto grid = pheromoneGrid->getGrid();

    bool pheromoneFound = false;
    std::pair<int, int> strongestPheromonePos;
    double strongestPheromoneDistance;
    int strongestPheromone = 0;
    for (int iY = minY; iY < maxY; iY++) {
        for (int iX = minX; iX < maxX; iX++) {
            Pheromone *p = grid->at(iY).at(iX);

            if (p->level >= strongestPheromone) {
#ifdef SLIME_IGNORE_SELF_PHEROMONE
                if (p->slimeId != id) {
#endif
                    if (pheromoneFound && p->level == strongestPheromone) {
                        double newDistance = sqrt(pow(iX - x, 2) + pow(iY - y, 2));
                        if (strongestPheromoneDistance < newDistance) {
                            strongestPheromonePos = std::make_pair(iX, iY);
                            strongestPheromoneDistance = newDistance;
                        }
                    } else {
                        pheromoneFound = true;
                        strongestPheromone = p->level;
                        strongestPheromonePos = std::make_pair(iX, iY);
                        strongestPheromoneDistance = sqrt(pow(strongestPheromonePos.first - x, 2) + pow(strongestPheromonePos.second - y, 2));
                    }
#ifdef SLIME_IGNORE_SELF_PHEROMONE
                }
#endif
            }
        }
    }

    if (pheromoneFound) {
        turnTorwards(strongestPheromonePos.first, strongestPheromonePos.second, SLIME_PHEROMONE_TURN_ANGLE);
    }

    return pheromoneFound;
}

void Slime::turn(bool canBeRandom, double turnAngle) {
    if (canBeRandom && Random::getRandomBool(SLIME_RANDOM_ROTATION_CHANCE)) {
        if (Random::getRandomBool(0.5)) angle += SLIME_RANDOM_ROTATION_CHANCE;
        else angle -= SLIME_RANDOM_ROTATION_CHANCE;
    } else angle += turnAngle;

    if (2 * M_PI < angle){
        angle -= 2 * M_PI;
    } else if (angle < 0) {
        angle += 2 * M_PI;
    }
}

void Slime::turnToAngle(bool canBeRandom, double targetAngle, double maxTurnAngle) {
    if (targetAngle < angle) targetAngle += 2 * M_PI;

    if (std::abs(targetAngle - angle) > std::abs(targetAngle - (angle + (2 * M_PI))))
        targetAngle -= 2 * M_PI;

    double angleDiff = std::abs(angle - targetAngle);

    double turnAngle = std::min(maxTurnAngle, angleDiff);

    if (targetAngle > angle) turnAngle = turnAngle;
    else turnAngle = -turnAngle;

    turn(canBeRandom, turnAngle);
}

void Slime::turnTorwards(int targetX, int targetY, double maxAngle) {
    int floorX = floor(x);
    int floorY = floor(y);

    double centeredX = targetX - floorX;
    double centeredY = targetY - floorY;

    double targetAngle = atan(centeredY / centeredX);

    if (centeredX < 0) targetAngle += M_PI;

    if (targetAngle < 0) targetAngle += 2 * M_PI;

    turnToAngle(true, targetAngle, maxAngle);
}

bool Slime::alignDirectionWithNearbySlime(std::vector<Slime*> *slimes) {
    bool slimeFound = false;

//    if (lastSlimeAligned != nullptr) {
//        if (sqrt(pow(std::abs(x - lastSlimeAligned->getX()), 2) + pow(std::abs(y - lastSlimeAligned->getY()), 2)) <= SLIME_OTHER_DETECTION_RANGE) {
//            slimeFound = true;
//            alignDirectionWithSlime(lastSlimeAligned);
//        }
//    }

    if (!slimeFound) {
        for (Slime* pS : *slimes) {
            double dX = std::abs(x - pS->getX());
            double dY = std::abs(y - pS->getY());

            if (dX < SLIME_OTHER_DETECTION_RANGE && dY < SLIME_OTHER_DETECTION_RANGE) {
                if (sqrt((dX * dX) + (dY * dY)) <= SLIME_OTHER_DETECTION_RANGE) {
                    if (pS != this) {
                        slimeFound = true;
                        lastSlimeAligned = pS;
                        alignDirectionWithSlime(pS);
                        break;
                    }
                }
            }
        }
    }

    if (!slimeFound) {
        lastSlimeAligned = nullptr;
    }

    return slimeFound;
}

void Slime::alignDirectionWithSlime(Slime *slime) {
    turnToAngle(true, slime->angle, SLIME_ALIGN_TURN_ANGLE);
}

std::string Slime::getInfoString(int spacingCount) const {
    std::string spacing = std::string(spacingCount, ' ');

    std::stringstream s = std::stringstream();
    s << spacing << "Slime info:" << std::endl
      << spacing << " X: " << x << std::endl
      << spacing << " Y: " << y << std::endl
      << spacing << " Angle: " << angle << std::endl
      << spacing << " Speed: " << speed << std::endl;

    return s.str();
}
