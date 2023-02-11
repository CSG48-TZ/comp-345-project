#ifndef COMP345_PLAYER_H
#define COMP345_PLAYER_H

#endif //COMP345_PLAYER_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Territory{};
class Hand{};
class Orders{};
class OrdersList{};

class Player {
public:
    string pName;
    vector<Territory *> territories;
    Hand* hand;
    OrdersList* orderList;

    Player(); // default constructor
    Player(string pName, vector<Territory *> territories, Hand * hand, OrdersList * orderList);
    Player(const Player &player);
    ~Player();   // deconstruct
    Player& operator=(const Player &player);

    void setName(string name);
    string getName();
    vector<Territory *> getTerritory();
    Hand *getHand();
    OrdersList *getOrderList();

    vector<Territory *> toDefend();
    void printDefendList(vector<Territory *> defendList);
    vector<Territory *> toAttack();
    void printAttackList(vector<Territory *> attackList);
    void issueOrder();
};

