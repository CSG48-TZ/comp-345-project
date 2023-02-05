#include <string>
#include <iterator>
#include <list>

using namespace std;

class Orders
{

public:
	Orders(int type, int target, int from, int armyCount, int targetLocation, int fromLocation, int orderNumber);
	string getCurrentOrder(void);
	int getOrderTargetPlayer(void);
	int getOrderArmyCount(void);
	int getOrderIssuer(void);
	void changeOrder(int newOrder);
	int getTargetLocation(void);
	int getIssuerLocation(void);
	int getOrderNumber(void);
	string toString(void);

private:
	string orderType[6] = { "Deploy", "Advance", "Bomb", "Blockade", "Airlift", "Negotiate"};
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

