#pragma once
#include <string>
#include <stdexcept>
#include <vector>

class GameEngine{
    public:
        // Define a enum data member to present the all the states of the game engine
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

        // Constructor
        GameEngine();
        ~GameEngine();

        // To process the command entered in the program console
        bool processCommand(std::string& command);

        // Accessors for private variables
        State getCurrentState();
        void setCurrentState(State newState);

    private:
        // A private attribute to track current state
        State currentState;
};