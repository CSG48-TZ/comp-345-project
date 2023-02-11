#include "Player.h"

// Implementation of Player class
Player::Player(){
    this->pName = "default";
    this->territories = vector<Territory *>();
    this->hand = new Hand();
    this->orderList = new OrdersList();
}

// parametrized constructor
Player::Player(string pName, vector<Territory *> territories, Hand * hand, OrdersList * orderList){
    this->pName = pName;
    this->territories = territories;
    this->hand = hand;
    this->orderList = orderList;
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
    cout << "Player name = " << player.getName() << endl;
    cout << "\tTerritories = " << player.getTerritory();
    cout << "\tCards in hand = " << player.getHand();
    cout << "\tOrder list = " << player.getOrderList();
    return cout;
}

// getter & setter for player names
void Player:: setName(string name){
    pName = name;
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
    vector<Territory *> defendList;
    // return an arbitrary list
}

// return a list of territories that are to be attacked
vector<Territory *> Player::toAttack(){
    vector<Territory *> attackList;
    // return an arbitrary list
}

//  creates an order object and adds it to the list of orders.
void issueOrder(OrdersList orderList) {
    Orders * order = new Orders();
    orderList.add(order);  // adding order to the list
    cout << "Order has been added to the list" << endl;
}

