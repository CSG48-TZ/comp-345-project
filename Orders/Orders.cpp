#include "Orders.h"

Orders::Orders(int type, int target, int from, int armyCount, int targetLocation, int fromLocation) {
	this->target = target;
	this->from = from;
	this->armyCount = armyCount;
	this->targetLocation = targetLocation;
	this->fromLocation = fromLocation;

	currentOrder = orderType[type];
}

string Orders::getCurrentOrder(void) {
	return currentOrder;
}

void Orders::changeOrder(int newOrder) {
	currentOrder = orderType[newOrder];
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

int Orders::getTargetLocation() {
	return targetLocation;
}

int Orders::getIssuerLocation() {
	return fromLocation;
}


string Orders::toString(void) {
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
