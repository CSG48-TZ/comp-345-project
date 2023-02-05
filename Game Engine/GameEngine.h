#pragma once
#include <string>
#include <stdexcept>
#include <vector>

class GameEngine
{
public:
    enum State { 
        START = 0, 
        MAP_LOADED = 1, 
        MAP_VALIDATED = 2, 
        PLAYERS_ADDED = 3,
        ASSIGN_REINFORCEMENT = 4,
        ISSUE_ORDERS = 5,
        EXECUTE_ORDERS = 6,
        WIN = 7,
        END = 8
    };

    GameEngine();
    ~GameEngine();
    bool processCommand(std::string& command);
    State getCurrentState();
    void setCurrentState(State newState);

private:
    State currentState;
};
