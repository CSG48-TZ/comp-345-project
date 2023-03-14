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
class OrdersList;

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
    void removeOwnedTerritory(int id);
    void clearOrdersList();
    Hand *getHand();
    void addPlayerToNegociatedList(Player* p);
    void clearNegociatedList();
    OrdersList *getOrderList();
    void addArmies(int num);

    void setConqueredFlag(bool value);
    vector<Territory *> toDefend();
    void printDefendList(vector<Territory *> defendList);
    vector<Territory *> toAttack();
    void printAttackList(vector<Territory *> attackList);
    void printOwnedTerritoryList();
    void issueOrder(string type, Player* target, int armyCount, Territory* targetLocation, Territory* fromLocation);
    void printCurrentHand();

private:
    static int numPlayers;
};

#endif //COMP345_PLAYER_H
