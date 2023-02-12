/* ==========================================
; Title:  Orders.cpp
; Author: Dario Cimmino
; Student ID: 40068769
; Date:   12 FEB 2023
; Description: Orders Class used by the Player class that contains the OrdersList class and all the different types of Orders subclasses. This is the orders management part of the game.
; ==========================================
*/

#include "Orders.h"
#include <iostream>

/*
* Constructor
*/
Orders::Orders() {
	this->target = 0;
	this->from = 0;
	this->armyCount = 0;
	this->targetLocation = 0;
	this->fromLocation = 0;
	this->orderNumber = 0;
}

/*
* Deconstructor
*/
Orders::~Orders() {

}

/*
* Gets the current order type as a string.
*/
string Orders::getCurrentOrder(void) {
	return currentOrder;
}

/*
* Gets the current player ID the order is targeted to.
*/
int Orders::getOrderTargetPlayer(void) {
	return target;
}

/*
* Gets the current army count affected with the order
*/
int Orders::getOrderArmyCount(void) {
	return armyCount;
}

/*
* Gets the current player ID the order is assigned to.
*/
int Orders::getOrderIssuer(void) {
	return from;
}

/*
* Gets the order ID.
*/
int Orders::getOrderNumber() {
	return orderNumber;
}

/*
* Gets the target the location ID
*/
int Orders::getTargetLocation() {
	return targetLocation;
}

/*
* Gets the location ID the order is coming from
*/
int Orders::getIssuerLocation() {
	return fromLocation;
}

/*
* Validate function, will be overriden by the subclasses
*/
bool Orders::validate() {
	return false;
}

/*
* execute function, will be overriden by the subclasses
*/
bool Orders::execute() {
	return false;
}

/*
* Stream Insertion operator
*/
ostream& operator << (ostream& out, const Orders &o)
{
	out << "Order ID: " << o.orderNumber;
	out << " - Player " << o.from;
	out << " issued the order: \"" << o.currentOrder;
	out << "\" to target Player: \"" << o.target;
	out << "\" from: \"" << o.fromLocation;
	out << "\" to \"" << o.targetLocation << "\".";
	return out;
}

/*
* Stream Input Operator TODO
*/
istream& operator >> (istream& in, Orders& o)
{
	return in;
}


/*
* toString() Implementation.
*/
string Orders::toString(void) {
	string returnString;
	returnString.append("Order#: ");
	returnString.append(to_string(orderNumber));
	returnString.append(" - Player ");
	returnString.append(to_string(from));
	returnString.append(" issued the order: \"");
	returnString.append(currentOrder);
	returnString.append("\" to target Player: \"");
	returnString.append(to_string(target));
	returnString.append("\" from: \"");
	returnString.append(to_string(getIssuerLocation()));
	returnString.append("\" to \"");
	returnString.append(to_string(getTargetLocation()));
	returnString.append("\".");

	return returnString;
}

/*
* Assignment Operator
*/
void Orders::operator = (const Orders& o) {
	this->target = o.target;
	this->from = o.from;
	this->armyCount = o.armyCount;
	this->targetLocation = o.targetLocation;
	this->fromLocation = o.fromLocation;
	this->orderNumber = o.orderNumber;
	this->currentOrder = o.currentOrder;
}

/****************ORDERS LIST CLASS****************/

/*
* This class creates a doubly linked list to store all the ORders currently requested by a player.
*/

/*
* Constructor
*/
OrdersList::OrdersList(int player) {
	this->player = player;
	hasOrdersInList = false;
	lastOrderModifiedIndex = 0;
	orderNumber = 0;
}

/*
* Deconstructor
*/
OrdersList::~OrdersList() {
	ordersList.clear();
}

/*
* Copy function (REQUIREMENT).
*/
OrdersList* OrdersList::copy(OrdersList* orderList) {
	OrdersList* copy = new OrdersList(orderList->getPlayerID());
	
	copy->lastOrderModifiedIndex = orderList->getLastOrderModified();
	copy->ordersList = orderList->getCurrentOrdersList();
	copy->hasOrdersInList = orderList->hasOrdersInList;
	copy->orderNumber = orderList->orderNumber;

	return copy;
}

/*
* Returns the Player ID this list is attributed to
*/
int OrdersList::getPlayerID() {
	return player;
}


/*
* Adds an Order to the list.
*/
void OrdersList::add(Orders* order) {
	ordersList.push_back(order);
	//Update lastOrderModifiedIndex
	lastOrderModifiedIndex = (int)ordersList.size() - 1;
	hasOrdersInList = true;
}

/*
* Moves the order in the list. Takes an index of the order to move, and a target index.
* 
* Moves order from index "index" to index "toIndex"
* 
*/
void OrdersList::move(int index, int toIndex) {
	//Creates Iterator
	list<Orders*>::iterator it;
	//Starts at the beginning of the list.
	it = ordersList.begin();
	//Advances to the desired Index
	advance(it, index);
	//Copy the Order.
	Orders* orderToMove = *it;
	//Erase the Order.
	ordersList.erase(it);

	//Start at the beginning of the list
	it = ordersList.begin();
	//Advance to new index
	advance(it, toIndex);
	//Insert the previously Copied Order.
	ordersList.insert(it, orderToMove);

	//Update lastOrderModifiedIndex
	lastOrderModifiedIndex = toIndex;
}

/*
* Removes the order at the requested Index
*/
void OrdersList::remove(int index) {
	//Creates Iterator
	list<Orders*>::iterator it;
	//Starts at the beginning of the list.
	it = ordersList.begin();
	//Advances to the desired Index
	advance(it, index);
	//Check if the order is correct
	Orders* orderToRemove = *it;

	//Erase the Order.
	ordersList.erase(it);
	//Update lastOrderModifiedIndex
	lastOrderModifiedIndex = index;

	if ((int)ordersList.size() == 0) {
		hasOrdersInList = false;
	}
}

/*
* Validates the whole orders lists.
*/
bool OrdersList::validate()
{
	list<Orders*>::iterator it;

	for (it = ordersList.begin(); it != ordersList.end(); it++) {
		Orders* current = *it;
		if (!current->validate()) {
			return false;
		}
	}

	return true;
}

/*
* Executes all the orders.
*/
bool OrdersList::execute()
{
	list<Orders*>::iterator it;

	for (it = ordersList.begin(); it != ordersList.end(); it++) {
		Orders* current = *it;
		if (!current->execute()) {
			return false;
		}
	}

	return true;
}

/*
* Gets the current size of the list, i.e. the number of orders the player has.
*/
int OrdersList::getCurrentNumberOfOrders()
{
	return (int)ordersList.size();
}

/*
* Helper function, returns the index of the last modified order (addition, deletion, etc..)
*/
int OrdersList::getLastOrderModified()
{
	return lastOrderModifiedIndex;
}

/*
* Gets the last Order in the list.
*/
Orders* OrdersList::getLastOrder()
{
	return ordersList.back();
}

/*
* Gets the first Order in the list.
*/
Orders* OrdersList::getNextOrder()
{
	return ordersList.front();
}

/*
* Returns the list.
*/
list<Orders*> OrdersList::getCurrentOrdersList()
{
	return ordersList;
}

/*
* Assignment Operator
*/
void OrdersList::operator = (const OrdersList& o) {
	this->ordersList = o.ordersList;
	this->player = o.player;
	hasOrdersInList = o.hasOrdersInList;
	lastOrderModifiedIndex = o.lastOrderModifiedIndex;
	orderNumber = o.orderNumber;
}


/****************DEPLOY ORDER LIST CLASS****************/

/*
* Constructor
*/
Deploy::Deploy(int target, int from, int armyCount, int targetLocation, int fromLocation, int orderNumber) {
	this->target = target;
	this->from = from;
	this->armyCount = armyCount;
	this->targetLocation = targetLocation;
	this->fromLocation = fromLocation;
	this->orderNumber = orderNumber;

	currentOrder = "Deploy";
}

/*
* Deconstructor
*/
Deploy::~Deploy() {

}

/*
* Validates the order, returns true or false
*/
bool Deploy::validate() {
	cout << "Validating Deploy order: \"" << this->toString();
	return false;
}

/*
* Executes the Order returns true is successful
*/
bool Deploy::execute() {
	if (validate()) {
		return true;
	}
	return false;
}


/*
* Copy function (REQUIREMENT). 
*/
Deploy Deploy::copy(Deploy order) {
	Deploy copy = Deploy(this->target, this->from, this->armyCount, this->targetLocation, this->fromLocation, this->orderNumber);
	return copy;
}

/****************ADVANCE ORDER LIST CLASS****************/

/*
* Constructor
*/
Advance::Advance(int target, int from, int armyCount, int targetLocation, int fromLocation, int orderNumber) {
	this->target = target;
	this->from = from;
	this->armyCount = armyCount;
	this->targetLocation = targetLocation;
	this->fromLocation = fromLocation;
	this->orderNumber = orderNumber;

	currentOrder = "Advance";
}

/*
* Deconstructor
*/
Advance::~Advance() {

}

/*
* Validates the order, returns true or false
*/
bool Advance::validate() {
	cout << "Validating Advance order: \"" << this->toString();
	return false;
}

/*
* Executes the Order returns true is successful
*/
bool Advance::execute() {
	if (validate()) {
		return true;
	}
	return false;
}

/*
* Copy function (REQUIREMENT).
*/
Advance Advance::copy(Advance order) {
	Advance copy = Advance(this->target, this->from, this->armyCount, this->targetLocation, this->fromLocation, this->orderNumber);
	return copy;
}

/****************BOMB ORDER LIST SUB CLASS****************/

/*
* Constructor
*/
Bomb::Bomb(int target, int from, int armyCount, int targetLocation, int fromLocation, int orderNumber) {
	this->target = target;
	this->from = from;
	this->armyCount = armyCount;
	this->targetLocation = targetLocation;
	this->fromLocation = fromLocation;
	this->orderNumber = orderNumber;

	currentOrder = "Bomb";
}

/*
* Deconstructor
*/
Bomb::~Bomb() {

}

/*
* Validates the order, returns true or false
*/
bool Bomb::validate() {
	cout << "Validating Bomb order: \"" << this->toString();
	return false;
}

/*
* Executes the Order returns true is successful
*/
bool Bomb::execute() {
	if (validate()) {
		return true;
	}
	return false;
}

/*
* Copy function (REQUIREMENT).
*/
Bomb Bomb::copy(Bomb order) {
	Bomb copy = Bomb(this->target, this->from, this->armyCount, this->targetLocation, this->fromLocation, this->orderNumber);
	return copy;
}

/****************BLOCKADE ORDER LIST SUB CLASS****************/

/*
* Constructor
*/
Blockade::Blockade(int target, int from, int armyCount, int targetLocation, int fromLocation, int orderNumber) {
	this->target = target;
	this->from = from;
	this->armyCount = armyCount;
	this->targetLocation = targetLocation;
	this->fromLocation = fromLocation;
	this->orderNumber = orderNumber;

	currentOrder = "Blockade";
}

/*
* Deconstructor
*/
Blockade::~Blockade() {

}

/*
* Validates the order, returns true or false
*/
bool Blockade::validate() {
	cout << "Validating Blockade order: \"" << this->toString();
	return false;
}

/*
* Executes the Order returns true is successful
*/
bool Blockade::execute() {
	if (validate()) {
		return true;
	}
	return false;
}

/*
* Copy function (REQUIREMENT).
*/
Blockade Blockade::copy(Blockade order) {
	Blockade copy = Blockade(this->target, this->from, this->armyCount, this->targetLocation, this->fromLocation, this->orderNumber);
	return copy;
}

/****************AIRLIFT ORDER LIST SUB CLASS****************/

/*
* Constructor
*/
Airlift::Airlift(int target, int from, int armyCount, int targetLocation, int fromLocation, int orderNumber) {
	this->target = target;
	this->from = from;
	this->armyCount = armyCount;
	this->targetLocation = targetLocation;
	this->fromLocation = fromLocation;
	this->orderNumber = orderNumber;

	currentOrder = "Airlift";

}

/*
* Deconstructor
*/
Airlift::~Airlift() {

}

/*
* Validates the order, returns true or false
*/
bool Airlift::validate() {
	cout << "Validating Airlift order: \"" << this->toString();
	return false;
}

/*
* Executes the Order returns true is successful
*/
bool Airlift::execute() {
	if (validate()) {
		return true;
	}
	return false;
}

/*
* Copy function (REQUIREMENT).
*/
Airlift Airlift::copy(Airlift order) {
	Airlift copy = Airlift(this->target, this->from, this->armyCount, this->targetLocation, this->fromLocation, this->orderNumber);
	return copy;
}

/****************NEGOCIATE ORDER LIST SUB CLASS****************/

/*
* Constructor
*/
Negociate::Negociate(int target, int from, int armyCount, int targetLocation, int fromLocation, int orderNumber) {
	this->target = target;
	this->from = from;
	this->armyCount = armyCount;
	this->targetLocation = targetLocation;
	this->fromLocation = fromLocation;
	this->orderNumber = orderNumber;

	currentOrder = "Negociate";
}

/*
* Deconstructor
*/
Negociate::~Negociate() {

}

/*
* Validates the Negociate order, returns true or false
*/
bool Negociate::validate() {
	cout << "Validating Negociate order: \"" << this->toString();
	return false;
}

/*
* Executes the Order returns true is successful
*/
bool Negociate::execute() {
	if (validate()) {
		return true;
	}
	return false;
}

/*
* Copy function (REQUIREMENT).
*/
Negociate Negociate::copy(Negociate order) {
	Negociate copy = Negociate(this->target, this->from, this->armyCount, this->targetLocation, this->fromLocation, this->orderNumber);
	return copy;
}