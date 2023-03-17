#include "GameEngine.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
    cout << "Reinforcement Phase" << endl;
    GameEngine* game = new GameEngine;
    string command;
    game->reinforcementPhase();
    delete game;
    game = NULL;
    return 0;
}
