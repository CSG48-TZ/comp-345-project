#include "Player.h"

#include <algorithm>
#include <cctype>

// Implementation of Player class
Player::Player(){
    this->pName = "default";
    this->territories = vector<Territory *>();
    this->hand = new Hand();
    this->playerID = 0;
    this->orderList = new OrdersList(this->playerID);
}

// parametrized constructor
Player::Player(string pName, int id, vector<Territory *> territories, Hand * hand){
    this->pName = pName;
    this->territories = territories;
    this->hand = hand;
    this->playerID = id;
    this->orderList = new OrdersList(id);
}

// copy constructor
Player::Player(const Player &player){
    pName = player.pName;
    territories = player.territories;
    hand = player.hand;
    orderList = player.orderList;
}

// destructor
Player::~Player(){
    territories.clear();
    delete hand;
    hand = nullptr;
    delete orderList;
    orderList = nullptr;
}

// assignment operator
Player& Player::operator=(const Player& player){
    this->pName = player.pName;
    this->territories = player.territories;
    this->hand = player.hand;
    this->orderList = player.orderList;
    return *this;
}

// stream insertion operator
ostream &operator <<(std::ostream &strm, const Player &player){
    cout << "Player name = " << player.pName << endl;
    cout << "Player ID = " << player.playerID << endl;
    cout << "\tTerritories = ";
    for (int i = 0; i < player.territories.size(); ++i) {
        cout << player.territories[i] << ", ";
    }
    cout << endl;
    cout << "\tCards in hand = " << player.hand;
    cout << "\tOrder list = " << player.orderList;
    return cout;
}

// getter & setter for player names
void Player:: setName(string name){
    pName = name;
}

//Sets the Player ID
void Player::setPlayerID(int id) {
    playerID = id;
}


string Player::getName(){
    return pName;
}

// getter for territory
vector <Territory *> Player::getTerritory(){
    return territories;
}

// getter for Hand cards
Hand* Player::getHand(){
    return hand;
}

// getter for Order List
OrdersList* Player::getOrderList(){
    return orderList;
}

// return a list of territories that are to be defended
vector<Territory *> Player::toDefend(){
    int random1 = rand()% 5;  // # of territories to defend[0~4]
    int random2 = rand()% (territories.size());  // which territories to defend[0~4]
    vector<Territory *> defendList;
    // return an arbitrary list
    for (int i = 0; i < random1; ++i) {
        defendList.push_back(territories.at(random2));
    }
    return defendList;
}

// print defend list
void Player::printDefendList(vector<Territory *> defendList){
    for (int i = 0; i < defendList.size(); i++) {
        cout << "Defend list = " << defendList.at(i) << ", " ;
    }
    cout << endl;
}

// return a list of territories that are to be attacked
vector<Territory *> Player::toAttack(){
    int random1 = rand() % 4 + 1;  // # of territories to attack[1~4]
    int random2 = rand() % (territories.size() + 1);  // which territories to attack[1~4]
    vector<Territory *> attackList;
    for (int i = 0; i < random1; ++i) {
        attackList.push_back(territories.at(random2));
    }
    return attackList;
}

// print attack list
void Player::printAttackList(vector<Territory *> attackList){
    for (int i = 0; i < attackList.size(); i++) {
        cout << "Attack list = " << attackList.at(i) << ", " ;
    }
    cout << endl;
}

//  creates an order object and adds it to the list of orders.
void Player::issueOrder(string type, int target, int from, int armyCount, int targetLocation, int fromLocation, int orderNumber) {
    Orders* order{};
    
    std::transform(type.begin(), type.end(), type.begin(),
        [](unsigned char c) { return std::tolower(c); });
    
    if (type == "deploy") {
        order = new Deploy(target, from, armyCount, targetLocation, fromLocation, orderNumber);
    }
    else if (type == "airlift") {
        order = new Airlift(target, from, armyCount, targetLocation, fromLocation, orderNumber);
    }
    else if (type == "blockade") {
        order = new Blockade(target, from, armyCount, targetLocation, fromLocation, orderNumber);
    }
    else if (type == "bomb") {
        order = new Bomb(target, from, armyCount, targetLocation, fromLocation, orderNumber);
    }
    else if (type == "advance") {
        order = new Advance(target, from, armyCount, targetLocation, fromLocation, orderNumber);
    }
    else if (type == "negociate") {
        order = new Negociate(target, from, armyCount, targetLocation, fromLocation, orderNumber);
    }

    orderList->add(order);  // adding order to the list
    cout << "Order has been added to the list" << endl;
}

