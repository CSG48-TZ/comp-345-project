#pragma once
#include <string>
#include <iterator>
#include <list>
#include "Orders.h"

using namespace std;
class OrdersList
{
public:

	void add(Orders order);
	void move(int index, int toIndex);
	void remove(int index, Orders order);
	bool validate();
	bool execute(int index);
	int getCurrentNumberOfOrders();
	int getLastOrderModified();
	Orders getLastOrder();
	Orders getNextOrder();
	list<Orders> getCurrentOrdersList();
	OrdersList(int playerNumber);

private:
	
	int player;
	int currentNumberOfOrders;
	const int orderLimit = 99;
	int lastOrderModifiedIndex;
	bool hasOrdersInList;
	list<Orders> ordersList;
	
	
};

