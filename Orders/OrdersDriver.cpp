// Orders.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Orders.h"

int main()
{
	OrdersList ol(1);

	list<Orders> testOrders;

	int N = 21; 
	int N1 = 6;
	int test = 0;

	srand(time(0));
	Orders o;

	//CREATION OF RANDOM ORDERS FOR PLAYER 1
	for (int i = 0; i < 10; i++) {
		test = (rand() % N1);
		switch (test) {
		case 0:
			o = Deploy(rand() % N, 1, rand() % 100, rand() % 121, rand() % 121, i);
			break;
		case 1:
			o = Advance(rand() % N, 1, rand() % 100, rand() % 121, rand() % 121, i);
			break;
		case 2:
			o = Bomb(rand() % N, 1, rand() % 100, rand() % 121, rand() % 121, i);
			break;
		case 3:
			o = Blockade(rand() % N, 1, rand() % 100, rand() % 121, rand() % 121, i);
			break;
		case 4:
			o = Airlift(rand() % N, 1, rand() % 100, rand() % 121, rand() % 121, i);
			break;
		case 5:
			o = Negociate(rand() % N, 1, rand() % 100, rand() % 121, rand() % 121, i);
			break;
		default:
			o = Deploy(rand() % N, 1, rand() % 100, rand() % 121, rand() % 121, i);
		}

		testOrders.push_front(o);
	}

	list<Orders>::iterator it;

	//ADDING ORDERS TO PLAYER 1 LIST OF ORDER.
	for (it = testOrders.begin(); it != testOrders.end(); it++) {
		ol.add(*it);
	}

	//SHOWING CURRENT ORDERS ON SCREEN
	cout << "Current number of order in list: " << ol.getCurrentNumberOfOrders();
	cout << "\n\nCurrent orders are: \n";

	list<Orders> currentList;

	currentList = ol.getCurrentOrdersList();

	for (it = currentList.begin(); it != currentList.end(); it++) {
		Orders current = *it;
		cout << current.toString();
	}

	//PAUSE
	cout << "\nPress any key to continue..";
	cin.get();

	//CHOOSING A RANDOM ORDER MOVE
	int index = rand() % ol.getCurrentNumberOfOrders();
	int toIndex = rand() % ol.getCurrentNumberOfOrders();

	cout << "\nMoving order at index: " << index << " to index: " << toIndex << "...";

	//PAUSE
	cout << "\nPress any key to continue..";
	cin.get();

	//SHOWCASING THE MOVE() FUNCTION
	ol.move(index, toIndex);

	//SHOWING UPDATED DATA
	cout << "\n\nUpdated Current orders are: \n";


	currentList = ol.getCurrentOrdersList();

	for (it = currentList.begin(); it != currentList.end(); it++) {
		Orders current = *it;
		cout << current.toString();
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
		Orders current = *it;
		cout << current.toString();
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
		Orders current = *it;
		if (!current.validate()) {
			cout << "Order " << current.getOrderNumber() << " is invalid!\n";
		}
	}

	//EXECUTING ALL ORDERS IN ORDER

	cout << "\n\nTrying to execute current orders... **ALL WILL FAIL SINCE ORDERS ARE INVALID BY DEFAULT** \n";

	//PAUSE
	cout << "\nPress any key to continue..";
	cin.get();

	for (it = currentList.begin(); it != currentList.end(); it++) {
		Orders current = *it;
		if (!current.execute()) {
			cout << "Order " << current.getOrderNumber() << " could not be executed because it is invalid!\n";
		}
	}

}

