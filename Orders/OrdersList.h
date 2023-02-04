#pragma once
#include <string>
#include <iterator>
#include <list>
#include "Order.h"

using namespace std;
class OrdersList
{
public:

	void add(Order order);
	void move(int index, int toIndex);
	void remove(int index, Order order);
	bool validate();
	bool execute(int index);
	int getCurrentNumberOfOrders();
	int getLastOrderModified();
	Order getLastOrder();
	Order getNextOrder();
	list<Order> getCurrentOrdersList();
	OrdersList(int playerNumber);

private:
	
	int player;
	int currentNumberOfOrders;
	const int orderLimit = 99;
	int lastOrderModifiedIndex;
	bool hasOrdersInList;
	list<Order> ordersList;
	
	
};

