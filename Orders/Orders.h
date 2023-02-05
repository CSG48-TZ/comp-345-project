#include <string>

using namespace std;

class Orders
{

public:
	Orders(int type, int target, int from, int armyCount, int targetLocation, int fromLocation);
	string getCurrentOrder(void);
	int getOrderTargetPlayer(void);
	int getOrderArmyCount(void);
	int getOrderIssuer(void);
	void changeOrder(int newOrder);
	int getTargetLocation(void);
	int getIssuerLocation(void);
	string toString(void);

private:
	string orderType[6] = { "Deploy", "Advance", "Bomb", "Blockade", "Airlift", "Negotiate"};
	string currentOrder;
	int target;
	int from;
	int armyCount;
	int targetLocation;
	int fromLocation;
};

