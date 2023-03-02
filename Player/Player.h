#ifndef COMP345_PLAYER_H
#define COMP345_PLAYER_H

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../Cards/Cards.h"

using namespace std;


class Hand;
class Territory;

class Player {
public:
    string pName;
    vector<Territory* > territories;
    Hand* hand;
    OrdersList* orderList;
    int playerID;
    int reinforcementPool;

    Player(); // default constructor
    Player(string pName, int id);
    Player(const Player &player);
    ~Player();   // deconstruct
    Player& operator=(const Player &player);

    void setName(string name);
    string getName();
    void setPlayerID(int id);
    vector<Territory *> getTerritory();
    void addOwnedTerritory(Territory* t);
    Hand *getHand();
    OrdersList *getOrderList();
    void addArmies(int num);

    vector<Territory *> toDefend();
    void printDefendList(vector<Territory *> defendList);
    vector<Territory *> toAttack();
    void printAttackList(vector<Territory *> attackList);
    void printOwnedTerritoryList();
    void issueOrder(string type, int target, int from, int armyCount, int targetLocation, int fromLocation, int orderNumber);
    void printCurrentHand();

private:
    static int numPlayers;
};

#endif //COMP345_PLAYER_H
