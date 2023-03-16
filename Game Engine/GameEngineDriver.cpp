#include "GameEngine.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
    cout << "***********Game Start***********\nWelcome to the game!" << endl;
    GameEngine* game = new GameEngine;
    string command;
    cout << "Initial State is " << game->getCurrentState() << endl;
    game->startupPhase();
    cout << "***********Game Over! Thank you!***********" << endl;
    delete game;
    game = NULL;
    return 0;
}
