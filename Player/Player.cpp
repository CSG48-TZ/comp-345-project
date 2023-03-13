#pragma once
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
Player::Player(string pName, int id){
    this->pName = pName;
    this->territories = vector<Territory*>();
    this->hand = new Hand();
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

//Adds a Territory to the list of owned Territory
void Player::addOwnedTerritory(Territory* t) {
    t->changeOwner(this);
    territories.push_back(t);
}

// print Owned list
void Player::printOwnedTerritoryList() {
    for (int i = 0; i < territories.size(); i++) {
        cout << territories.at(i)->name << "\n";
    }
}

// return a list of territories that are to be defended
vector<Territory *> Player::toDefend(){
    vector<Territory *> defendList;
    vector<int> random;
    for (int i = 0; i < 10; i++) {
        random.push_back(i);
    }

    std::random_shuffle(random.begin(), random.end());

    for (int i = 0; i < 5; i++) {

        defendList.push_back(territories.at(random.at(i)));

    }
    return defendList;
}

// print defend list
void Player::printDefendList(vector<Territory *> defendList){
    for (int i = 0; i < defendList.size(); i++) {
        cout << "Defend list = " << defendList.at(i)->name << "\n" ;
    }
    cout << endl;
}

// return a list of territories that are to be attacked
vector<Territory *> Player::toAttack(){
    string name;
    vector<Territory *> attackList;
    for (int i = 10; i < 16; i++) {

        name = "Territory " + to_string(i);
        attackList.push_back(new Territory(i, name, rand() % 5 + 1, rand() % 120, rand() % 120));

    }
    return attackList;
}

// print attack list
void Player::printAttackList(vector<Territory *> attackList){
    for (int i = 0; i < attackList.size(); i++) {
        cout << "Attack list = " << attackList.at(i)->name << "\n";
    }
}

//  creates an order object and adds it to the list of orders.
void Player::issueOrder(string type, Player* target, int armyCount, Territory* targetLocation, Territory* fromLocation, int orderNumber) {
    Orders* order{};
    
    std::transform(type.begin(), type.end(), type.begin(),
        [](unsigned char c) { return std::tolower(c); });
    
    if (type == "deploy") {
        order = new Deploy(this, this, armyCount, targetLocation, fromLocation, orderNumber);
    }
    else if (type == "airlift") {
        order = new Airlift(target, this, armyCount, targetLocation, fromLocation, orderNumber);
    }
    else if (type == "blockade") {
        order = new Blockade(target, this, armyCount, targetLocation, fromLocation, orderNumber);
    }
    else if (type == "bomb") {
        order = new Bomb(target, this, armyCount, targetLocation, fromLocation, orderNumber);
    }
    else if (type == "advance") {
        order = new Advance(target, this, armyCount, targetLocation, fromLocation, orderNumber);
    }
    else if (type == "negociate") {
        order = new Negociate(target, this, armyCount, targetLocation, fromLocation, orderNumber);
    }

    orderList->add(order);  // adding order to the list
    cout << "Order has been added to the list" << endl;
}

//Helper funtion for the driver to show current hand.
void Player::printCurrentHand() {
    for(int i = 0; i < 7; i++) {
        hand->addCard(new Card(rand() % 5));
    }

    hand->showHand();

}

//Sets a flag if the player conquered a territory or not this turn
void Player::setConqueredFlag(bool value) {
    conqueredTerritoryThisTurn = value;
}
