#include "GameEngine.h"
#include <iostream>
#include <string>
using namespace std;

// Implementation of Constructors
GameEngine::GameEngine(){
    currentState = new State(START);
}

// copy constructor
GameEngine::GameEngine(const GameEngine& engine) {
    this->currentState = engine.currentState;
}

// assignment operator
GameEngine& GameEngine::operator=(const GameEngine& engine) {
    this->currentState= engine.currentState;
    return *this;
}

// stream insertion operator
ostream& operator<<(ostream& out, const GameEngine& engine) {
    out << "Current State is " << engine.getCurrentState() << endl;
    return out;
}

// destructor
GameEngine::~GameEngine() {
    delete currentState;
    currentState = NULL;
}

// Implementation of Accessors
void GameEngine::setCurrentState(string& state) {
    if (state == "start") {
        *currentState = State::START;
    }
    else if (state == "maploaded") {
        *currentState = State::MAP_LOADED;
    }
    else if (state == "mapvalidated") {
        *currentState = State::MAP_VALIDATED;
    }
    else if (state == "playersadded") {
        *currentState = State::PLAYERS_ADDED;
    }
    else if (state == "assignreinforcement") {
        *currentState = State::ASSIGN_REINFORCEMENT;
    }
    else if (state == "issueorders") {
        *currentState = State::ISSUE_ORDERS;
    }
    else if (state == "executeorders") {
        *currentState = State::EXECUTE_ORDERS;
    }
    else if (state == "win") {
        *currentState = State::WIN;
    }
    else if (state == "exit program") {
        *currentState = State::END;
    }
}

std::string GameEngine::getCurrentState() const {
    switch (*currentState) {
        case START:
            return "start";
        case MAP_LOADED:
            return "maploaded";
        case MAP_VALIDATED:
            return "mapvalidated";
        case PLAYERS_ADDED:
            return "playersadded";
        case ASSIGN_REINFORCEMENT:
            return "assignreinforcement";
        case ISSUE_ORDERS:
            return "issueorders";
        case EXECUTE_ORDERS:
            return "executeorders";
        case WIN:
            return "win";
        case END:
            return "exit program";
    }
    return "Invalid State";
}

// Implementation of command processing step
// Make the transition based on the input command
// If the command is a valid command, return true
// If the command is invalid, or at least can not be used in the current state, return false
bool GameEngine::processCommand(std::string& command) {
    if (command == "loadmap") {
        if (*currentState == State::START || *currentState == State::MAP_LOADED) {
            *currentState = State::MAP_LOADED;
            return true;
        } else {
            return false;
        }
    } else if (command == "validatemap") {
        if (*currentState == State::MAP_LOADED) {
            *currentState = State::MAP_VALIDATED;
            return true;
        } else {
            return false;
        }
    } else if (command == "addplayer") {
        if (*currentState == State::MAP_VALIDATED || *currentState == State::PLAYERS_ADDED) {
            *currentState = State::PLAYERS_ADDED;
            return true;
        } else {
            return false;
        }
    } else if (command == "assigncountries") {
        if (*currentState == State::PLAYERS_ADDED) {
            *currentState = State::ASSIGN_REINFORCEMENT;
            return true;
        } else {
            return false;
        }
    } else if (command == "issueorder") {
        if (*currentState == State::ASSIGN_REINFORCEMENT || *currentState == State::ISSUE_ORDERS) {
            *currentState = State::ISSUE_ORDERS;
            return true;
        } else {
            return false;
        }
    } else if (command == "endissueorders") {
        if (*currentState == State::ISSUE_ORDERS) {
            *currentState = State::EXECUTE_ORDERS;
            return true;
        } else {
            return false;
        }
    } else if (command == "execorder") {
        if (*currentState == State::EXECUTE_ORDERS) {
            *currentState = State::EXECUTE_ORDERS;
            return true;
        } else {
            return false;
        }
    } else if (command == "endexecorders") {
        if (*currentState == State::EXECUTE_ORDERS) {
            *currentState = State::ASSIGN_REINFORCEMENT;
            return true;
        } else {
            return false;
        }
    } else if (command == "win") {
        if (*currentState == State::EXECUTE_ORDERS) {
            *currentState = State::WIN;
            return true;
        } else {
            return false;
        }
    } else if (command == "play") {
        if (*currentState == State::WIN) {
            *currentState = State::START;
            return true;
        } else {
            return false;
        }
    } else if (command == "end") {
        if (*currentState == State::WIN) {
            *currentState = State::END;
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}
