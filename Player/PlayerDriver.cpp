/* ==========================================
; Title:  PlayerDriver.cpp
; Author: Dario Cimmino
; Student ID: 40068769
; Date:   12 FEB 2023
; Description: This is a simple Driver to showcase different methods of the Player capabilities as described in
; Programming assignment.
; ==========================================
*/

#include "Player.h"

int main(){

    // create territories that a player owns (randomly)
    vector<Territory *> terre1;
    string name;
    for (int i = 0; i < 10; i++) {
        name = "Territory " + to_string(i);
        terre1.push_back(new Territory(i, name, rand() % 5 + 1, rand() % 120, rand() % 120));
    }

    // create player
    Player* p1 = new Player("Dax", 1);

    //adds territories to the player
    vector<Territory*>::iterator it;

    for (it = terre1.begin(); it != terre1.end(); it++) {
        Territory* current = *it;
        p1->addOwnedTerritory(current);
    }
  
    //display current owned territories
    cout << "Current Owned Territories: " << endl;
    p1->printOwnedTerritoryList();

    //PAUSE
    cout << "\nPress any key to continue..";
    cin.get();

    // territories to be attacked by player 1
    vector<Territory *> attack = p1->toAttack();
    p1->printAttackList(attack);

    //PAUSE
    cout << "\nPress any key to continue..";
    cin.get();

    // territories to be defended by player 1
    vector<Territory *> defend = p1->toDefend();
    p1->printDefendList(defend);

    //PAUSE
    cout << "\nPress any key to continue..";
    cin.get();

    //Creates random orders for the player
    string orderType = "";
    int random;
    srand((int)time(0));
    // issue order for player 1
    for (int i = 0; i < 10; i++) {
        random = rand() % 6;

        switch (random) {
        case 0:
            p1->issueOrder("Deploy", rand() % 6, p1->playerID, rand() % 200 + 1, rand() % 120, rand() %120, i);
            break;
        case 1:
            p1->issueOrder("Bomb", rand() % 6, p1->playerID, rand() % 200 + 1, rand() % 120, rand() % 120, i);
            break;
        case 2:
            p1->issueOrder("Blockade", rand() % 6, p1->playerID, rand() % 200 + 1, rand() % 120, rand() % 120, i);
            break;
        case 3:
            p1->issueOrder("Advance", rand() % 6, p1->playerID, rand() % 200 + 1, rand() % 120, rand() % 120, i);
            break;
        case 4:
            p1->issueOrder("Airlift", rand() % 6, p1->playerID, rand() % 200 + 1, rand() % 120, rand() % 120, i);
            break;
        case 5:
            p1->issueOrder("Negociate", rand() % 6, p1->playerID, rand() % 200 + 1, rand() % 120, rand() % 120, i);
            break;
        default:
            break;
        }
    }

    OrdersList* p1Orders = p1->getOrderList();
    list<Orders*>::iterator it2;
    list<Orders*> currentList;
    currentList = p1Orders->getCurrentOrdersList();

    //SHOWING CURRENT ORDERS ON SCREEN
    cout << "Current number of order in list: " << p1Orders->getCurrentNumberOfOrders();
    cout << "\n\nCurrent orders are: \n";

    for (it2 = currentList.begin(); it2 != currentList.end(); it2++) {
        Orders* current = *it2;
        cout << *current << "\n";
    }

    //SHOW CURRENT HAND
    cout << "\nCurrent cards in hand are: " << "\n";
    p1->printCurrentHand();

    return 0;
}
