#include "OrdersList.h"


OrdersList::OrdersList(int player) {
	this->player = player;
}

void OrdersList::add(Order order) {
	ordersList.push_front(order);
	//Update lastOrderModifiedIndex
	lastOrderModifiedIndex = ordersList.size() - 1;
}

void OrdersList::move(int index, int toIndex) {
	//Creates Iterator
	list<Order>::iterator it;
	//Starts at the beginning of the list.
	it = ordersList.begin();
	//Advances to the desired Index
	advance(it, index);
	//Copy the Order.
	Order orderToMove = *it;
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

void OrdersList::remove(int index, Order order) {
	//Creates Iterator
	list<Order>::iterator it;
	//Starts at the beginning of the list.
	it = ordersList.begin();
	//Advances to the desired Index
	advance(it, index);
	//Check if the order is correct
	Order orderToRemove = *it;
	if (order.getCurrentOrder() == orderToRemove.getCurrentOrder()) {
		//Erase the Order.
		ordersList.erase(it);
		//Update lastOrderModifiedIndex
		lastOrderModifiedIndex = index;
	}

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

Order OrdersList::getLastOrder()
{
	return ordersList.back();
}

Order OrdersList::getNextOrder()
{
	return ordersList.front();
}

list<Order> OrdersList::getCurrentOrdersList()
{
	return ordersList;
}

bool OrdersList::execute(int index) {
	return false;
}