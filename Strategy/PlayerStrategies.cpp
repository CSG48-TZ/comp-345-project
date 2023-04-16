#include <iostream>
#include <map>
#include <set>
#include <random>

#include "../Player/Player.h"
#include "PlayerStrategies.h"
#include "../Orders/Orders.h"


/* PlayerStrategy class */
PlayerStrategy::PlayerStrategy() {}
PlayerStrategy::~PlayerStrategy() {}

void PlayerStrategy::setStrategyName(string name) {
	strategy_name = name;
}

string PlayerStrategy::getStrategyName() const {
	return strategy_name;
}

PlayerStrategy& PlayerStrategy::operator=(const PlayerStrategy& strategy) {
	if (this != &strategy)
	{
		this->setStrategyName(strategy.strategy_name);
	}

	return *this;
}

std::ostream& operator<<(ostream& out, const PlayerStrategy& strategy) {
	return out << strategy.strategy_name;
}

PlayerStrategy::PlayerStrategy(const PlayerStrategy& strategy) {
	this->setStrategyName(strategy.strategy_name);
}


/* DefaultPlayerStrategy class */
DefaultPlayerStrategy::DefaultPlayerStrategy() {
	setStrategyName("Default");
}
DefaultPlayerStrategy::~DefaultPlayerStrategy() {}

vector<Territory*> DefaultPlayerStrategy::to_defend(Player* player) {
	return player->getTerritory();
}

vector<Territory*> DefaultPlayerStrategy::to_attack(Player* player) {
	std::set<Territory*> territoriesToAttack = set<Territory*>();

	// Loop through all our territories...
	for (Territory* t : player->getTerritory())
	{
		for (Territory* adj : t->edges) {

			if (adj->owner != player)
				territoriesToAttack.emplace(adj);
		}
	}

	// Transforming the set to a vector.
	vector<Territory*> setToVector = vector<Territory*>();

	setToVector.reserve(territoriesToAttack.size());
	for (Territory* t : territoriesToAttack)
	{
		setToVector.push_back(t);
	}
	return setToVector;
}

bool DefaultPlayerStrategy::issueOrder(Player* player) {
	int actionNumber = -1;

	std::random_device randomDevice;
	std::mt19937 mt(randomDevice());

	// If some reinforcements are left in the pool of the player, he can only take deploy actions.
	if (player->reinforcementPool > 0)
	{
		cout << "You have reinforcements in your pool. Only deploy orders are allowed." << endl;
		// Deploy
		actionNumber = 0;
	}
	else
	{
		list<int> possibleActions = list<int>();

		// Advance
		bool advanceAllowed = false;
		// Checking if an advance can be done
		for (Territory* t : player->getTerritory())
		{
			if (t->numArmies > 0)
				advanceAllowed = true;
		}

		if (advanceAllowed)
			possibleActions.push_back(1);

		// Play a card
		if (player->getHand()->getNumberOfCardsInHand() > 0)
			possibleActions.push_back(2);

		// End turn
		possibleActions.push_back(3);

		// Generate a random input
		std::uniform_int_distribution<int> distribution(0, possibleActions.size() - 1);

		auto iterator = std::next(possibleActions.begin(), distribution(mt));
		actionNumber = *iterator;
	}

	// Depending on which action was chosen, create an appropriate order.
	switch (actionNumber)
	{
	case 0:
	{
		// Deploy

		// Choose a territory
		std::map<int, Territory*> territoryToNumberMap = map<int, Territory*>();
		int counter = 0;
		for (Territory* t : player->toDefend())
		{
			territoryToNumberMap[counter] = t;
			counter++;
		}

		// Generate a random input
		std::uniform_int_distribution<int> distribution(0, territoryToNumberMap.size() - 1);

		int territoryChoice = distribution(mt);

		// Generate a random input
		std::uniform_int_distribution<int> distributionTroops(1, player->reinforcementPool);
		int troopNumber = distributionTroops(mt);

		player->issue_Order("Deploy", player, troopNumber, territoryToNumberMap[territoryChoice], territoryToNumberMap[territoryChoice]);

		cout << "Deploy order issued." << endl;

		// Adjust the uncommitted reinforcement pool.
		player->reinforcementPool = player->reinforcementPool - troopNumber;
		break;
	}
	case 1:
	{
		// Advance

		// Choosing a starting point
		std::map<int, Territory*> sourceTerritoryToNumberMap = map<int, Territory*>();
		int counter = 0;

		for (Territory* t : player->toDefend())
		{
			// We can choose a starting point only if it has any armies.
			if (t->numArmies > 0)
			{
				sourceTerritoryToNumberMap[counter] = t;
				counter++;
			}
		}

		// Generate a random input
		std::uniform_int_distribution<int> distribution(0, sourceTerritoryToNumberMap.size() - 1);

		int sourceTerritoryChoice = distribution(mt);

		// Choosing randomly a number of troops to move
		std::uniform_int_distribution<int> distributionTroops(1, sourceTerritoryToNumberMap[sourceTerritoryChoice]->numArmies);

		int troopNumber = distributionTroops(mt);

		// Choose a territory for the player to advance to.
		std::map<int, Territory*> destinationTerritoryToNumberMap = map<int, Territory*>();
		int counter2 = 0;

		// Advancing to attack
		for (Territory* t : player->toAttack())
		{
			if (sourceTerritoryToNumberMap[sourceTerritoryChoice]->isAnEdge(t))
			{
				destinationTerritoryToNumberMap[counter2] = t;
				counter2++;
			}
		}
		// Advancing to defend
		for (Territory* t : player->toDefend())
		{
			if (sourceTerritoryToNumberMap[sourceTerritoryChoice]->isAnEdge(t))
			{
				destinationTerritoryToNumberMap[counter2] = t;
				counter2++;
			}
		}

		// Choosing randomly a territory to move to
		std::uniform_int_distribution<int> distributionDestination(0, destinationTerritoryToNumberMap.size() - 1);

		int destinationTerritoryChoice = distributionDestination(mt);

		player->issue_Order("Advance", player, troopNumber, destinationTerritoryToNumberMap.at(destinationTerritoryChoice), sourceTerritoryToNumberMap.at(sourceTerritoryChoice));

		cout << "Advance order issued." << endl;
		break;
	}
	case 2:
	{
		// Play a card

		int counter = 0;
		std::map<int, Card*> cardsToNumbers = std::map<int, Card*>();

		// Iterating through the hand
		for (Card* c : player->getHand()->cardHand) {
			cardsToNumbers[counter] = &*c;
			counter++;
		}

		// Generate a random input
		std::uniform_int_distribution<int> distribution(0, player->hand->getNumberOfCardsInHand() - 1);
		int cardChoice = distribution(mt);

		// Playing the card.
		Card* card = cardsToNumbers[cardChoice];

		cout << "Playing a card: " + card->getType() << endl;
		//TODO PLAY THE CARD
		break;
	}
	case 3:
		// End Turn
		cout << "Ending turn.\n" << endl;
		return false;
	default:
		throw exception("Invalid action chosen for a player's turn.");
	}

	return true;
}

DefaultPlayerStrategy::DefaultPlayerStrategy(const DefaultPlayerStrategy& strategy) {
	this->setStrategyName(strategy.getStrategyName());
}

std::ostream& operator<<(ostream& out, const DefaultPlayerStrategy& strategy) {
	return out << strategy.getStrategyName();
}

DefaultPlayerStrategy& DefaultPlayerStrategy::operator=(const DefaultPlayerStrategy& strategy) {
	if (this != &strategy)
	{
		this->setStrategyName(strategy.getStrategyName());
	}
	return *this;
}


/* HumanPlayerStrategy class */
HumanPlayerStrategy::HumanPlayerStrategy() {
	setStrategyName("Human");
}
HumanPlayerStrategy::~HumanPlayerStrategy() {}
vector<Territory*> HumanPlayerStrategy::to_defend(Player* player) {
	return player->getTerritory();
}

vector<Territory*> HumanPlayerStrategy::to_attack(Player* player) {
	std::set<Territory*> territoriesToAttack = set<Territory*>();

	// Loop through all our territories...
	for (Territory* t : player->getTerritory())
	{
		for (Territory* adj : t->edges) {

			if (adj->owner != player)
				territoriesToAttack.emplace(adj);
		}
	}

	// Transforming the set to a vector.
	vector<Territory*> setToVector = vector<Territory*>();

	setToVector.reserve(territoriesToAttack.size());
	for (Territory* t : territoriesToAttack)
	{
		setToVector.push_back(t);
	}
	return setToVector;
}

bool HumanPlayerStrategy::issueOrder(Player* player) {
	int nbOfPossibleActions = 4;
	int actionNumber = -1;

	cout << player->pName << ", which order would you like to issue? (input the number)" << endl;
	cout << "List of possible orders:" << endl;

	// If some reinforcements are left in the pool of the player, he can only take deploy actions.
	if (player->reinforcementPool > 0)
	{
		// Deploy
		cout << "0: Deploy " << endl;
		cout << "(You have " << player->reinforcementPool << " reinforcements left in your pool. You must deploy them before issuing any other order." << endl;

		// Validate input.
		while (actionNumber != 0)
			cin >> actionNumber;
	}
	else
	{
		list<int> possibleActions = list<int>();

		// Advance
		bool advanceAllowed = false;
		// Checking if an advance can be done
		for (Territory* t : player->getTerritory())
		{
			if (t->numArmies > 0)
				advanceAllowed = true;
		}

		if (advanceAllowed) {
			possibleActions.push_back(1);
			cout << "1: Advance" << endl;
		}

		// Play a card
		if (player->hand->getNumberOfCardsInHand() > 0)
		{
			possibleActions.push_back(2);
			cout << "2: Play a card" << endl;
		}

		// End turn
		possibleActions.push_back(3);
		cout << "3: End your turn." << endl;

		// Validate input.
		while (actionNumber < 0 ||
			actionNumber >= nbOfPossibleActions ||
			(std::find(possibleActions.begin(), possibleActions.end(), actionNumber) == possibleActions.end()))
			cin >> actionNumber;
	}

	// Depending on which action was chosen, create an appropriate order.
	switch (actionNumber)
	{
	case 0:
	{
		// Deploy

		// List the territories the player can choose
		cout << "In which territory would you like to deploy your troops?" << endl;
		std::map<int, Territory*> territoryToNumberMap = map<int, Territory*>();
		int counter = 0;
		for (Territory* t : this->to_defend(player))
		{
			territoryToNumberMap[counter] = t;

			cout << counter << ": " << t->name << " (" << t->numArmies << " troops)" << endl;
			counter++;
		}

		// Read input and validate it.
		int territoryChoice = -1;
		while (territoryChoice<0 || territoryChoice > this->to_defend(player).size())
			cin >> territoryChoice;

		cout << "How many troops would you like to deploy? (" << player->reinforcementPool << " remaining in your reinforcement pool.)" << endl;

		// Read input and validate it.
		int troopNumber = -1;
		while (troopNumber<0 || troopNumber > player->reinforcementPool)
			cin >> troopNumber;


		player->issue_Order("Deploy", player, troopNumber, territoryToNumberMap[territoryChoice], territoryToNumberMap[territoryChoice]);

		cout << "Deploy order issued." << endl;

		// Adjust the uncommitted reinforcement pool
		player->reinforcementPool = (player->reinforcementPool - troopNumber);
		break;
	}
	case 1:
	{
		// Advance

		// List the territories the player can choose as starting point
		cout << "From which territory would you like to select troops from?" << endl;
		std::map<int, Territory*> sourceTerritoryToNumberMap = map<int, Territory*>();
		int counter = 0;
		for (Territory* t : this->to_defend(player))
		{
			// We can choose a starting point only if there are armies in it.
			if (t->numArmies > 0)
			{
				sourceTerritoryToNumberMap[counter] = t;

				cout << counter << ": " << t->name << " (" << t->numArmies << " troops)" << endl;
				counter++;
			}
		}

		// Read input and validate it.
		int sourceTerritoryChoice = -1;
		while (sourceTerritoryChoice<0 || sourceTerritoryChoice > this->to_defend(player).size())
			cin >> sourceTerritoryChoice;

		cout << "How many troops would you like to move? (" << sourceTerritoryToNumberMap[sourceTerritoryChoice]->numArmies << " remaining in your territory.)" << endl;

		// Read input and validate it.
		int troopNumber = -1;
		while (troopNumber<0 || troopNumber > sourceTerritoryToNumberMap[sourceTerritoryChoice]->numArmies)
			cin >> troopNumber;

		// List the territories the player can choose to advance to
		cout << "To which territory would you like to advance your troops to?" << endl;
		std::map<int, Territory*> destinationTerritoryToNumberMap = map<int, Territory*>();
		int counter2 = 0;

		cout << "Territories to attack: " << endl;
		for (Territory* t : this->to_attack(player))
		{
			if (sourceTerritoryToNumberMap[sourceTerritoryChoice]->isAnEdge(t))
			{
				destinationTerritoryToNumberMap[counter2] = t;
				cout << counter2 << ": " << t->name << " (" << t->name << " troops)" << endl;
				counter2++;
			}
		}

		cout << "Territories to defend: " << endl;
		for (Territory* t : this->to_defend(player))
		{
			if (sourceTerritoryToNumberMap[sourceTerritoryChoice]->isAnEdge(t))
			{
				destinationTerritoryToNumberMap[counter2] = t;
				cout << counter2 << ": " << t->name << " (" << t->numArmies << " troops)" << endl;
				counter2++;
			}
		}

		// Read input and validate it.
		int destinationTerritoryChoice = -1;
		while (destinationTerritoryChoice<0 || destinationTerritoryChoice > destinationTerritoryToNumberMap.size())
			cin >> destinationTerritoryChoice;


		player->issue_Order("Advance", player, troopNumber, destinationTerritoryToNumberMap.at(destinationTerritoryChoice), sourceTerritoryToNumberMap.at(sourceTerritoryChoice));

		cout << "Advance order issued." << endl;
		break;
	}
	case 2:
	{
		// Play a card

		cout << "Which card would you like to play?" << endl;

		int counter = 0;
		std::map<int, Card*> cardsToNumbers = std::map<int, Card*>();

		// Creating an iterator
		std::list<Card>::iterator iterator;

		// Iterating through the hand
		for (Card* c : player->getHand()->cardHand) {
			cardsToNumbers[counter] = &*c;
			cout << counter << ": " << c << endl;
			counter++;
		}

		// Read input and validate it.
		int cardChoice = -1;
		while (cardChoice < 0 || cardChoice > player->getHand()->getNumberOfCardsInHand())
			cin >> cardChoice;

		// Playing the card.
		Card* card = cardsToNumbers[cardChoice];

		cout << "Playing a card: " << card << endl;

		//TODO Play Card

		break;
	}
	case 3:
		cout << "Ending turn." << endl;
		return false;
	default:
		throw exception("Invalid action chosen for a player's turn.");
	}
	return true;
}

HumanPlayerStrategy::HumanPlayerStrategy(const HumanPlayerStrategy& strategy) {
	this->setStrategyName(strategy.getStrategyName());
}

std::ostream& operator<<(ostream& out, const HumanPlayerStrategy& strategy) {
	return out << strategy.getStrategyName();
}

HumanPlayerStrategy& HumanPlayerStrategy::operator=(const HumanPlayerStrategy& strategy) {
	if (this != &strategy)
	{
		this->setStrategyName(strategy.getStrategyName());
	}
	return *this;
}


/* AggressivePlayerStrategy class */
AggressivePlayerStrategy::AggressivePlayerStrategy() {
	setStrategyName("Aggressive");
	strongestTerritory = nullptr;
	advanceAllowed = true;
}

AggressivePlayerStrategy::~AggressivePlayerStrategy() {
	strongestTerritory = nullptr;
}


Territory* AggressivePlayerStrategy::getStrongestTerritory() {
	return strongestTerritory;
}

void AggressivePlayerStrategy::setStrongestTerritory(Player* player) {
	this->strongestTerritory = player->getTerritory()[0];
	for (int i = 0; i < player->getTerritory().size(); i++) {
		if (this->strongestTerritory->numArmies < player->getTerritory()[i]->numArmies)
			this->strongestTerritory = player->getTerritory()[i];
	}
}

vector<Territory*> AggressivePlayerStrategy::to_defend(Player* player) {
	return player->getTerritory();
}

vector<Territory*> AggressivePlayerStrategy::to_attack(Player* player) {
	std::set<Territory*> territoriesToAttack = set<Territory*>();

	// Loop through all our territories...
	for (Territory* t : player->getTerritory())
	{
		for (Territory* adj : t->edges) {

			if (adj->owner != player)
				territoriesToAttack.emplace(adj);
		}
	}

	// Transforming the set to a vector.
	vector<Territory*> setToVector = vector<Territory*>();

	setToVector.reserve(territoriesToAttack.size());
	for (Territory* t : territoriesToAttack)
	{
		setToVector.push_back(t);
	}
	return setToVector;
}

bool AggressivePlayerStrategy::issueOrder(Player* player) {
	int actionNumber = -1;

	std::random_device randomDevice;
	std::mt19937 mt(randomDevice());

	setStrongestTerritory(player);
	// If some reinforcements are left in the pool of the player, he can only take deploy actions.
	if (player->reinforcementPool > 0) {
		advanceAllowed = true;
		cout << "You have reinforcements in your pool. Only deploy orders are allowed." << endl;
		// Deploy
		actionNumber = 0;
	}
	else {
		list<int> possibleActions = list<int>();

		// Advance
		if (advanceAllowed) {
			possibleActions.push_back(1);
		}

		// Play a card
		if (player->getHand()->getNumberOfCardsInHand() > 0)
			possibleActions.push_back(2);

		// End turn
		possibleActions.push_back(3);

		// Generate a random input
		std::uniform_int_distribution<int> distribution(0, possibleActions.size() - 1);

		auto iterator = std::next(possibleActions.begin(), distribution(mt));
		actionNumber = *iterator;
	}

	// Depending on which action was chosen, create an appropriate order.
	switch (actionNumber) {
	case 0: {
		// Deploy

		// Choose a territory

		// Generate a random input
		std::uniform_int_distribution<int> distributionTroops(1, player->reinforcementPool);
		int troopNumber = distributionTroops(mt);

		player->issue_Order("Deploy", player, troopNumber, strongestTerritory, strongestTerritory);

		cout << "Deploy order issued." << endl;

		// Adjust the uncommitted reinforcement pool.
		player->reinforcementPool = (player->reinforcementPool - troopNumber);
		break;
	}
	case 1: {

		// Advance

		// Choosing a starting point
		for (int i = 0; i < to_defend(player).size(); i++) {
			int sourceTerritoryChoice = i;

			// Choosing randomly a number of troops to move;

			int troopNumber = to_defend(player)[sourceTerritoryChoice]->numArmies;
			if (troopNumber > 0) {
				// Choose a territory for the player to advance to.
				std::map<int, Territory*> destinationTerritoryToNumberMap = map<int, Territory*>();
				int counter2 = 0;

				for (int j = 0;
					j < to_defend(player)[sourceTerritoryChoice]->edges.size(); j++) {
					if (to_defend(player)[sourceTerritoryChoice]->edges[j]->owner == nullptr || player->pName.compare(
						to_defend(player)[sourceTerritoryChoice]->edges[j]->owner->pName) != 0) {
						destinationTerritoryToNumberMap[counter2] = to_defend(
							player)[sourceTerritoryChoice]->edges[j];
						counter2++;
					}
				}

				if (destinationTerritoryToNumberMap.size() == 0) {
					if (to_defend(player)[i]->id == strongestTerritory->id) {
						std::uniform_int_distribution<int> distributionDestination(0,
							strongestTerritory->edges.size() -
							1);
						int destinationTerritoryChoice = distributionDestination(mt);

						player->issue_Order("Advance", player, troopNumber, strongestTerritory->edges[destinationTerritoryChoice], to_defend(player).at(sourceTerritoryChoice));

					}
					else {

						player->issue_Order("Advance", player, troopNumber, strongestTerritory, to_defend(player).at(sourceTerritoryChoice));

					}
				}
				else {
					std::uniform_int_distribution<int> distributionDestination(0,
						destinationTerritoryToNumberMap.size() -
						1);
					int destinationTerritoryChoice = distributionDestination(mt);
					player->issue_Order("Advance", player, troopNumber, destinationTerritoryToNumberMap[destinationTerritoryChoice], to_defend(player).at(sourceTerritoryChoice));
				}
			}
		}
		advanceAllowed = false;
		break;
	}
	case 2: {
		// Play a card

		int counter = 0;
		std::map<int, Card*> cardsToNumbers = std::map<int, Card*>();

		// Iterating through the hand
		for (Card* c : player->getHand()->cardHand) {
			cardsToNumbers[counter] = &*c;
			counter++;
		}

		// Generate a random input
		if (counter > 0) {
			std::uniform_int_distribution<int> distribution(0, player->hand->getNumberOfCardsInHand() - 1);
			int cardChoice = distribution(mt);

			// Playing the card.
			Card* card = cardsToNumbers[cardChoice];

			cout << "Playing a card: " << card << endl;
			//TODO Play the card
		}
		break;
	}
	case 3:
		// End Turn
		cout << "Ending turn.\n" << endl;
		return false;
	default:
		throw exception("Invalid action chosen for a player's turn.");
	}

	return true;
}

AggressivePlayerStrategy::AggressivePlayerStrategy(const AggressivePlayerStrategy& strategy) : PlayerStrategy(strategy) {
	strongestTerritory = strategy.strongestTerritory;
	advanceAllowed = strategy.advanceAllowed;
}

std::ostream& operator<<(ostream& out, const AggressivePlayerStrategy& strategy) {
	return out << strategy.getStrategyName() << " AdvanceAllowed: " << strategy.advanceAllowed
		<< " StrongestTerritory: " << strategy.strongestTerritory->name;
}

AggressivePlayerStrategy& AggressivePlayerStrategy::operator=(const AggressivePlayerStrategy& strategy) {
	if (this != &strategy)
	{
		strongestTerritory = nullptr;
		strongestTerritory = strategy.strongestTerritory;
		advanceAllowed = strategy.advanceAllowed;
		setStrategyName(strategy.getStrategyName());
	}
	return *this;
}


//BenevolentPlayerStrategy class
BenevolentPlayerStrategy::BenevolentPlayerStrategy() {
	setStrategyName("Benevolent");
	weakestTerritory = nullptr;
	weakestTerritories = vector<Territory*>();
}

BenevolentPlayerStrategy::~BenevolentPlayerStrategy() {
	weakestTerritory = nullptr;
	for (Territory* ptr : weakestTerritories)
	{
		ptr = nullptr;
	}
}

Territory* BenevolentPlayerStrategy::getWeakestTerritory() {
	return weakestTerritory;
}

vector<Territory*> BenevolentPlayerStrategy::getWeakestTerritories(Player* player) {
	weakestTerritories.clear();
	this->weakestTerritory = player->getTerritory()[0];
	for (int i = 0; i < player->getTerritory().size(); i++) {
		if (this->weakestTerritory->numArmies > player->getTerritory()[i]->numArmies)
			this->weakestTerritory = player->getTerritory()[i];
	}
	weakestTerritories.push_back(this->weakestTerritory);
	for (Territory* t : player->getTerritory()) {
		if (t->numArmies == this->weakestTerritory->numArmies)
			weakestTerritories.push_back(t);
	}
	return weakestTerritories;
}

vector<Territory*> BenevolentPlayerStrategy::to_defend(Player* player) {
	return player->getTerritory();
}

vector<Territory*> BenevolentPlayerStrategy::to_attack(Player* player) {
	std::set<Territory*> territoriesToAttack = set<Territory*>();

	// Loop through all our territories...
	for (Territory* t : player->getTerritory())
	{
		for (Territory* adj : t->edges) {

			if (adj->owner != player)
				territoriesToAttack.emplace(adj);
		}
	}

	// Transforming the set to a vector.
	vector<Territory*> setToVector = vector<Territory*>();

	setToVector.reserve(territoriesToAttack.size());
	for (Territory* t : territoriesToAttack)
	{
		setToVector.push_back(t);
	}
	return setToVector;
}

bool BenevolentPlayerStrategy::issueOrder(Player* player) {
	int actionNumber = -1;

	std::random_device randomDevice;
	std::mt19937 mt(randomDevice());

	// If some reinforcements are left in the pool of the player, he can only take deploy actions.
	if (player->reinforcementPool > 0)
	{
		cout << "You have reinforcements in your pool. Only deploy orders are allowed." << endl;
		// Deploy
		actionNumber = 0;
	}
	else
	{
		list<int> possibleActions = list<int>();

		// Advance
		bool advanceAllowed = false;
		// Checking if an advance can be done
		getWeakestTerritories(player);
		for (Territory* t : player->getTerritory())
		{
			if (t->numArmies > weakestTerritory->numArmies)
				advanceAllowed = true;
		}

		if (advanceAllowed) {
			possibleActions.push_back(1);
			cout << "1: Advance " << endl;
		}

		// Play a card
		if (player->getHand()->getNumberOfCardsInHand() > 0)
			possibleActions.push_back(2);

		// End turn
		possibleActions.push_back(3);

		// Generate a random input
		std::uniform_int_distribution<int> distribution(0, possibleActions.size() - 1);

		auto iterator = std::next(possibleActions.begin(), distribution(mt));
		actionNumber = *iterator;
	}

	// Depending on which action was chosen, create an appropriate order.
	switch (actionNumber)
	{
	case 0:
	{
		// Deploy

		// Choose a territory
		std::map<int, Territory*> territoryToNumberMap = map<int, Territory*>();
		int counter = 0;
		for (Territory* t : getWeakestTerritories(player)) //********************
		{
			territoryToNumberMap[counter] = t;
			counter++;
		}

		// Generate a random input
		std::uniform_int_distribution<int> distribution(0, territoryToNumberMap.size() - 1);

		int territoryChoice = distribution(mt);

		// Generate a random input
		std::uniform_int_distribution<int> distributionTroops(1, player->reinforcementPool);
		int troopNumber = distributionTroops(mt);

		player->issue_Order("Deploy", player, troopNumber, territoryToNumberMap[territoryChoice], territoryToNumberMap[territoryChoice]);

		cout << "Deploy order issued." << endl;

		// Adjust the uncommitted reinforcement pool.
		player->reinforcementPool = (player->reinforcementPool - troopNumber);
		break;
	}
	case 1:
	{
		// Advance

		// Choosing a starting point
		std::map<int, Territory*> sourceTerritoryToNumberMap = map<int, Territory*>();
		int counter = 0;
		for (Territory* t : player->getTerritory())
		{
			// We can choose a starting point only if it has any armies.
			if (t->numArmies > weakestTerritory->numArmies)
			{
				sourceTerritoryToNumberMap[counter] = t;
				counter++;
			}
		}

		// Generate a random input
		std::uniform_int_distribution<int> distribution(0, sourceTerritoryToNumberMap.size() - 1);

		int sourceTerritoryChoice = distribution(mt);

		// Choosing randomly a number of troops to move
		std::uniform_int_distribution<int> distributionTroops(1, sourceTerritoryToNumberMap[sourceTerritoryChoice]->numArmies);

		int troopNumber = distributionTroops(mt);

		// Choose a territory for the player to advance to.
		std::map<int, Territory*> destinationTerritoryToNumberMap = map<int, Territory*>();
		int counter2 = 0;

		// Advancing to defend
		for (Territory* t : weakestTerritories)
		{
			if (sourceTerritoryToNumberMap[sourceTerritoryChoice]->isAnEdge(t))
			{
				destinationTerritoryToNumberMap[counter2] = t;
				counter2++;
			}
		}

		// Choosing randomly a territory to move to
		if (destinationTerritoryToNumberMap.size() != 0) {
			std::uniform_int_distribution<int> distributionDestination(0,
				destinationTerritoryToNumberMap.size() - 1);

			int destinationTerritoryChoice = distributionDestination(mt);

			player->issue_Order("Advance", player, troopNumber, destinationTerritoryToNumberMap.at(destinationTerritoryChoice), sourceTerritoryToNumberMap.at(sourceTerritoryChoice));

			cout << "Advance order issued." << endl;
		}
		else {
			cout << "This territory does not border your weakest territories" << endl;
		}
		break;
	}
	case 2:
	{
		// Play a card

		int counter = 0;
		std::map<int, Card*> cardsToNumbers = std::map<int, Card*>();


		// Iterating through the hand
		for (Card* c : player->getHand()->cardHand) {
			if (c->getType() != 2) {
				cardsToNumbers[counter] = &*c;
				counter++;
			}
		}

		// Generate a random input
		std::uniform_int_distribution<int> distribution(0, player->hand->getNumberOfCardsInHand() - 1);
		int cardChoice = distribution(mt);

		// Playing the card.
		Card* card = cardsToNumbers[cardChoice];
		
		//TODO Play card

		break;
	}
	case 3:
		// End Turn
		cout << "Ending turn.\n" << endl;
		return false;
	default:
		throw exception("Invalid action chosen for a player's turn.");
	}

	return true;
}

BenevolentPlayerStrategy::BenevolentPlayerStrategy(const BenevolentPlayerStrategy& strategy) : PlayerStrategy(strategy) {
	weakestTerritories = strategy.weakestTerritories;
	weakestTerritory = strategy.weakestTerritory;
}

std::ostream& operator<<(ostream& out, const BenevolentPlayerStrategy& strategy) {
	string weakestTerritories;
	int count = 0;
	for (Territory* territory : strategy.weakestTerritories)
	{
		if (count != 0)
			weakestTerritories += " ";
		weakestTerritories += territory->name;
	}
	return out << strategy.getStrategyName() << " WeakestTerritory: " << strategy.weakestTerritory->name <<
		" " << "WeakestTerritories:" << weakestTerritories;
}

BenevolentPlayerStrategy& BenevolentPlayerStrategy::operator=(const BenevolentPlayerStrategy& strategy) {
	if (this != &strategy)
	{
		weakestTerritories = strategy.weakestTerritories;
		weakestTerritory = strategy.weakestTerritory;
		setStrategyName(strategy.getStrategyName());
	}
	return *this;
}


/* NeutralPlayerStrategy class */
NeutralPlayerStrategy::NeutralPlayerStrategy() {
	setStrategyName("Neutral");
}
NeutralPlayerStrategy::~NeutralPlayerStrategy() {}

vector<Territory*> NeutralPlayerStrategy::to_defend(Player* player) {
	return player->getTerritory();
}

vector<Territory*> NeutralPlayerStrategy::to_attack(Player* player) {
	std::set<Territory*> territoriesToAttack = set<Territory*>();

	// Loop through all our territories...
	for (Territory* t : player->getTerritory())
	{
		for (Territory* adj : t->edges) {

			if (adj->owner != player)
				territoriesToAttack.emplace(adj);
		}
	}

	// Transforming the set to a vector.
	vector<Territory*> setToVector = vector<Territory*>();

	setToVector.reserve(territoriesToAttack.size());
	for (Territory* t : territoriesToAttack)
	{
		setToVector.push_back(t);
	}
	return setToVector;
}

bool NeutralPlayerStrategy::issueOrder(Player* player) {
	cout << "Neutral Player does not issue any orders.\n" << endl;
	return false;
}

NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy& strategy) : PlayerStrategy(strategy) {

}

std::ostream& operator<<(ostream& out, const NeutralPlayerStrategy& strategy) {
	return out << strategy.getStrategyName();
}

NeutralPlayerStrategy& NeutralPlayerStrategy::operator=(const NeutralPlayerStrategy& strategy) {
	if (this != &strategy)
	{
		setStrategyName(strategy.getStrategyName());
	}

	return *this;
}


/* CheaterPlayerStrategy class */
CheaterPlayerStrategy::CheaterPlayerStrategy() {
	setStrategyName("Cheater");
}
CheaterPlayerStrategy::~CheaterPlayerStrategy() {}

vector<Territory*> CheaterPlayerStrategy::to_defend(Player* player) {
	return player->getTerritory();
}

vector<Territory*> CheaterPlayerStrategy::to_attack(Player* player) {
	std::set<Territory*> territoriesToAttack = set<Territory*>();

	// Loop through all our territories...
	for (Territory* t : player->getTerritory())
	{
		for (Territory* adj : t->edges) {

			if (adj->owner != player)
				territoriesToAttack.emplace(adj);
		}
	}

	// Transforming the set to a vector.
	vector<Territory*> setToVector = vector<Territory*>();

	setToVector.reserve(territoriesToAttack.size());
	for (Territory* t : territoriesToAttack)
	{
		setToVector.push_back(t);
	}
	return setToVector;
}

bool CheaterPlayerStrategy::issueOrder(Player* player) {
    player->issue_Order("steal", player, 0, nullptr, nullptr);
	cout << "Ending turn.\n" << endl;
	return false;
}

CheaterPlayerStrategy::CheaterPlayerStrategy(const CheaterPlayerStrategy& strategy) : PlayerStrategy(strategy) {

}

std::ostream& operator<<(ostream& out, const CheaterPlayerStrategy& strategy) {
	return out << strategy.getStrategyName();
}

CheaterPlayerStrategy& CheaterPlayerStrategy::operator=(const CheaterPlayerStrategy& strategy) {
	if (this != &strategy)
	{
		setStrategyName(strategy.getStrategyName());
	}

	return *this;
}


