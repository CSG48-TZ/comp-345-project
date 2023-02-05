#include <string>
#include <iterator>
#include <list>

using namespace std;

class Orders
{

public:
	Orders();
	string getCurrentOrder(void);
	int getOrderTargetPlayer(void);
	int getOrderArmyCount(void);
	int getOrderIssuer(void);
	int getTargetLocation(void);
	int getIssuerLocation(void);
	int getOrderNumber(void);
	string toString(void);

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

	void add(Orders order);
	void move(int index, int toIndex);
	void remove(int index);
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
	int orderNumber = 0;

};

class Deploy : public Orders {
public:
	Deploy(int target, int from, int armyCount, int targetLocation, int fromLocation, int orderNumber);
	bool validate(void);
	bool execute();
};

class Advance : public Orders {
	Advance(int target, int from, int armyCount, int targetLocation, int fromLocation, int orderNumber);
	bool validate(void);
	bool execute();
};

class Bomb : public Orders {
	Bomb(int target, int from, int armyCount, int targetLocation, int fromLocation, int orderNumber);
	bool validate(void);
	bool execute();
};

class Blockade : public Orders {
	Blockade(int target, int from, int armyCount, int targetLocation, int fromLocation, int orderNumber);
	bool validate(void);
	bool execute();
};

class Airlift : public Orders {
	Airlift(int target, int from, int armyCount, int targetLocation, int fromLocation, int orderNumber);
	bool validate(void);
	bool execute();
};

class Negociate : public Orders {
	Negociate(int target, int from, int armyCount, int targetLocation, int fromLocation, int orderNumber);
	bool validate(void);
	bool execute();
};