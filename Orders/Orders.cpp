#include "Orders.h"

Orders::Orders() {
	this->target = 0;
	this->from = 0;
	this->armyCount = 0;
	this->targetLocation = 0;
	this->fromLocation = 0;
	this->orderNumber = 0;
}

string Orders::getCurrentOrder(void) {
	return currentOrder;
}

int Orders::getOrderTargetPlayer(void) {
	return target;
}
int Orders::getOrderArmyCount(void) {
	return armyCount;
}
int Orders::getOrderIssuer(void) {
	return from;
}

int Orders::getOrderNumber() {
	return orderNumber;
}

int Orders::getTargetLocation() {
	return targetLocation;
}

int Orders::getIssuerLocation() {
	return fromLocation;
}


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


OrdersList::OrdersList(int player) {
	this->player = player;
	currentNumberOfOrders = 0;
	hasOrdersInList = false;
	lastOrderModifiedIndex = 0;
	orderNumber = 0;
}

void OrdersList::add(Orders order) {
	ordersList.push_front(order);
	//Update lastOrderModifiedIndex
	lastOrderModifiedIndex = ordersList.size() - 1;
}

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


	//TODO send error if the order doesn't match.
}

bool OrdersList::validate()
{
	return false;
}

int OrdersList::getCurrentNumberOfOrders()
{
	return ordersList.size();
}

int OrdersList::getLastOrderModified()
{
	return lastOrderModifiedIndex;
}

Orders OrdersList::getLastOrder()
{
	return ordersList.back();
}

Orders OrdersList::getNextOrder()
{
	return ordersList.front();
}

list<Orders> OrdersList::getCurrentOrdersList()
{
	return ordersList;
}

bool OrdersList::execute(int index) {
	return false;
}

Deploy::Deploy(int target, int from, int armyCount, int targetLocation, int fromLocation, int orderNumber) {
	this->target = target;
	this->from = from;
	this->armyCount = armyCount;
	this->targetLocation = targetLocation;
	this->fromLocation = fromLocation;
	this->orderNumber = orderNumber;
}

bool Deploy::validate() {
	return false;
}

bool Deploy::execute() {
	return false;
}

Advance::Advance(int target, int from, int armyCount, int targetLocation, int fromLocation, int orderNumber) {
	this->target = target;
	this->from = from;
	this->armyCount = armyCount;
	this->targetLocation = targetLocation;
	this->fromLocation = fromLocation;
	this->orderNumber = orderNumber;
}

bool Advance::validate() {
	return false;
}

bool Advance::execute() {
	return false;
}

Bomb::Bomb(int target, int from, int armyCount, int targetLocation, int fromLocation, int orderNumber) {
	this->target = target;
	this->from = from;
	this->armyCount = armyCount;
	this->targetLocation = targetLocation;
	this->fromLocation = fromLocation;
	this->orderNumber = orderNumber;
}

bool Bomb::validate() {
	return false;
}

bool Bomb::execute() {
	return false;
}

Blockade::Blockade(int target, int from, int armyCount, int targetLocation, int fromLocation, int orderNumber) {
	this->target = target;
	this->from = from;
	this->armyCount = armyCount;
	this->targetLocation = targetLocation;
	this->fromLocation = fromLocation;
	this->orderNumber = orderNumber;
}

bool Blockade::validate() {
	return false;
}

bool Blockade::execute() {
	return false;
}

Airlift::Airlift(int target, int from, int armyCount, int targetLocation, int fromLocation, int orderNumber) {
	this->target = target;
	this->from = from;
	this->armyCount = armyCount;
	this->targetLocation = targetLocation;
	this->fromLocation = fromLocation;
	this->orderNumber = orderNumber;
}

bool Airlift::validate() {
	return false;
}

bool Airlift::execute() {
	return false;
}

Negociate::Negociate(int target, int from, int armyCount, int targetLocation, int fromLocation, int orderNumber) {
	this->target = target;
	this->from = from;
	this->armyCount = armyCount;
	this->targetLocation = targetLocation;
	this->fromLocation = fromLocation;
	this->orderNumber = orderNumber;
}

bool Negociate::validate() {
	return false;
}

bool Negociate::execute() {
	return false;
}