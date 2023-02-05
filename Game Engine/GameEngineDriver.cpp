#include "GameEngine.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    GameEngine game;
    string command;
    while (true) {
        cout << "Please Enter command: ";
        cin >> command;
        if (!game.processCommand(command)) {
            cout << "Error Message: Invalid command" << endl;
            break;
        } else{
            cout << "Valid Command! Current State is " << game.getCurrentState() <<endl;
            if (game.getCurrentState() == GameEngine::State::END){
                cout << "Game Over! Thank you!" << endl;
                break;
            } else if (game.getCurrentState() == GameEngine::State::WIN) {
                cout << "Game Win! Please choose the next step by typing \"play\" or \"end\"..." << endl;
            }
            cout << endl;
        }

    }
    return 0;
}
