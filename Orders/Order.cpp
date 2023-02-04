#include "Order.h"

Order::Order(int type, int target, int from, int armyCount, int targetLocation, int fromLocation) {
	this->target = target;
	this->from = from;
	this->armyCount = armyCount;
	this->targetLocation = targetLocation;
	this->fromLocation = fromLocation;

	currentOrder = orderType[type];
}

string Order::getCurrentOrder(void) {
	return currentOrder;
}

void Order::changeOrder(int newOrder) {
	currentOrder = orderType[newOrder];
}

int Order::getOrderTargetPlayer(void) {
	return target;
}
int Order::getOrderArmyCount(void) {
	return armyCount;
}
int Order::getOrderIssuer(void) {
	return from;
}

int Order::getTargetLocation() {
	return targetLocation;
}

int Order::getIssuerLocation() {
	return fromLocation;
}


string Order::toString(void) {
	string returnString;
	returnString.append("\nPlayer ");
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
