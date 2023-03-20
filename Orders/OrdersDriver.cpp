/* ==========================================
; Title:  OrdersDriver.cpp
; Author: Dario Cimmino
; Student ID: 40068769
; Date:   12 MARCH 2023
; Description: This is a simple Driver to showcase different methods of the Orders, Orders subclasses and OrdersList as described in
; Programming assignment 2.
; ==========================================
*/
#pragma once
#include <iostream>
#include "Orders.h"
#include <windows.h>

int main_()
{
	cout << "\nCreating setup...";
	//Creating 3 players
	Player* p = new Player("Dax", 1);
	Player* t = new Player("Enemy", 2);
	Player* r = new Player("Neutral", 3);

	//Loading the map
	Maploader maploader = { "C:\\Dev\\test.txt" };
	Map* map = maploader.load();

	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

	//Creating some territories for DEMO.
	Territory* playerTerr = map->territories.at(14);
	Territory* targetTerr = map->territories.at(8);
	Territory* neutralTerr = map->territories.at(23);

	Territory* t1 = map->territories.at(1);
	Territory* t2 = map->territories.at(2);
	Territory* t3 = map->territories.at(3);
	Territory* t4 = map->territories.at(4);
	Territory* t5 = map->territories.at(5);
	Territory* t6 = map->territories.at(6);

	//Adding territories to players.
	t->addOwnedTerritory(targetTerr);
	p->addOwnedTerritory(playerTerr);
	r->addOwnedTerritory(neutralTerr);

	//Adding armies to territories
	playerTerr->addArmies(500);
	targetTerr->addArmies(50);
	neutralTerr->addArmies(500);

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 6);


	
	cout << "*********************************************************************************\n";
	cout << "*                           Part 4 : Orders Execution                           *\n";
	cout << "*********************************************************************************\n\n\n";

	cout << "*********************************************************************************\n";
	cout << "*                                ADVANCE ORDER                                  *\n";
	cout << "*********************************************************************************\n\n\n";

	SetConsoleTextAttribute(hConsole, 3);
	cout << "Current setup: \n";
	cout << "*********************************************************************************\n";
	cout << "Number of armies in Player 1 territory: " << playerTerr->numArmies << "\n";
	cout << "Number of armies in Player 2 territory: " << targetTerr->numArmies << "\n";
	cout << "Ownedship of Player 1 Territory: ";
	SetConsoleTextAttribute(hConsole, 10);
	cout << playerTerr->owner->getName() << " - " << playerTerr->name << "\n";
	SetConsoleTextAttribute(hConsole, 3);
	cout << "Ownedship of Player 2 Territory: ";
	SetConsoleTextAttribute(hConsole, 12);
	cout << targetTerr->owner->getName() << " - " << targetTerr->name << "\n";
	SetConsoleTextAttribute(hConsole, 3);
	cout << "*********************************************************************************\n\n";

	//Showing off Advance Order:
	//Here player 1 will attack player 2 from a territory isn't owned by p1.
	SetConsoleTextAttribute(hConsole, 6);
	cout << "\n\nAdvance Order 0 will be issued with a territory that is not owned by the player.\nPress any key to continue..";
	cin.get();
	p->issueOrder("Advance", t, 500, targetTerr, t1);
	cout << "*********************************************************************************";
	SetConsoleTextAttribute(hConsole, 4);
	p->getOrderList()->execute();
	p->clearOrdersList();
	SetConsoleTextAttribute(hConsole, 6);
	cout << "\n*********************************************************************************\n\n";

	//Here player 1 will attack player 3 from a territory isn't adjacent.
	cout << "\n\nAdvance Order 1 will be issued with a territory that is not adjacent to the target territory. \nPress any key to continue..";
	cin.get();
	p->issueOrder("Advance", t, 500, neutralTerr, playerTerr);
	cout << "*********************************************************************************";
	SetConsoleTextAttribute(hConsole, 4);
	p->getOrderList()->execute();
	p->clearOrdersList();
	SetConsoleTextAttribute(hConsole, 6);
	cout << "\n*********************************************************************************\n\n";

	//Here player 1 will attack player 3 from a territory that is owned.
	cout << "\n\nAdvance Order 2 will be issued with a territory that is owned and  adjacent to the target territory. \nPress any key to continue..";
	cin.get();
	p->issueOrder("Advance", t, 500, targetTerr, playerTerr);
	cout << "*********************************************************************************";
	SetConsoleTextAttribute(hConsole, 10);
	p->getOrderList()->execute();
	p->clearOrdersList();
	SetConsoleTextAttribute(hConsole, 6);
	cout << "\n*********************************************************************************\n\n";

	//Current Values
	SetConsoleTextAttribute(hConsole, 3);
	cout << "Current setup: \n";
	cout << "*********************************************************************************\n";
	cout << "Number of armies in Player 1 territory: " << playerTerr->numArmies << "\n";
	cout << "Number of armies in Player 2 territory: " << targetTerr->numArmies << "\n";
	cout << "Ownedship of Player 1 Territory: ";
	SetConsoleTextAttribute(hConsole, 10);
	cout << playerTerr->owner->getName() << " - " << playerTerr->name << "\n";
	SetConsoleTextAttribute(hConsole, 3);
	cout << "Ownedship of Player 2 Territory: ";
	SetConsoleTextAttribute(hConsole, 12);
	cout << targetTerr->owner->getName() << " - " << targetTerr->name << "\n";
	SetConsoleTextAttribute(hConsole, 3);
	cout << "*********************************************************************************\n\n";

	cout << "Press Any Key To Continue...\n";
	cin.get();
	SetConsoleTextAttribute(hConsole, 6);
	cout << "*********************************************************************************\n";
	cout << "*                                BOMB    ORDER                                  *\n";
	cout << "*********************************************************************************\n\n\n";

	//Clears the Orders List.
	p->clearOrdersList();

	//Reset Values and Ownerships.
	SetConsoleTextAttribute(hConsole, 4);
	cout << "\n\nClearing orders list and resetting army values...\n\n";
	playerTerr->numArmies = 500;
	targetTerr->numArmies = 500;
	neutralTerr->numArmies = 500;

	//Adding territories to players.
	t->addOwnedTerritory(targetTerr);
	p->addOwnedTerritory(playerTerr);
	r->addOwnedTerritory(neutralTerr);

	//Current values
	SetConsoleTextAttribute(hConsole, 3);
	cout << "Current setup: \n";
	cout << "*********************************************************************************\n";
	cout << "Number of armies in Player 1 territory: " << playerTerr->numArmies << "\n";
	cout << "Number of armies in Player 2 territory: " << targetTerr->numArmies << "\n";
	cout << "Ownedship of Player 1 Territory: ";
	SetConsoleTextAttribute(hConsole, 10);
	cout << playerTerr->owner->getName() << " - " << playerTerr->name << "\n";
	SetConsoleTextAttribute(hConsole, 3);
	cout << "Ownedship of Player 2 Territory: ";
	SetConsoleTextAttribute(hConsole, 12);
	cout << targetTerr->owner->getName() << " - " << targetTerr->name << "\n";
	SetConsoleTextAttribute(hConsole, 3);
	cout << "*********************************************************************************\n\n";

	
	//Showing BOMB Order:
	


	//Here player 1 will bomb its own territory.
	SetConsoleTextAttribute(hConsole, 6);
	cout << "\nBomb Order 3 will be issued with a territory that owned by the same player issuing the order. \nPress any key to continue..";
	cin.get();
	p->issueOrder("Bomb", t, 0, playerTerr, playerTerr);
	cout << "*********************************************************************************";
	SetConsoleTextAttribute(hConsole, 4);
	p->getOrderList()->execute();
	p->clearOrdersList();
	SetConsoleTextAttribute(hConsole, 6);
	cout << "\n*********************************************************************************\n\n";

	//Here player 1 will bomb player 3 without a card.
	cout << "\nBomb Order 4 will be issued with no bomb card. \nPress any key to continue..";
	cin.get();
	p->issueOrder("Bomb", t, 500, targetTerr, playerTerr);
	cout << "*********************************************************************************";
	SetConsoleTextAttribute(hConsole, 4);
	p->getOrderList()->execute();
	p->clearOrdersList();
	SetConsoleTextAttribute(hConsole, 6);
	cout << "\n*********************************************************************************\n\n";

	SetConsoleTextAttribute(hConsole, 7);
	cout << "\nADDED CARD \"BOMB\" TO PLAYER 1\n\n";
	p->getHand()->addCard(new Card(2));

	//Here player 1 will bomb player 3 from a territory isn't adjacent.
	SetConsoleTextAttribute(hConsole, 6);
	cout << "\n\nBomb Order 5 will be issued with a territory that is not adjacent to the target territory. \nPress any key to continue..";
	cin.get();
	p->issueOrder("Bomb", t, 500, neutralTerr, playerTerr);
	cout << "*********************************************************************************";
	SetConsoleTextAttribute(hConsole, 4);
	p->getOrderList()->execute();
	p->clearOrdersList();
	SetConsoleTextAttribute(hConsole, 6);
	cout << "\n*********************************************************************************\n\n";

	//Here player 1 will attack player 3 from a territory that is owned.
	cout << "\n\nBomb Order 6 will be issued with a territory that is owned and adjacent to the target territory. \nPress any key to continue..";
	cin.get();
	p->issueOrder("Bomb", t, 500, targetTerr, playerTerr);
	cout << "*********************************************************************************";
	SetConsoleTextAttribute(hConsole, 10);
	p->getOrderList()->execute();
	p->clearOrdersList();
	SetConsoleTextAttribute(hConsole, 6);
	cout << "\n*********************************************************************************\n\n";

	//CURRENT VALUES
	//Current values
	SetConsoleTextAttribute(hConsole, 3);
	cout << "Current setup: \n";
	cout << "*********************************************************************************\n";
	cout << "Number of armies in Player 1 territory: " << playerTerr->numArmies << "\n";
	cout << "Number of armies in Player 2 territory: " << targetTerr->numArmies << "\n";
	cout << "Ownedship of Player 1 Territory: ";
	SetConsoleTextAttribute(hConsole, 10);
	cout << playerTerr->owner->getName() << " - " << playerTerr->name << "\n";
	SetConsoleTextAttribute(hConsole, 3);
	cout << "Ownedship of Player 2 Territory: ";
	SetConsoleTextAttribute(hConsole, 12);
	cout << targetTerr->owner->getName() << " - " << targetTerr->name << "\n";
	SetConsoleTextAttribute(hConsole, 3);
	cout << "*********************************************************************************\n\n";


	cout << "Press Any Key To Continue...\n";
	cin.get();
	SetConsoleTextAttribute(hConsole, 6);
	cout << "*********************************************************************************\n";
	cout << "*                                AIRLIFT ORDER                                  *\n";
	cout << "*********************************************************************************\n\n\n";

	//reset orders list.
	p->clearOrdersList();;


	//Showing Airlift Order:

	//RESET VALUES
	SetConsoleTextAttribute(hConsole, 4);
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

	//Current values
	SetConsoleTextAttribute(hConsole, 3);
	cout << "Current setup: \n";
	cout << "*********************************************************************************\n";
	cout << "Number of armies in Player 1 territory: " << playerTerr->numArmies << "\n";
	cout << "Number of armies in Player 1 - Second territory: " << t1->numArmies << "\n";
	cout << "Ownedship of Player 1 Territory: ";
	SetConsoleTextAttribute(hConsole, 10);
	cout << playerTerr->owner->getName() << " - " << playerTerr->name << "\n";
	SetConsoleTextAttribute(hConsole, 3);
	cout << "Ownedship of Player 2 Territory: ";
	SetConsoleTextAttribute(hConsole, 12);
	cout << targetTerr->owner->getName() << " - " << targetTerr->name << "\n";
	SetConsoleTextAttribute(hConsole, 3);
	cout << "Ownedship of Player 1 - Second Territory: ";
	SetConsoleTextAttribute(hConsole, 10);
	cout << t1->owner->getName() << " - " << t1->name << "\n";
	SetConsoleTextAttribute(hConsole, 3);
	cout << "*********************************************************************************\n\n";

	//Here player 1 will airlift without a card.
	SetConsoleTextAttribute(hConsole, 6);
	cout << "\nAirlift Order 7 will be issued without a card. \nPress any key to continue..";
	cin.get();
	p->issueOrder("Airlift", p, 0, playerTerr, playerTerr);
	cout << "*********************************************************************************";
	SetConsoleTextAttribute(hConsole, 4);
	p->getOrderList()->execute();
	p->clearOrdersList();
	SetConsoleTextAttribute(hConsole, 6);
	cout << "\n*********************************************************************************\n\n";


	SetConsoleTextAttribute(hConsole, 7);
	cout << "\nADDED CARD \"AIRLIFT\" TO PLAYER 1\n\n";
	p->getHand()->addCard(new Card(0));

	//Here player 1 will airlift into enemy territory.
	SetConsoleTextAttribute(hConsole, 6);
	cout << "\nAirlift Order 8 will be issued into enemy territory. \nPress any key to continue..";
	cin.get();
	p->issueOrder("Airlift", t, 500, targetTerr, playerTerr);
	cout << "*********************************************************************************";
	SetConsoleTextAttribute(hConsole, 4);
	p->getOrderList()->execute();
	p->clearOrdersList();
	SetConsoleTextAttribute(hConsole, 6);
	cout << "\n*********************************************************************************\n\n";


	//Here player 1 will airlift troop from 2 owned territory but with not enough armies.
	cout << "\nAirlift Order 9 will be issued with 500 troop from t1 territory to player territory. \nPress any key to continue..";
	cin.get();
	p->issueOrder("Airlift", p, 500, playerTerr, t1);
	cout << "*********************************************************************************";
	SetConsoleTextAttribute(hConsole, 4);
	p->getOrderList()->execute();
	p->clearOrdersList();
	SetConsoleTextAttribute(hConsole, 6);
	cout << "\n*********************************************************************************\n\n";

	//Here player 1 will airlift troop from 2 owned territories.
	cout << "\n\nAirlift Order 10 will be issued with 250 troop from t1 territory to player territory. \nPress any key to continue..";
	cin.get();
	p->issueOrder("Airlift", p, 250, playerTerr, t1);
	cout << "*********************************************************************************";
	SetConsoleTextAttribute(hConsole, 10);
	p->getOrderList()->execute();
	p->clearOrdersList();
	SetConsoleTextAttribute(hConsole, 6);
	cout << "\n*********************************************************************************\n\n";

	//Current values
	SetConsoleTextAttribute(hConsole, 3);
	cout << "Current setup: \n";
	cout << "*********************************************************************************\n";
	cout << "Number of armies in Player 1 territory: " << playerTerr->numArmies << "\n";
	cout << "Number of armies in Player 1 - Second territory: " << t1->numArmies << "\n";
	cout << "Ownedship of Player 1 Territory: ";
	SetConsoleTextAttribute(hConsole, 10);
	cout << playerTerr->owner->getName() << " - " << playerTerr->name << "\n";
	SetConsoleTextAttribute(hConsole, 3);
	cout << "Ownedship of Player 2 Territory: ";
	SetConsoleTextAttribute(hConsole, 12);
	cout << targetTerr->owner->getName() << " - " << targetTerr->name << "\n";
	SetConsoleTextAttribute(hConsole, 3);
	cout << "Ownedship of Player 1 - Second Territory: ";
	SetConsoleTextAttribute(hConsole, 10);
	cout << t1->owner->getName() << " - " << t1->name << "\n";
	SetConsoleTextAttribute(hConsole, 3);
	cout << "*********************************************************************************\n\n";

	cout << "Press Any Key To Continue...\n";
	cin.get();
	SetConsoleTextAttribute(hConsole, 6);
	cout << "*********************************************************************************\n";
	cout << "*                                 DEPLOY ORDER                                  *\n";
	cout << "*********************************************************************************\n\n\n";

	//Deploy DEMO
	//Here player 1 will DEPLOY troop to a enemy territory.
	cout << "\nDeploy Order 11 will be issued with 500 troop by player 1 to player 2 territory. \nPress any key to continue..";
	cin.get();
	p->issueOrder("Deploy", t, 500, targetTerr, playerTerr);
	cout << "*********************************************************************************";
	SetConsoleTextAttribute(hConsole, 4);
	p->getOrderList()->execute();
	p->clearOrdersList();
	SetConsoleTextAttribute(hConsole, 6);
	cout << "\n*********************************************************************************\n\n";

	//Here player 1 will DEPLOY troop to a owned territory.
	cout << "\n\nDeploy Order 12 will be issued with 500 troop by player 1 to own territory. \nPress any key to continue..";
	cin.get();
	p->issueOrder("Deploy", t, 500, playerTerr, playerTerr);
	cout << "*********************************************************************************";
	SetConsoleTextAttribute(hConsole, 10);
	p->getOrderList()->execute();
	p->clearOrdersList();
	SetConsoleTextAttribute(hConsole, 6);
	cout << "\n*********************************************************************************\n\n";

	//Current values
	SetConsoleTextAttribute(hConsole, 3);
	cout << "Current setup: \n";
	cout << "*********************************************************************************\n";
	cout << "Number of armies in Player 1 territory: " << playerTerr->numArmies << "\n";
	cout << "Number of armies in Player 1 - Second territory: " << t1->numArmies << "\n";
	cout << "Ownedship of Player 1 Territory: ";
	SetConsoleTextAttribute(hConsole, 10);
	cout << playerTerr->owner->getName() << " - " << playerTerr->name << "\n";
	SetConsoleTextAttribute(hConsole, 3);
	cout << "Ownedship of Player 1 - Second Territory: ";
	SetConsoleTextAttribute(hConsole, 10);
	cout << t1->owner->getName() << " - " << t1->name << "\n";
	SetConsoleTextAttribute(hConsole, 3);
	cout << "*********************************************************************************\n\n";

	cout << "Press Any Key To Continue...\n";
	cin.get();
	SetConsoleTextAttribute(hConsole, 6);
	cout << "*********************************************************************************\n";
	cout << "*                                BLOCKADE ORDER                                 *\n";
	cout << "*********************************************************************************\n\n\n";

	//BLOCKADE DEMO
	

	//Here player 1 will try to blockade without a card.
	cout << "\nBLOCKADE Order 13 will be issued without a card. \nPress any key to continue..";
	cin.get();
	p->issueOrder("Blockade", t, 500, playerTerr, playerTerr);
	cout << "*********************************************************************************";
	SetConsoleTextAttribute(hConsole, 4);
	p->getOrderList()->execute();
	p->clearOrdersList();
	SetConsoleTextAttribute(hConsole, 6);
	cout << "\n*********************************************************************************\n\n";

	SetConsoleTextAttribute(hConsole, 7);
	cout << "\nADDED CARD \"BLOCKADE\" TO PLAYER 1\n\n";
	p->getHand()->addCard(new Card(1)); //1 for Blockade
	SetConsoleTextAttribute(hConsole, 6);

	//Here player 1 will try to blockade enemy territory.
	cout << "\n\nBLOCKADE Order 14 will be issued into enemy territory. \nPress any key to continue..";
	cin.get();
	p->issueOrder("Blockade", t, 500, targetTerr, playerTerr);
	cout << "*********************************************************************************";
	SetConsoleTextAttribute(hConsole, 4);
	p->getOrderList()->execute();
	p->clearOrdersList();
	SetConsoleTextAttribute(hConsole, 6);
	cout << "\n*********************************************************************************\n\n";

	//Here player 1 will blockade his own territory.
	cout << "\n\nBLOCKADE Order 15 will be issued into owned territory. \nPress any key to continue..";
	cin.get();
	p->issueOrder("Blockade", t, 500, playerTerr, playerTerr);
	cout << "*********************************************************************************";
	SetConsoleTextAttribute(hConsole, 10);
	p->getOrderList()->execute();
	p->clearOrdersList();
	SetConsoleTextAttribute(hConsole, 6);
	cout << "\n*********************************************************************************\n\n";

	Player* n = targetTerr->owner;
	//Current values
	SetConsoleTextAttribute(hConsole, 3);
	cout << "Current setup: \n";
	cout << "*********************************************************************************\n";
	cout << "Number of armies in Player 1 territory: " << playerTerr->numArmies << "\n";
	cout << "Ownedship of Player 1 Territory: " << playerTerr->owner->getName() << "\n";
	cout << "\n*********************************************************************************\n\n";

	
	//Reset Values and Ownerships.
	SetConsoleTextAttribute(hConsole, 4);
	cout << "\n\nClearing orders list and resetting army values...\n\n";
	playerTerr->numArmies = 500;
	targetTerr->numArmies = 500;
	neutralTerr->numArmies = 500;

	//Adding territories to players.
	t->addOwnedTerritory(targetTerr);
	p->addOwnedTerritory(playerTerr);
	r->addOwnedTerritory(neutralTerr);

	//Current values
	SetConsoleTextAttribute(hConsole, 3);
	cout << "Current setup: \n";
	cout << "*********************************************************************************\n";
	cout << "Number of armies in Player 1 territory: " << playerTerr->numArmies << "\n";
	cout << "Number of armies in Player 2 territory: " << targetTerr->numArmies << "\n";
	cout << "Ownedship of Player 1 Territory: ";
	SetConsoleTextAttribute(hConsole, 10);
	cout << playerTerr->owner->getName() << " - " << playerTerr->name << "\n";
	SetConsoleTextAttribute(hConsole, 3);
	cout << "Ownedship of Player 2 Territory: ";
	SetConsoleTextAttribute(hConsole, 12);
	cout << targetTerr->owner->getName() << " - " << targetTerr->name << "\n";
	SetConsoleTextAttribute(hConsole, 3);
	cout << "*********************************************************************************\n\n";

	cout << "Press Any Key To Continue...\n";
	cin.get();
	SetConsoleTextAttribute(hConsole, 6);
	cout << "*********************************************************************************\n";
	cout << "*                              NEGOCIATE ORDER                                  *\n";
	cout << "*********************************************************************************\n\n\n";

	//Negociate DEMO
	//Here player 1 will try to negociate without a card.
	
	cout << "\nNEGOCIATE Order 16 will be issued without a card. \nPress any key to continue..";
	cin.get();
	p->issueOrder("Negociate", t, 500, targetTerr, playerTerr);
	cout << "*********************************************************************************";
	SetConsoleTextAttribute(hConsole, 4);
	p->getOrderList()->execute();
	p->clearOrdersList();
	SetConsoleTextAttribute(hConsole, 6);
	cout << "\n*********************************************************************************\n\n";

	SetConsoleTextAttribute(hConsole, 7);
	cout << "\nADDED CARD \"NEGOCIATE\" TO PLAYER 1\n\n";
	p->getHand()->addCard(new Card(3)); //1 for Negociate
	SetConsoleTextAttribute(hConsole, 6);

	//Here player 1 will try to negociate with himself.
	SetConsoleTextAttribute(hConsole, 6);
	cout << "\nNEGOCIATE Order 17 will be issued themselves. \nPress any key to continue..";
	cin.get();
	p->issueOrder("negociate", p, 500, playerTerr, playerTerr);
	cout << "*********************************************************************************";
	SetConsoleTextAttribute(hConsole, 4);
	p->getOrderList()->execute();
	p->clearOrdersList();
	SetConsoleTextAttribute(hConsole, 6);
	cout << "\n*********************************************************************************\n\n";

	//Here player 1 will negociate with player 2.
	SetConsoleTextAttribute(hConsole, 6);
	cout << "\nNEGOCIATE Order 18 will be issued themselves. \nPress any key to continue..";
	cin.get();
	p->issueOrder("negociate", t, 500, targetTerr, playerTerr);
	cout << "*********************************************************************************";
	SetConsoleTextAttribute(hConsole, 10);
	p->getOrderList()->execute();
	p->clearOrdersList();
	SetConsoleTextAttribute(hConsole, 6);
	cout << "\n*********************************************************************************\n\n";


	//Here player 1 will try to bomb player 2.
	SetConsoleTextAttribute(hConsole, 6);
	cout << "\nBOMB Order 19 will be issued on an enemy target. \nPress any key to continue..";
	cin.get();
	p->issueOrder("bomb", t, 500, targetTerr, playerTerr);
	cout << "*********************************************************************************";
	SetConsoleTextAttribute(hConsole, 4);
	p->getOrderList()->execute();
	p->clearOrdersList();
	SetConsoleTextAttribute(hConsole, 6);
	cout << "\n*********************************************************************************\n\n";

	SetConsoleTextAttribute(hConsole, 7);
	cout << "\nADDED CARD \"BOMB\" TO PLAYER 1\n\n";
	p->getHand()->addCard(new Card(2)); //2 for BOMB
	SetConsoleTextAttribute(hConsole, 6);

	//Here player 1 will try to bomb player 2. with a card this time.
	SetConsoleTextAttribute(hConsole, 6);
	cout << "\nBOMB Order 20 will be issued on an enemy target. \nPress any key to continue..";
	cin.get();
	p->issueOrder("bomb", t, 500, targetTerr, playerTerr);
	cout << "*********************************************************************************";
	SetConsoleTextAttribute(hConsole, 4);
	p->getOrderList()->execute();
	p->clearOrdersList();
	SetConsoleTextAttribute(hConsole, 6);
	cout << "\n*********************************************************************************\n\n";

	//Current values
	SetConsoleTextAttribute(hConsole, 3);
	cout << "Current setup: \n";
	cout << "*********************************************************************************\n";
	cout << "Number of armies in Player 1 territory: " << playerTerr->numArmies << "\n";
	cout << "Number of armies in Player 2 territory: " << targetTerr->numArmies << "\n";
	cout << "Ownedship of Player 1 Territory: ";
	SetConsoleTextAttribute(hConsole, 10);
	cout << playerTerr->owner->getName() << " - " << playerTerr->name << "\n";
	SetConsoleTextAttribute(hConsole, 3);
	cout << "Ownedship of Player 2 Territory: ";
	SetConsoleTextAttribute(hConsole, 12);
	cout << targetTerr->owner->getName() << " - " << targetTerr->name << "\n";
	SetConsoleTextAttribute(hConsole, 3);
	cout << "*********************************************************************************\n\n";

	delete p, t, r, playerTerr, targetTerr, neutralTerr, t1, t2 ,t3, t4, t5, t6, n;

	p, t, r, playerTerr, targetTerr, neutralTerr, t1, t2, t3, t4, t5, t6, n = nullptr;

	return 0;
}

