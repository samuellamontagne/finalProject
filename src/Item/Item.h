//
// Created by hello on 2021-03-13.
//

#ifndef FINALPROJECTWEEK5_ITEM_H
#define FINALPROJECTWEEK5_ITEM_H
#include <iostream>

using namespace std;

class Item {
protected:
    string name;
    string description;
    string type;
    int buyPrice;
//    int spaceNeed=0;
    int level;
public:
    int getLevel() const;

    void setType(const string &type);

    void setLevel(int level);

//    int getSpaceNeed() const;
//
//    void setSpaceNeed(int spaceNeed);

    const string &getName() const;

    void setName(const string &name);

    Item(const string &name, const string &description, int buyPrice, int level);

    const string &getDescription() const;

    void setDescription(const string &description);

    int getBuyPrice() const;

    void setBuyPrice(int buyPrice);

    virtual void printInfo()=0;

    virtual ~Item();

    virtual const string &getType() const=0;



};


#endif //FINALPROJECTWEEK5_ITEM_H
