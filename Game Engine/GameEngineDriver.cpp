#include "GameEngine.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
    cout << "***********Game Start***********" << endl;
    GameEngine game;
    string command;
    while (true) {
        // Ask for input command
        cout << "Please Enter command: ";
        cin >> command;
        if (!game.processCommand(command)) {
            cout << "Error Message: Invalid command" << endl;
            break;
        } else{
            cout << "Valid Command! Current State is " << game.getCurrentState() <<endl;
            if (game.getCurrentState() == GameEngine::State::END){
                break;
            } else if (game.getCurrentState() == GameEngine::State::WIN) {
                cout << "Game Win! Please choose the next step by typing \"play\" or \"end\"..." << endl;
            }
            cout << endl;
        }

    }
    cout << "***********Game Over! Thank you!***********" << endl;
    return 0;
}
