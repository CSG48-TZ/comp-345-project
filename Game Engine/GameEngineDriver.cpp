#include "GameEngine.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
    cout << "***********Game Start***********\nWelcome to the game!" << endl;
    GameEngine* game = new GameEngine;
    string command;
    cout << "Initial State is " << game->getCurrentState() << endl;
    while (true) {
        // Ask for input command
        cout << "\nPlease Enter command or input 'E' to exit the game: ";
        cin >> command;
        // Manually exit
        if (command == "E") {
            break;
        }
        // Check if the command is valid and print respective messages
        if (!game->processCommand(command)) {
            cout << "Error Message: Invalid command. Please try again or input 'E' to exit the game." << endl;
        } else{
            cout << "Valid Command! " << *game << endl;
            if (game->getCurrentState() == "End") {
                break;
            } else if (game->getCurrentState() == "Win") {
                cout << "Game Win! Please choose the next step by typing \"play\" or \"end\"..." << endl;
            }
            cout << endl;
        }

    }
    cout << "***********Game Over! Thank you!***********" << endl;
    delete game;
    return 0;
}
