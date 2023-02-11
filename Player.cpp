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
    cout << "Player name = " << player.pName << endl;
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
    int random1 = rand()% 5;  // # of territories to attack[0~4]
    int random2 = rand()% (territories.size());  // which territories to attack[0~4]
    vector<Territory *> defendList;
    // return an arbitrary list
    for (int i = 0; i < random1; ++i) {
        defendList.push_back(territories.at(random2));
    }
    return defendList;
}

// return a list of territories that are to be attacked
vector<Territory *> Player::toAttack(){
    int random1 = rand()% 5;  // # of territories to attack[0~4]
    int random2 = rand()% (territories.size());  // which territories to attack[0~4]
    vector<Territory *> attackList;
    for (int i = 0; i < random1; ++i) {
        attackList.push_back(territories.at(random2));
    }
    return attackList;
}

//  creates an order object and adds it to the list of orders.
void issueOrder(OrdersList orderList) {
    Orders * order = new Orders();
    orderList.add(order);  // adding order to the list
    cout << "Order has been added to the list" << endl;
}

