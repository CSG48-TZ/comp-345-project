#ifndef COMP345_PLAYER_H
#define COMP345_PLAYER_H

#endif //COMP345_PLAYER_H
#include <iostream>
#include <string>
#include <vector>
#include "../Orders/Orders.h"

using namespace std;

class Territory{};
class Hand{};

class Player {
public:
    string pName;
    vector<Territory *> territories;
    Hand* hand;
    OrdersList* orderList;
    int playerID;

    Player(); // default constructor
    Player(string pName, int id, vector<Territory *> territories, Hand * hand);
    Player(const Player &player);
    ~Player();   // deconstruct
    Player& operator=(const Player &player);

    void setName(string name);
    string getName();
    void setPlayerID(int id);
    vector<Territory *> getTerritory();
    Hand *getHand();
    OrdersList *getOrderList();

    vector<Territory *> toDefend();
    void printDefendList(vector<Territory *> defendList);
    vector<Territory *> toAttack();
    void printAttackList(vector<Territory *> attackList);
    void issueOrder(string type, int target, int from, int armyCount, int targetLocation, int fromLocation, int orderNumber);
};

