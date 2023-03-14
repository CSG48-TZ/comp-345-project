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

    // Read command line argument to determine the source of commands
    cout << "Please enter a command line argument that enables the user to choose between accepting the "
        << "commands from the console(-console) or from a file(-file <filename>)." << endl;
    string cla;
    getline(cin, cla);
    istringstream iss(cla);
    vector<string> result;
    string word;
    while (getline(iss, word, ' ')) {
        result.push_back(word);
    }
    string arg = result[0];
    if (arg == "-console") {
        // If the user wants to read from console, create a command processor to read command and save effect
        CommandProcessor* cmdPcs = new CommandProcessor();
        while (true) {
            // Ask for input command
            cout << "\nPlease Enter command or enter \"E\" to exit: ";
            Command* command = cmdPcs->getCommand();
            if (command == NULL) {
                cout << "No command was input." << endl;
                continue;
            }
            // Check if the command is valid and save effect
            string currentState = engine->getCurrentState();
            string nextState = cmdPcs->validate(command, currentState);
            cout << "Details of the input command: " << * command << endl;
            engine->setCurrentState(nextState);
            delete command;
            command = NULL;
        }
        delete cmdPcs;
        cmdPcs = NULL;
    }
    else if (arg == "-file" && result.size() == 2) {
        // If the user wants to read from a file, create a file processor to read command and save effect
        string fileName = result[1];
        cout << "\nStart to read commands from " << fileName << endl;
        FileCommandProcessorAdapter* filePcs = new FileCommandProcessorAdapter(fileName);
        while (true) {
            Command* command = filePcs->getCommand();
            if (command == NULL) {
                cout << "All commands have been read." << endl;
                break;
            }
            // Check if the command is valid and save effect
            string currentState = engine->getCurrentState();
            string nextState = filePcs->validate(command, currentState);
            cout << "\nSuccessfully Read: \n" <<  * command << endl;
            engine->setCurrentState(nextState);
            cout << "\n Input any letter to continue" << endl;
            string ctn;
            cin >> ctn;
            delete command;
            command = NULL;
        }
        delete filePcs;
        filePcs = NULL;
    }
    else {
        cout << "Invalid";
    }
    delete engine;
    engine = NULL;
    return 0;
}