//
// Created by hello on 2021-03-13.
//

#include "Shield.h"




void Shield::printInfo() {
    Weapon::printInfo();
}




Shield::Shield(const string &name, const string &description, int buyPrice, int level, int protectValue,
                double dodgeProbability) : Weapon(name, description, buyPrice, level, 0,
                                                                    protectValue, false),
                                               dodgeProbability(dodgeProbability) {}

int Shield::getDefenceValue() {
    int result=protectValue;
    for (Diamond* d : diamondPlace) {
        result+=d->getBasePoint();
    }
    result=(int)(result/(1-dodgeProbability));   //calculate the defence value
    return result;
}

int Shield::getAttackValue() {
    return 0;
}

double Shield::getDodgeProbability() const {
    return dodgeProbability;
}

void Shield::setDodgeProbability(double dodgeProbability) {
    Shield::dodgeProbability = dodgeProbability;
}
