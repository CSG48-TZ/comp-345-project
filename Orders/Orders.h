#ifndef COMP345_ORDERS_H
#define COMP345_ORDERS_H

#include <string>
#include <iterator>
#include <list>
#include "../Player/Player.h"
#include "../Map/Map.h"
#include "../Observer/LoggingObserver.h"


using namespace std;

class Player;
class Territory;

class Orders : public Iloggable, public Subject
{

public:
	Orders();
	~Orders();
	string getCurrentOrder(void);
	Player* getOrderTargetPlayer(void);
	int getOrderArmyCount(void);
	Player* getOrderIssuer(void);
	Territory* getTargetLocation(void);
	Territory* getIssuerLocation(void);
	int getOrderNumber(void);
	string toString(void);
	virtual bool validate();
	virtual bool execute();
	void operator = (const Orders& o);
	friend ostream& operator << (ostream& out, const Orders& o);
	friend istream& operator >> (istream& in, Orders& o);

	string stringToLog();

protected:
	string currentOrder;
	Player* target;
	Player* player;
	int armyCount;
	Territory* targetLocation;
	Territory* fromLocation;
	int orderNumber;
};

class OrdersList : public Iloggable, public Subject
{
public:

	void add(Orders* order);
	void move(int index, int toIndex);
	void remove(int index); \
		void removeOrder(Orders* order);
	void clearOrdersList();
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

	string stringToLog();

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
	Deploy(Player* target, Player* from, int armyCount, Territory* targetLocation, Territory* fromLocation, int orderNumber);
	~Deploy();
	bool validate(void) override;
	bool execute() override;
	Deploy copy(Deploy order);
};

class Advance : public Orders {
public:
	Advance(Player* target, Player* from, int armyCount, Territory* targetLocation, Territory* fromLocation, int orderNumber);
	~Advance();
	bool validate(void) override;
	bool execute() override;
	Advance copy(Advance order);
};

class Bomb : public Orders {
public:
	Bomb(Player* target, Player* from, int armyCount, Territory* targetLocation, Territory* fromLocation, int orderNumber);
	~Bomb();
	bool validate(void) override;
	bool execute() override;
	Bomb copy(Bomb order);
};

class Blockade : public Orders {
public:
	Blockade(Player* target, Player* from, int armyCount, Territory* targetLocation, Territory* fromLocation, int orderNumber);
	~Blockade();
	bool validate(void) override;
	bool execute() override;
	Blockade copy(Blockade order);
};

class Airlift : public Orders {
public:
	Airlift(Player* target, Player* from, int armyCount, Territory* targetLocation, Territory* fromLocation, int orderNumber);
	~Airlift();
	bool validate(void) override;
	bool execute() override;
	Airlift copy(Airlift order);
};

class Negociate : public Orders {
public:
	Negociate(Player* target, Player* from, int armyCount, Territory* targetLocation, Territory* fromLocation, int orderNumber);
	~Negociate();
	bool validate(void) override;
	bool execute() override;
	Negociate copy(Negociate order);
};

class Steal : public Orders {
public:
    Steal(Player * cheaterPlayer);
    ~Steal();
    bool validate(void) override;
    bool execute() override;
    Steal copy(Steal order);
};

#endif
