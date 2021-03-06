//
// Created by hello on 2021-03-13.
//

#ifndef FINALPROJECTWEEK5_MERCHANDISE_H
#define FINALPROJECTWEEK5_MERCHANDISE_H

#include <map>
#include "Town.h"
#include "../Item/Item.h"
#include <iostream>
#include <vector>


using namespace std;

class Merchandise : public Town {
private:
    map<Item*,int >saleList;
public:
    Merchandise(const string &name, const string &description,const vector<Item*>&itemTotalMap);

    Merchandise(const string &name, const string &description);

    Merchandise();

    const map<Item *, int> &getSaleList() const;

    void setSaleList(const map<Item *, int> &saleList);

//    void addItem(Item* Item, int quantity);

    void printInfo() override;

    static int getRandomNumByLevel(Item* item);

    Merchandise& operator=(const Merchandise& other);

    string toSave();
};


#endif //FINALPROJECTWEEK5_MERCHANDISE_H
