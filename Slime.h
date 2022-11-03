//
// Created by zwazo on 2022-09-24.
//

#ifndef SLIMESIM_SLIME_H
#define SLIMESIM_SLIME_H

#include "EnvironmentData.h"
#include "PheromoneGrid.h"

#include <string>

class Slime {
private :
    double x, y, angle, speed;
    long id;

    Slime *lastSlimeAligned;

    Slime(long _id, double _x, double _y, double _angle, double _speed);

    void turn(bool canBeRandom, double angle);

    void turnToAngle(bool canBeRandom, double angle, double maxTurnAngle);

    void turnTorwards(int targetX, int targetY, double angle);

    bool seekPheromones(EnvironmentData *environmentData, PheromoneGrid *grid);

    bool avoidWalls(double xSpeed, double ySpeed, EnvironmentData *environmentData);

    bool alignDirectionWithNearbySlime(std::vector<Slime*> *slimes);

    void alignDirectionWithSlime(Slime *slime);
public:
    Slime(long _id);

    Slime *copy();

    double getX() const;

    double getY() const;

    double getAngle() const;

    double getSpeed() const;

    long getId() const;

    static Slime *generateRandom(EnvironmentData *environmentData, long _id);

    void setRandomValues(EnvironmentData *environmentData);

    void copyValues(Slime *slime);

    void moveForward(EnvironmentData *environmentData, PheromoneGrid* grid, std::vector<Slime*> *slimes, bool _seekPheromones);

    std::string getInfoString(int spacingCount) const;
};

#endif //SLIMESIM_SLIME_H
