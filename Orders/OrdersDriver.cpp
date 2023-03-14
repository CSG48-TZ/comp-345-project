/* ==========================================
; Title:  OrdersDriver.cpp
; Author: Dario Cimmino
; Student ID: 40068769
; Date:   12 FEB 2023
; Description: This is a simple Driver to showcase different methods of the Orders, Orders subclasses and OrdersList as described in
; Programming assignment.
; ==========================================
*/
#pragma once
#include <iostream>
#include "Orders.h"

int main()
{
	cout << "\nCreating setup...";
	//Creating 3 players
	Player* p = new Player("Dax", 1);
	Player* t = new Player("Enemy", 2);
	Player* r = new Player("Neutral", 3);

	//Loading the map
	Maploader maploader = { "C:\\Dev\\test.txt" };
	Map map = maploader.load();

	//Creating some territories for DEMO.
	Territory* playerTerr = map.territories.at(14);
	Territory* targetTerr = map.territories.at(8);
	Territory* neutralTerr = map.territories.at(23);

	Territory* t1 = map.territories.at(1);
	Territory* t2 = map.territories.at(2);
	Territory* t3 = map.territories.at(3);
	Territory* t4 = map.territories.at(4);
	Territory* t5 = map.territories.at(5);
	Territory* t6 = map.territories.at(6);

	//Adding territories to players.
	t->addOwnedTerritory(targetTerr);
	p->addOwnedTerritory(playerTerr);
	r->addOwnedTerritory(neutralTerr);

	//Adding armies to territories
	playerTerr->addArmies(500);
	targetTerr->addArmies(50);
	neutralTerr->addArmies(500);

	cout << "\n\nNumber of armies in Player 1 territory: " << playerTerr->numArmies << "\n";
	cout << "Number of armies in Player 2 territory: " << targetTerr->numArmies << "\n";
	cout << "Ownedship of Player 1 Territory: " << playerTerr->owner->getName() << "\n";
	cout << "Ownedship of Player 2 Territory: " << targetTerr->owner->getName() << "\n";


	//Showing off Advance Order:
	//Here player 1 will attack player 2 from a territory isn't owned by p1.
	cout << "\nAdvance Order 0 will be issued with a territory that is not owned by the player. Press any key to continue..";
	cin.get();
	p->issueOrder("Advance", t, 500, targetTerr, t1);

	//Here player 1 will attack player 3 from a territory isn't adjacent.
	cout << "\n\nAdvance Order 1 will be issued with a territory that is not adjacent to the target territory. Press any key to continue..";
	cin.get();
	p->issueOrder("Advance", t, 500, neutralTerr, playerTerr);
	
	//Here player 1 will attack player 3 from a territory that is owned.
	cout << "\n\nAdvance Order 2 will be issued with a territory that is owned and  adjacent to the target territory. Press any key to continue..";
	cin.get();
	p->issueOrder("Advance", t, 500, targetTerr, playerTerr);
	
	p->getOrderList()->execute();

	cout << "\n\nNumber of armies in Player 1 territory: " << playerTerr->numArmies << "\n";
	cout << "Number of armies in Player 2 territory: " << targetTerr->numArmies << "\n";
	cout << "Ownedship of Player 1 Territory: " << playerTerr->owner->getName() << "\n";
	cout << "Ownedship of Player 2 Territory: " << targetTerr->owner->getName() << "\n";


	p->clearOrdersList();;

	cout << "\n\nClearing orders list and resetting army values...\n\n";
	playerTerr->numArmies = 500;
	targetTerr->numArmies = 500;
	neutralTerr->numArmies = 500;

	//Adding territories to players.
	t->addOwnedTerritory(targetTerr);
	p->addOwnedTerritory(playerTerr);
	r->addOwnedTerritory(neutralTerr);

	//Showing BOMB Order:
	//Here player 1 will bomb iots own territorty.
	cout << "\Bomb Order 3 will be issued with a territory that owned by the same player issuing the order. Press any key to continue..";
	cin.get();
	p->issueOrder("Bomb", t, 0, playerTerr, playerTerr);

	//Here player 1 will bomb player 3 without a card.
	cout << "\n\Bomb Order 4 will be issued with no bomb card. Press any key to continue..";
	cin.get();
	p->issueOrder("Bomb", t, 500, neutralTerr, playerTerr);

	p->getOrderList()->execute();

	p->getHand()->addCard(new Card(2));

	//Here player 1 will bomb player 3 from a territory isn't adjacent.
	cout << "\n\Bomb Order 5 will be issued with a territory that is not adjacent to the target territory. Press any key to continue..";
	cin.get();
	p->issueOrder("Bomb", t, 500, neutralTerr, playerTerr);

	//Here player 1 will attack player 3 from a territory that is owned.
	cout << "\n\Bomb Order 5 will be issued with a territory that is owned and adjacent to the target territory. Press any key to continue..";
	cin.get();
	p->issueOrder("Bomb", t, 500, targetTerr, playerTerr);

	p->getOrderList()->execute();


	cout << "\n\nNumber of armies in Player 1 territory: " << playerTerr->numArmies << "\n";
	cout << "Number of armies in Player 2 territory: " << targetTerr->numArmies << "\n";
	cout << "Ownedship of Player 1 Territory: " << playerTerr->owner->getName() << "\n";
	cout << "Ownedship of Player 2 Territory: " << targetTerr->owner->getName() << "\n";

	//Showing Airlift Order:
 	p->clearOrdersList();;

	cout << "\n\nClearing orders list and resetting army values...\n\n";
	playerTerr->numArmies = 500;
	targetTerr->numArmies = 500;
	neutralTerr->numArmies = 500;
	t1->numArmies = 250;

	//Adding territories to players.
	t->addOwnedTerritory(targetTerr);
	p->addOwnedTerritory(playerTerr);
	p->addOwnedTerritory(t1);
	r->addOwnedTerritory(neutralTerr);

	//Here player 1 will airlift without a card.
	cout << "\Airlift Order 6 will be issued without a card. Press any key to continue..";
	cin.get();
	p->issueOrder("Airlift", t, 0, playerTerr, playerTerr);
	p->getOrderList()->execute();

	p->clearOrdersList();
	p->getHand()->addCard(new Card(0));

	//Here player 1 will airlift into enemy territory.
	cout << "\n\Airlift Order 7 will be issued into enemy territory. Press any key to continue..";
	cin.get();
	p->issueOrder("Airlift", t, 500, targetTerr, playerTerr);

	p->getOrderList()->execute();


	//Here player 1 will airlift troop from 2 owned territory but with not enough armies.
	cout << "\n\Airlift Order  will be issued with 500 troop from t1 territory to player territory. Press any key to continue..";
	cin.get();
	p->issueOrder("Airlift", t, 500, playerTerr, t1);

	p->getOrderList()->execute();
	p->clearOrdersList();

	//Here player 1 will airlift troop from 2 owned territories.
	cout << "\n\Airlift Order  will be issued with 250 troop from t1 territory to player territory. Press any key to continue..";
	cin.get();
	p->issueOrder("Airlift", t, 250, playerTerr, t1);
	p->getOrderList()->execute();

	cout << "\n\nNumber of armies in Player 1 territory: " << playerTerr->numArmies << "\n";
	cout << "Number of armies in t1 territory: " << t1->numArmies << "\n";
	cout << "Ownedship of Player 1 Territory: " << playerTerr->owner->getName() << "\n";
	cout << "Ownedship of t1 Territory: " << t1->owner->getName() << "\n";
	

	delete p, t, r, playerTerr, targetTerr, neutralTerr, t1, t2 ,t3, t4, t5, t6;

	return 0;
}

