/* ==========================================
; Title:  OrdersDriver.cpp
; Author: Dario Cimmino
; Student ID: 40068769
; Date:   12 FEB 2023
; Description: This is a simple Driver to showcase different methods of the Orders, Orders subclasses and OrdersList as described in
; Programming assignment.
; ==========================================
*/

#include <iostream>
#include "Orders.h"

int main()
{
	OrdersList ol(1);

	list<Orders*> testOrders;

	int N = 21;
	int N1 = 6;
	int test = 0;

	srand((int)time(0));
	Orders* o;

	//CREATION OF RANDOM ORDERS FOR PLAYER 1
	for (int i = 0; i < 10; i++) {
		test = (rand() % N1);
		switch (test) {
		case 0:
			o = new Deploy(rand() % N, 1, rand() % 100, rand() % 121, rand() % 121, i);
			break;
		case 1:
			o = new Advance(rand() % N, 1, rand() % 100, rand() % 121, rand() % 121, i);
			break;
		case 2:
			o = new Bomb(rand() % N, 1, rand() % 100, rand() % 121, rand() % 121, i);
			break;
		case 3:
			o = new Blockade(rand() % N, 1, rand() % 100, rand() % 121, rand() % 121, i);
			break;
		case 4:
			o = new Airlift(rand() % N, 1, rand() % 100, rand() % 121, rand() % 121, i);
			break;
		case 5:
			o = new Negociate(rand() % N, 1, rand() % 100, rand() % 121, rand() % 121, i);
			break;
		default:
			o = new Deploy(rand() % N, 1, rand() % 100, rand() % 121, rand() % 121, i);
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

	for (it = currentList.begin(); it != currentList.end(); it++) {
		Orders* current = *it;
		cout << *current << "\n";
	}

	//PAUSE
	cout << "\nPress any key to continue..";
	cin.get();

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
		Orders* current = *it;
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
		Orders* current = *it;
		cout << *current << "\n";
	}

	//PAUSE
	cout << "\nPress any key to continue..";
	cin.get();

	//VALIDATING ALL ORDERS IN ORDER

	cout << "\n\nTrying to validate current orders... **ALL WILL FAIL** \n";

	//PAUSE
	cout << "\nPress any key to continue..";
	cin.get();

	for (it = currentList.begin(); it != currentList.end(); it++) {
		Orders* current = *it;
		if (!current->validate()) {
			cout << "\nOrder " << current->getOrderNumber() << " is invalid!\n\n";
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

	return 0;
}

