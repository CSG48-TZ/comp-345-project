
#pragma once
#ifndef COMP345_ORDERS_H
#define COMP345_ORDERS_H

#include <string>
#include <iterator>
#include <list>


using namespace std;

class Orders
{

public:
	Orders();
	~Orders();
	string getCurrentOrder(void);
	int getOrderTargetPlayer(void);
	int getOrderArmyCount(void);
	int getOrderIssuer(void);
	int getTargetLocation(void);
	int getIssuerLocation(void);
	int getOrderNumber(void);
	string toString(void);
	virtual bool validate();
	virtual bool execute();
	void operator = (const Orders& o);
	friend ostream& operator << (ostream& out, const Orders& o);
	friend istream& operator >> (istream& in, Orders& o);

protected:
	string currentOrder;
	int target;
	int from;
	int armyCount;
	int targetLocation;
	int fromLocation;
	int orderNumber;
};

class OrdersList
{
public:

	void add(Orders* order);
	void move(int index, int toIndex);
	void remove(int index);
	bool validate();
	bool execute();
	int getCurrentNumberOfOrders();
	int getLastOrderModified();
	int getPlayerID();
	OrdersList* copy(OrdersList* ordersList);
	Orders* getLastOrder();
	Orders* getNextOrder();
	list<Orders*> getCurrentOrdersList();
	OrdersList(int playerNumber);
	~OrdersList();
	void operator = (const OrdersList& D);

protected:

	int player;
	const int orderLimit = 99;
	int lastOrderModifiedIndex;
	bool hasOrdersInList;
	list<Orders*> ordersList;
	int orderNumber;

};

class Deploy : public Orders {
public:
	Deploy(int target, int from, int armyCount, int targetLocation, int fromLocation, int orderNumber);
	~Deploy();
	bool validate(void) override;
	bool execute() override;
	Deploy copy(Deploy order);
};

class Advance : public Orders {
public:
	Advance(int target, int from, int armyCount, int targetLocation, int fromLocation, int orderNumber);
	~Advance();
	bool validate(void) override;
	bool execute() override;
	Advance copy(Advance order);
};

class Bomb : public Orders {
public:
	Bomb(int target, int from, int armyCount, int targetLocation, int fromLocation, int orderNumber);
	~Bomb();
	bool validate(void) override;
	bool execute() override;
	Bomb copy(Bomb order);
};

class Blockade : public Orders {
public:
	Blockade(int target, int from, int armyCount, int targetLocation, int fromLocation, int orderNumber);
	~Blockade();
	bool validate(void) override;
	bool execute() override;
	Blockade copy(Blockade order);
};

class Airlift : public Orders {
public:
	Airlift(int target, int from, int armyCount, int targetLocation, int fromLocation, int orderNumber);
	~Airlift();
	bool validate(void) override;
	bool execute() override;
	Airlift copy(Airlift order);
};

class Negociate : public Orders {
public:
	Negociate(int target, int from, int armyCount, int targetLocation, int fromLocation, int orderNumber);
	~Negociate();
	bool validate(void) override;
	bool execute() override;
	Negociate copy(Negociate order);
};

#endif