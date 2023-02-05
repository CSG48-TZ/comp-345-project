// Orders.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Orders.h"

int main()
{
	OrdersList ol(1);

	list<Orders> testOrders;

	int N = 21;
	int N1 = 7;
	int test = (rand() % N1);

	srand(time(0));

	//CREATION OF RANDOM ORDERS FOR PLAYER 1


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

	//CHOOSING A RANDOM ORDER MOVE
	int index = rand() % ol.getCurrentNumberOfOrders() - 1;
	int toIndex = rand() % ol.getCurrentNumberOfOrders() - 1;

	cout << "\nMoving order at index: " << index << " to index: " << toIndex << "...";

	//SHOWCASING THE MOVE() FUNCTION
	ol.move(index, toIndex);

	//SHOWING UPDATED DATA
	cout << "\n\nUpdated Current orders are: \n";


	currentList = ol.getCurrentOrdersList();

	for (it = currentList.begin(); it != currentList.end(); it++) {
		Orders current = *it;
		cout << current.toString();
	}

	//CHOOSING A RANDOM ORDER TO REMOVE MOVE
	index = rand() % ol.getCurrentNumberOfOrders() - 1;

	cout << "\nRemoving order at index: " << index << "...";


	ol.remove(index);

	//SHOWING UPDATED DATA
	cout << "\n\nUpdated Current orders are: \n";


	currentList = ol.getCurrentOrdersList();

	for (it = currentList.begin(); it != currentList.end(); it++) {
		Orders current = *it;
		cout << current.toString();
	}


}

