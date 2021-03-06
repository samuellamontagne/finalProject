//
// Created by hello on 2021-03-16.
//

#include "Gold.h"

int Gold::getValue() const {
    return value;
}

void Gold::setValue(int value) {
    Gold::value = value;
}

Gold::Gold(const string &name, const string &description, int value) : Item(name, description,value, 0),
                                                                                                value(value) {}

void Gold::printInfo() {
    cout<<"This is a "<<description<<" which is worth $"<< value;
}

const string &Gold::getType() const {
    return type;
}



