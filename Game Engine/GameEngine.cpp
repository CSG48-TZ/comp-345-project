#include "GameEngine.h"

GameEngine::GameEngine()
    : currentState(State::START){}

GameEngine::~GameEngine(){}

void GameEngine::setCurrentState(GameEngine::State newState) {
    currentState = newState;
}

GameEngine::State GameEngine::getCurrentState() {
    return currentState;
}

bool GameEngine::processCommand(std::string& command) {
    if (command == "loadmap") {
        if (currentState == State::START || currentState == State::MAP_LOADED) {
            currentState = State::MAP_LOADED;
            return true;
        } else {
            return false;
        }
    } else if (command == "validatemap") {
        if (currentState == State::MAP_LOADED) {
            currentState = State::MAP_VALIDATED;
            return true;
        } else {
            return false;
        }
    } else if (command == "addplayer") {
        if (currentState == State::MAP_LOADED || currentState == State::PLAYERS_ADDED) {
            currentState = State::PLAYERS_ADDED;
            return true;
        } else {
            return false;
        }
    } else if (command == "assigncountries") {
        if (currentState == State::PLAYERS_ADDED) {
            currentState = State::ASSIGN_REINFORCEMENT;
            return true;
        } else {
            return false;
        }
    } else if (command == "issueorders") {
        if (currentState == State::ASSIGN_REINFORCEMENT || currentState == State::ISSUE_ORDERS) {
            currentState = State::ISSUE_ORDERS;
            return true;
        } else {
            return false;
        }
    } else if (command == "endissueorders") {
        if (currentState == State::ISSUE_ORDERS) {
            currentState = State::EXECUTE_ORDERS;
            return true;
        } else {
            return false;
        }
    } else if (command == "execorder") {
        if (currentState == State::EXECUTE_ORDERS) {
            currentState = State::EXECUTE_ORDERS;
            return true;
        } else {
            return false;
        }
    } else if (command == "endexecorders") {
        if (currentState == State::EXECUTE_ORDERS) {
            currentState = State::ASSIGN_REINFORCEMENT;
            return true;
        } else {
            return false;
        }
    } else if (command == "win") {
        if (currentState == State::EXECUTE_ORDERS) {
            currentState = State::WIN;
            return true;
        } else {
            return false;
        }
    } else if (command == "play") {
        if (currentState == State::WIN) {
            currentState = State::START;
            return true;
        } else {
            return false;
        }
    } else if (command == "end") {
        if (currentState == State::WIN) {
            currentState = State::END;
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}
