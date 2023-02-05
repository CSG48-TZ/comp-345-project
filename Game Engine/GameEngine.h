#pragma once
#include <string>
#include <stdexcept>
#include <vector>

class GameEngine{
    public:
        // Define a enum data member to present the all the states of the game engine
        enum State { 
            START, 
            MAP_LOADED, 
            MAP_VALIDATED, 
            PLAYERS_ADDED,
            ASSIGN_REINFORCEMENT,
            ISSUE_ORDERS,
            EXECUTE_ORDERS,
            WIN,
            END
        };

        // Constructor
        GameEngine();
        ~GameEngine();

        // To process the command entered in the program console
        bool processCommand(std::string& command);

        // Accessors for private variables
        std::string getCurrentState();
        void setCurrentState(State newState);

    private:
        // A private attribute to track current state
        State currentState;
};