#include "GameEngine.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
    cout << "***********Game Start***********\nWelcome to the game!" << endl;
    GameEngine game;
    string command;
    cout << "Initial State is " << game.getCurrentState() << endl;
    while (true) {
        // Ask for input command
        cout << "\nPlease Enter command: ";
        cin >> command;
        if (!game.processCommand(command)) {
            cout << "Error Message: Invalid command" << endl;
            break;
        } else{
            cout << "Valid Command! Current State is " << game.getCurrentState() << endl;
            if (game.getCurrentState() == "End") {
                break;
            } else if (game.getCurrentState() == "Win") {
                cout << "Game Win! Please choose the next step by typing \"play\" or \"end\"..." << endl;
            }
            cout << endl;
        }

    }
    cout << "***********Game Over! Thank you!***********" << endl;
    return 0;
}
