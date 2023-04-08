//
// Created by Salman Hussain Ali on 08/04/2023.
//

#ifndef COMP_345_A1_PLAYERSTRATEGIES_H
#define COMP_345_A1_PLAYERSTRATEGIES_H

#include "../Map/Map.h"
#include "../Player/Player.h"

class PlayerStrategy {
public:
/**
* Method whose implementation varies depending on the strategy adopted.
*/
    Player * player;
    virtual void issueOrder() = 0;
    virtual vector<Territory *> toAttack() = 0;
    virtual vector<Territory *> toDefend() = 0;
};

class NeutralPlayerStrategy : public PlayerStrategy{
public:
    void issueOrder();
    vector<Territory *> toAttack();
    vector<Territory *> toDefend();
};

class CheaterPlayerStrategy : public PlayerStrategy{
public:
    void issueOrder();
    vector<Territory *> toAttack();
    vector<Territory *> toDefend();
};

class HumanPlayerStrategy : public PlayerStrategy{
public:
    void issueOrder();
    vector<Territory *> toAttack();
    vector<Territory *> toDefend();
};

class AggressivePlayerStrategy : public PlayerStrategy{
public:
    void issueOrder();
    vector<Territory *> toAttack();
    vector<Territory *> toDefend();
};

class BenevolentPlayerStrategy : public PlayerStrategy{
public:
    void issueOrder();
    vector<Territory *> toAttack();
    vector<Territory *> toDefend();
};

#endif //COMP_345_A1_PLAYERSTRATEGIES_H
