#pragma once

#include "../Map/Map.h"
#include "../Cards/Cards.h"

class Player;

/**
 * PlayerStrategy is an abstract class. All concrete Strategy classes that inherit this class must
 * provide function definition for issueOrder(), toAttack() and toDefend().
 */
class PlayerStrategy {
private:
    string strategy_name;
public:
    PlayerStrategy();
    // Copy constructor
    PlayerStrategy(const PlayerStrategy& strategy);
    virtual ~PlayerStrategy();

    virtual vector<Territory*> to_defend(Player *player) = 0;
    virtual vector<Territory*> to_attack(Player *player) = 0;
    virtual bool issueOrder(Player *player, Deck* deck, Map* territoriesMap, const list<Player*> gamePlayers) = 0;

    // Stream insertion operator
    friend std::ostream& operator<<(std::ostream& out, const PlayerStrategy& strategy);

    // Assignment Operator
    PlayerStrategy& operator =(const PlayerStrategy& strategy);

    void setStrategyName(string name);
    string getStrategyName() const;
};


/**
 * Default Strategy (the original AI from A2)
 */
class DefaultPlayerStrategy : public PlayerStrategy {
public:
    DefaultPlayerStrategy();
    // Copy constructor
    DefaultPlayerStrategy(const DefaultPlayerStrategy& strategy);
    ~DefaultPlayerStrategy();

    vector<Territory*> to_defend(Player *player);
    vector<Territory*> to_attack(Player *player);
    bool issueOrder(Player *player, Deck* deck, Map* territoriesMap,const list<Player*> gamePlayers);

    // Stream insertion operator
    friend std::ostream& operator<<(std::ostream& out, const DefaultPlayerStrategy& strategy);

    // Assignment Operator
    DefaultPlayerStrategy& operator =(const DefaultPlayerStrategy& strategy);
};


/**
 * The strategy that requires user interaction.
 */
class HumanPlayerStrategy : public PlayerStrategy {
public:
    HumanPlayerStrategy();
    // Copy constructor
    HumanPlayerStrategy(const HumanPlayerStrategy& strategy);
    ~HumanPlayerStrategy();

    vector<Territory*> to_defend(Player *player);
    vector<Territory*> to_attack(Player *player);
    bool issueOrder(Player *player, Deck* deck, Map* territoriesMap,const list<Player*> gamePlayers);

    // Stream insertion operator
    friend std::ostream& operator<<(std::ostream& out, const HumanPlayerStrategy& strategy);

    // Assignment Operator
    HumanPlayerStrategy& operator =(const HumanPlayerStrategy& strategy);
};


/**
 * The aggressive strategy focuses on attack orders. All reinforcements will be deployed to the
 * territory with most units and then attack with that army until it cannot attack anymore, then
 * fortifies in order to maximize aggregation of force in one territory.
 */
class AggressivePlayerStrategy : public PlayerStrategy {
protected:
    Territory* strongestTerritory;
    bool advanceAllowed;
public:
    AggressivePlayerStrategy();
    // Copy constructor
    AggressivePlayerStrategy(const AggressivePlayerStrategy& strategy);
    ~AggressivePlayerStrategy();

    Territory* getStrongestTerritory();
    void setStrongestTerritory(Player* player);
    vector<Territory*> to_defend(Player *player);
    vector<Territory*> to_attack(Player *player);
    bool issueOrder(Player *player, Deck* deck, Map* territoriesMap,const list<Player*> gamePlayers);

    // Stream insertion operator
    friend std::ostream& operator<<(std::ostream& out, const AggressivePlayerStrategy& strategy);

    // Assignment Operator
    AggressivePlayerStrategy& operator =(const AggressivePlayerStrategy& strategy);
};


/**
 * The benevolent strategy focuses on reinforcing its weakest territories and makes no attack orders, then
 * fortifies in order to move armies to weaker countries.
 *
 */
class BenevolentPlayerStrategy : public PlayerStrategy {
protected:
    Territory* weakestTerritory;
    vector<Territory*> weakestTerritories;
public:
    BenevolentPlayerStrategy();
    // Copy constructor
    BenevolentPlayerStrategy(const BenevolentPlayerStrategy& strategy);
    ~BenevolentPlayerStrategy();

    vector<Territory*> getWeakestTerritories(Player* player);
    Territory* getWeakestTerritory();
    vector<Territory*> to_defend(Player *player);
    vector<Territory*> to_attack(Player *player);
    bool issueOrder(Player *player, Deck* deck, Map* territoriesMap,const list<Player*> gamePlayers);

    // Stream insertion operator
    friend std::ostream& operator<<(std::ostream& out, const BenevolentPlayerStrategy& strategy);

    // Assignment Operator
    BenevolentPlayerStrategy& operator =(const BenevolentPlayerStrategy& strategy);
};


/**
 * This strategy will make sure the player never issues any order.
 */
class NeutralPlayerStrategy : public PlayerStrategy {
public:
    NeutralPlayerStrategy();
    // Copy constructor
    NeutralPlayerStrategy(const NeutralPlayerStrategy& strategy);
    ~NeutralPlayerStrategy();

    vector<Territory*> to_defend(Player *player);
    vector<Territory*> to_attack(Player *player);
    bool issueOrder(Player *player, Deck* deck, Map* territoriesMap,const list<Player*> gamePlayers);

    // Stream insertion operator
    friend std::ostream& operator<<(std::ostream& out, const NeutralPlayerStrategy& strategy);

    // Assignment Operator
    NeutralPlayerStrategy& operator =(const NeutralPlayerStrategy& strategy);
};