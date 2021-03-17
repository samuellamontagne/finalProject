// #include "Item.h"

#include "../Item/Item.h"
#include "../Item/Potion/Potion.h"
#include "../Item/Weapon/Weapon.h"
#include "../Item/Money/Gold.h"
#include <typeinfo>
#include <map>
#include <iostream>

using namespace std;

class Inventory {
private:
    int maxPlace=10; // init value
    string name;
    map<Item *, int> myItemMap;
public:
    Inventory(const string &name = "None");

    void upgradeInventory();

    int getMaxPlace() const;

    const map<Item *, int> &getMyItemMap() const;

    void setMyItemMap(const map<Item *, int> &myItemMap);

    void setMaxPlace(int maxPlace);

    const string &getName() const;

    void setName(const string &name);

    void showPotions();

    void showWeapons();

    void showMyMoney();

    void addItem(Item *item, int quantity);

    int getTotalItemQuantity();
};
