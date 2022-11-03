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
        readEnv = new Environment(SLIME_COUNT);
        writeEnv = new Environment(readEnv);
    }

    virtual void refresh() = 0;

    virtual void physics() = 0;
protected:
    Environment* readEnv;
    Environment* writeEnv;
};

#endif //SLIMESIMAPP_USERINTERFACE_H
