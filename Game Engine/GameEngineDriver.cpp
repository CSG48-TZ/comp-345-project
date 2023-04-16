#include "../Game Engine/GameEngine.h"
#include <windows.h>
#include <iostream>
#include <string>
#include "../Observer/LoggingObserver.h"
using namespace std;


int foo() {
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

int main() {
    cout << "*********************************************************************************\n";
    cout << "*                           Part 3 : MAIN GAME LOOP                             *\n";
    cout << "*********************************************************************************\n\n\n";
    
    cout << "A command file will be used to do the following: \n";
    cout << "- Load a map \n";
    cout << "- Validate a map \n";
    cout << "- Create two players : Maggie and Bob \n\n";
    cout << "- Replay or Quiz the game when the game ends \n";

    GameEngine* game = new GameEngine;
    // Create an observer for every object
    LogObserver* gameEngineObserver = new LogObserver(game->mode);
    cout << "***********Game Start***********\nWelcome to the game!" << endl;
    game->runGame();
    cout << "***********Game Over! Thank you!***********" << endl;

    delete game, gameEngineObserver;
    game, gameEngineObserver = NULL;
    return 0;
}