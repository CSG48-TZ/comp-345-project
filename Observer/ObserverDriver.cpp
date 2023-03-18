#include "LoggingObserver.h"
#include "../CommandProcess/CommandProcessing.h"
#include "../Game Engine/GameEngine.h"

int main() {
    GameEngine* engine = new GameEngine();
    while (true) {
        // Ask for input command
        LogObserver* processorObserver = new LogObserver(engine->cmdPcs);
        Command* command = engine->cmdPcs->getCommand();
        LogObserver* commandObserver = new LogObserver(command);
        if (command == NULL) {
            cout << "No command was input." << endl;
            break;
        }
        // Check if the command is valid and save effect
        string currentState = engine->getCurrentState();
        string nextState = engine->cmdPcs->validate(command, currentState);

        engine->setCurrentState(nextState);
        delete command;
        command = NULL;
        cout << "\nInput any letter to continue" << endl;
        string ctn;
        getline(cin, ctn);
        cout << endl;
    }
    delete engine;
    engine = NULL;
	return 0;
}