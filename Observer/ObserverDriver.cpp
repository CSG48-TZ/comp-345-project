#include "LoggingObserver.h"
#include "../CommandProcess/CommandProcessing.h"
#include "../Game Engine/GameEngine.h"
#include "../Orders/Orders.h"


int main() {
    GameEngine* engine = new GameEngine();
    // Create an observer for every object
    LogObserver* gameEngineObserver = new LogObserver(engine);
    LogObserver* processorObserver = new LogObserver(engine->cmdPcs);
    while (engine->getCurrentState() != "assignreinforcement") {
        // Ask for input command
        Command* command = engine->cmdPcs->getCommand();
        LogObserver* commandObserver = new LogObserver(command);
        if (command == NULL) {
            cout << "No command was input." << endl;
            break;
        }
        // Check if the command is valid and save effect
        string currentState = engine->getCurrentState();
        string nextState = engine->cmdPcs->validate(command, currentState);

        engine->transition(nextState);

        // Memory arrangements

        delete commandObserver;
        commandObserver = NULL;
        delete command;
        command = NULL;

        cout << "\nInput any letter to continue..." << endl;
        string ctn;
        getline(cin, ctn);
        cout << endl;
        
    }

    // Memory Arrangement
    delete gameEngineObserver;
    gameEngineObserver = NULL;
    delete processorObserver;
    processorObserver = NULL;
    delete engine;
    engine = NULL;
	return 0;
}
