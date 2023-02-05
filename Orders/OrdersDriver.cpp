// Orders.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "OrdersList.h"

int main()
{
    OrdersList ol(1);

    list<Orders> testOrders;

    int N = 21;
    int N1 = 6;
    int test = (rand() % N1);

    for (int i = 0; i < 10; i++) {
        Orders add = Orders((rand() % 5), (rand() % N1), 1, rand() % N, rand() % N, rand() % N);
        testOrders.push_front(add);
    }

    list<Orders>::iterator it;

    for (it = testOrders.begin(); it != testOrders.end(); it++) {
        ol.add(*it);
    }
    
   cout << "Current number of order in list: " << ol.getCurrentNumberOfOrders();
   cout << "\n\nCurrent orders are: \n";

   list<Orders> currentList;
    
   currentList = ol.getCurrentOrdersList();

   for (it = currentList.begin(); it != currentList.end(); it++) {
       Orders current = *it;
       cout << current.toString();
   }
}

