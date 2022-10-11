//
// Created by zwazo on 2022-09-24.
//

#ifndef SLIMESIMAPP_USERINTERFACE_H
#define SLIMESIMAPP_USERINTERFACE_H

#include "Environment.h"
#include "Constants.h"

#include <utility>

class UserInterface {
public:
    explicit UserInterface() {
        env = new Environment(SLIME_COUNT);
    }

    virtual void displayEnvironment() = 0;

    virtual void physics() = 0;
protected:
    Environment *env;
};

#endif //SLIMESIMAPP_USERINTERFACE_H
