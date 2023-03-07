// CommandProcess.cpp : This file contains the main function of driver 
//

#include <iostream>
#include <sstream>
#include "../Game Engine/GameEngine.h"
#include "CommandProcessing.h"
using namespace std;

int main()
{
    GameEngine engine = GameEngine();

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
        CommandProcessor cmdPcs = CommandProcessor();
        while (true) {
            // Ask for input command
            cout << "\nPlease Enter command or enter \"E\" to exit: ";
            Command* command = cmdPcs.getCommand();
            if (command == NULL) {
                cout << "No command was input." << endl;
            }
            // Check if the command is valid and print respective messages
            string currentState = engine.getCurrentState();
            string nextState = cmdPcs.validate(command, currentState);
            cout << *command << endl;
            engine.setCurrentState(nextState);
        }

    }
    else if (arg == "-file" && result.size() == 2) {
        string fileName = result[1];
        cout << "\nStart to read commands from " << fileName << endl;
        FileCommandProcessorAdapter filePcs = FileCommandProcessorAdapter(fileName);
        while (true) {
            Command* command = filePcs.getCommand();
            if (command == NULL) {
                cout << "All commands have been read." << endl;
                break;
            }
            // Check if the command is valid and print respective messages
            string currentState = engine.getCurrentState();
            string nextState = filePcs.validate(command, currentState);
            cout << "\nSuccessfully Read: \n" <<  * command << endl;
            engine.setCurrentState(nextState);
            cout << "\n Input any letter to continue" << endl;
            string ctn;
            cin >> ctn;
        }
    }
    else {
        cout << "Invalid";
    }
    return 0;
}