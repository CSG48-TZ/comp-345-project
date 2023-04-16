#pragma once
#include <string>
#include <stdexcept>
#include <vector>
#include "../CommandProcess/CommandProcessing.h"
#include "../Map/Map.h"
#include "../Cards/Cards.h"
#include "../Observer/LoggingObserver.h"


class TournamentMode : public Iloggable, public Subject {
public:
    TournamentMode();
    ~TournamentMode();
    TournamentMode(TournamentMode* other);
    TournamentMode& operator=(const TournamentMode& mode);
    // stream insertion operator
    friend std::ostream& operator<<(std::ostream& out, const TournamentMode& mode);

    int tourGameNum;
    int tourMaxTurn;
    vector<string> tourMaps;
    vector<string> tourStrategies;
    vector<string> winnerStrategies;

    string stringToLog();
    void generateLogFile();
};

class GameEngine : public Iloggable, public Subject{
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


        CommandProcessor* cmdPcs;
        TournamentMode* mode;

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
        void transition(std::string& state);

        // Method called during startup of game
        bool startupPhase();

        // Method called during reinforcement phase
        void reinforcementPhase();

        // Method called during issue orders phase
        void issueOrdersPhase();

        // Method called during execute orders phase
        void executeOrdersPhase();

        // Method called for the main game loop
        void mainGameLoop();
        string stringToLog();

        void tournamentModeStartUp(int mapID);
        void runGame();

    private:
        // A private attribute to track current state
        State* currentState;
        Map* map;
        vector<Player*> players;

        void initializeCommandProcessor();
        void initializeTourMode(Command* command);
};
