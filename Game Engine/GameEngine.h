#pragma once
#include <string>
#include <stdexcept>
#include <vector>
#include <sstream>
#include "../Player/Player.h"

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

        // default constructor
        GameEngine();
        // copy constructor
        GameEngine(const GameEngine& engine);
        // assignment operator
        GameEngine& operator=(const GameEngine& engine);
        // stream insertion operator
        friend std::ostream& operator<<(std::ostream& out, const GameEngine& GameEngine);
        // Destructor
        ~GameEngine();

        // To process the command entered in the program console
        bool processCommand(std::string& command);

        // Accessors for private variables
        std::string getCurrentState() const;
        void setCurrentState(std::string& state);

        // Method called during startup of game
        bool startupPhase();

        // Method called during reinforcement phase
        bool reinforcementPhase();

        // Method called during issue orders phase
        bool issueOrdersPhase();

        // Method called during execute orders phase
        bool executeOrdersPhase();

        // Method called for the main game loop
        void mainGameLoop(); 

        vector <Player *> players;
        Map * map;

    private:
        // A private attribute to track current state
        State* currentState;
};