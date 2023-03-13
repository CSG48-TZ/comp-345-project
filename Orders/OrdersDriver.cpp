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
	OrdersList ol(1);

	list<Orders*> testOrders;

	int N = 21;
	int N1 = 6;
	int test = 0;

	Player* p = new Player("Dax", 1);
	Player* t = new Player("Enemy", 2);
	Player* r = new Player("random", 3);

	Maploader maploader = { "C:\\Dev\\test.txt" };

	Map map = maploader.load();

	Territory* terr = map.territories.at(14);
	Territory* terr2 = map.territories.at(8);
	Territory* terr3 = map.territories.at(23);

	t->addOwnedTerritory(terr);
	p->addOwnedTerritory(terr2);
	r->addOwnedTerritory(terr3);

	srand((int)time(0));
	Orders* o;

	//CREATION OF RANDOM ORDERS FOR PLAYER 1
	for (int i = 0; i < 10; i++) {
		test = (rand() % N1);
		switch (test) {
		case 0:
			o = new Deploy(t, p, rand() % 100, terr, terr2, i);
			break;
		case 1:
			o = new Advance(t, p, rand() % 100, terr, terr2, i);
			break;
		case 2:
			o = new Bomb(t, p, rand() % 100, terr, terr2, i);
			break;
		case 3:
			o = new Blockade(t, p, rand() % 100, terr, terr2, i);
			break;
		case 4:
			o = new Airlift(t, p, rand() % 100, terr, terr2, i);
			break;
		case 5:
			o = new Negociate(t, p, rand() % 100, terr, terr2, i);
			break;
		default:
			o = new Deploy(t, p, rand() % 100, terr, terr2, i);
		}

		testOrders.push_back(o);
	}

	list<Orders*>::iterator it;

	//ADDING ORDERS TO PLAYER 1 LIST OF ORDER.
	for (it = testOrders.begin(); it != testOrders.end(); it++) {
		ol.add(*it);
	}

	//SHOWING CURRENT ORDERS ON SCREEN
	cout << "Current number of order in list: " << ol.getCurrentNumberOfOrders();
	cout << "\n\nCurrent orders are: \n";

	list<Orders*> currentList;

	currentList = ol.getCurrentOrdersList();
	Orders* current;

	for (it = currentList.begin(); it != currentList.end(); it++) {
		current = *it;
		cout << *current << "\n";
	}

	//PAUSE
	cout << "\nPress any key to continue..";
	cin.get();

	/* PART 1 CODE 
	//CHOOSING A RANDOM ORDER MOVE
	int index = rand() % ol.getCurrentNumberOfOrders();
	int toIndex = rand() % ol.getCurrentNumberOfOrders();

	cout << "\nMoving order from index: " << index << " to index: " << toIndex << "...";

	//PAUSE
	cout << "\nPress any key to continue..";
	cin.get();

	//SHOWCASING THE MOVE() FUNCTION
	ol.move(index, toIndex);

	//SHOWING UPDATED DATA
	cout << "\n\nUpdated Current orders are: \n";


	currentList = ol.getCurrentOrdersList();

	for (it = currentList.begin(); it != currentList.end(); it++) {
		current = *it;
		cout << *current << "\n";
	}

	//PAUSE
	cout << "\nPress any key to continue..";
	cin.get();

	//CHOOSING A RANDOM ORDER TO REMOVE MOVE
	index = rand() % ol.getCurrentNumberOfOrders();

	cout << "\nRemoving order at index: " << index << "...";

	//PAUSE
	cout << "\nPress any key to continue..";
	cin.get();

	ol.remove(index);

	//SHOWING UPDATED DATA
	cout << "\n\nUpdated Current orders are: \n";


	currentList = ol.getCurrentOrdersList();

	for (it = currentList.begin(); it != currentList.end(); it++) {
		current = *it;
		cout << *current << "\n";
	}

	//PAUSE
	cout << "\nPress any key to continue..";
	cin.get();
	*/

	//VALIDATING ALL ORDERS IN ORDER

	cout << "\n\nTrying to validate current orders... **ALL WILL FAIL** \n";

	//PAUSE
	cout << "\nPress any key to continue..";
	cin.get();

	for (it = currentList.begin(); it != currentList.end(); it++) {
		current = *it;
		cout << "\n";
		if (current->validate()) {
			cout << "\nOrder " << current->getOrderNumber() << " is valid!\n\n";
		}
	}

	//EXECUTING ALL ORDERS IN ORDER

	cout << "\nTrying to execute current orders... **ALL WILL FAIL SINCE ORDERS ARE INVALID BY DEFAULT** \n\n";

	//PAUSE
	cout << "\nPress any key to continue..";
	cin.get();

	for (it = currentList.begin(); it != currentList.end(); it++) {
		Orders* current = *it;
		if (!current->execute()) {
			cout << "\nOrder " << current->getOrderNumber() << " could not be executed because it is invalid!\n\n";
		}
	}


	delete p, t, r, terr, terr2;

	return 0;
}

