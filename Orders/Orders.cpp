#include "Orders.h"

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
* toString() Implementation.
*/
string Orders::toString(void) {
	string returnString;
	returnString.append("\nOrder#: ");
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
	returnString.append("\".\n");

	return returnString;
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
	currentNumberOfOrders = 0;
	hasOrdersInList = false;
	lastOrderModifiedIndex = 0;
	orderNumber = 0;
}

/*
* Adds an Order to the list.
*/
void OrdersList::add(Orders order) {
	ordersList.push_front(order);
	//Update lastOrderModifiedIndex
	lastOrderModifiedIndex = ordersList.size() - 1;
}

/*
* Moves the order in the list. Takes an index of the order to move, and a target index.
* 
* Moves order from index "index" to index "toIndex"
* 
*/
void OrdersList::move(int index, int toIndex) {
	//Creates Iterator
	list<Orders>::iterator it;
	//Starts at the beginning of the list.
	it = ordersList.begin();
	//Advances to the desired Index
	advance(it, index);
	//Copy the Order.
	Orders orderToMove = *it;
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
	list<Orders>::iterator it;
	//Starts at the beginning of the list.
	it = ordersList.begin();
	//Advances to the desired Index
	advance(it, index);
	//Check if the order is correct
	Orders orderToRemove = *it;

	//Erase the Order.
	ordersList.erase(it);
	//Update lastOrderModifiedIndex
	lastOrderModifiedIndex = index;

}

/*
* Validates the whole orders lists.
*/
bool OrdersList::validate()
{
	list<Orders>::iterator it;

	for (it = ordersList.begin(); it != ordersList.end(); it++) {
		Orders current = *it;
		if (!current.validate()) {
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
	list<Orders>::iterator it;

	for (it = ordersList.begin(); it != ordersList.end(); it++) {
		Orders current = *it;
		if (!current.execute()) {
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
	return ordersList.size();
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
Orders OrdersList::getLastOrder()
{
	return ordersList.back();
}

/*
* Gets the first Order in the list.
*/
Orders OrdersList::getNextOrder()
{
	return ordersList.front();
}

/*
* Returns the list.
*/
list<Orders> OrdersList::getCurrentOrdersList()
{
	return ordersList;
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
* Validates the order, returns true or false
*/
bool Deploy::validate() {
	return false;
}

/*
* Executes the Order returns true is successful
*/
bool Deploy::execute() {
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
* Validates the order, returns true or false
*/
bool Advance::validate() {
	return false;
}

/*
* Executes the Order returns true is successful
*/
bool Advance::execute() {
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
* Validates the order, returns true or false
*/
bool Bomb::validate() {
	return false;
}

/*
* Executes the Order returns true is successful
*/
bool Bomb::execute() {
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
* Validates the order, returns true or false
*/
bool Blockade::validate() {
	return false;
}

/*
* Executes the Order returns true is successful
*/
bool Blockade::execute() {
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
* Validates the order, returns true or false
*/
bool Airlift::validate() {
	return false;
}

/*
* Executes the Order returns true is successful
*/
bool Airlift::execute() {
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
* Validates the Negociate order, returns true or false
*/
bool Negociate::validate() {
	return false;
}

/*
* Executes the Order returns true is successful
*/
bool Negociate::execute() {
	return false;
}

/*
* Copy function (REQUIREMENT).
*/
Negociate Negociate::copy(Negociate order) {
	Negociate copy = Negociate(this->target, this->from, this->armyCount, this->targetLocation, this->fromLocation, this->orderNumber);
	return copy;
}