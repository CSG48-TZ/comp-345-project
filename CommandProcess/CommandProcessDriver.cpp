// CommandProcess.cpp : This file contains the main function of driver 
//

#include <iostream>
#include <sstream>
#include "../Game Engine/GameEngine.h"
#include "CommandProcessing.h"
using namespace std;

int main()
{   
    // Create a game engine to do transition
    GameEngine* engine = new GameEngine();
    while (true) {
        // Ask for input command
        Command* command = engine->cmdPcs->getCommand();
        if (command == NULL) {
            cout << "No command was input." << endl;
            break;
        }
        // Check if the command is valid and save effect
        string currentState = engine->getCurrentState();
        string nextState = engine->cmdPcs->validate(command, currentState);
        cout << "Details of the input command: \n" << *command << endl;

        engine->setCurrentState(nextState);
        delete command;
        command = NULL;
        cout << "\nInput any letter to continue" << endl;
        string ctn;
        cin >> ctn;
    }
    delete engine;
    engine = NULL;
    return 0;
}