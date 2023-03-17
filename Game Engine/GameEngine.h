#pragma once
#include <string>
#include <stdexcept>
#include <vector>
#include "../CommandProcess/CommandProcessing.h"
#include "../Map/Map.h"
#include "../Cards/Cards.h"

class GameEngine{
    public:
        // Define a enum data member to present the all the states of the game engine
        const enum State { 
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


        CommandProcessor* cmdPcs;

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

        // Accessor and Mutator for private variables
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



    private:
        // A private attribute to track current state
        State* currentState;
        Map* map;
        vector<Player*> players;
        void initializeCommandProcessor();
};

