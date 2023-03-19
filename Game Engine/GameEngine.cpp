#include "GameEngine.h"
#include <iostream>
#include <string>
using namespace std;

// Implementation of Constructors
GameEngine::GameEngine() {
    currentState = new State(START);
    this->initializeCommandProcessor();
}

// copy constructor
GameEngine::GameEngine(const GameEngine& engine) {
    this->currentState = engine.currentState;
    this->cmdPcs = engine.cmdPcs;
}

// assignment operator
GameEngine& GameEngine::operator=(const GameEngine& engine) {
    this->currentState = engine.currentState;
    this->cmdPcs = engine.cmdPcs;
    return *this;
}

// stream insertion operator
ostream& operator<<(ostream& out, const GameEngine& engine) {
    out << "Current State is " << engine.getCurrentState() << endl;
    out << *(engine.cmdPcs) << endl;
    return out;
}

// destructor
GameEngine::~GameEngine() {
    delete currentState;
    delete cmdPcs;
    delete map;
    currentState = NULL;
    cmdPcs = NULL;
    map = NULL;
    for (int i = 0; i < players.size(); i++) {
        delete players[i];
        players[i] = NULL;
    }
    players.clear();
}

// Implementation of Accessors
void GameEngine::transition(string& state) {
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
    notify(this);
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

// Initialize the command processor inside constructor
void GameEngine::initializeCommandProcessor() {
    cout << "Please enter a command line argument that enables the user to choose between accepting the "
        << "commands from the console(-console) or from a file(-file <filename>)." << endl;
    string cla;
    getline(cin, cla);
    istringstream iss(cla);
    vector<string> result;
    string word;
    while (getline(iss, word, ' ')) {
        result.push_back(word);
    }
    string arg = result[0];
    while (true) {
        if (arg == "-console") {
            // If the user wants to read from console, create a command processor to read command and to save effect
            this->cmdPcs = new CommandProcessor();
            break;
        }
        else if (arg == "-file" && result.size() == 2) {
            // If the user wants to read from a file, create a file processor to read command and to save effect
            string fileName = result[1];
            cout << "\nStart to read commands from " << fileName << endl;
            FileLineReader* reader = new FileLineReader(fileName);
            this->cmdPcs = new FileCommandProcessorAdapter(reader);
            break;
        }
        else {
            cout << "Invalid Choice. Please select the source of commands again." << endl;
        }
    }
}

// Override the method in iloggable to generate the output message
string GameEngine::stringToLog() {
    string message = "Game Engine New State: " + this->getCurrentState() + "; ";
    return message;
}

// Implementation of the startup phase
// Returns true if startup completed without any issues
// Returns false if an error occurs
bool GameEngine::startupPhase() {
    while (*currentState != State::ASSIGN_REINFORCEMENT) {
        // Ask for input command
        Command* command = this->cmdPcs->getCommand();
        if (command == NULL) {
            cout << "No command was input." << endl;
            exit(0);
        }
        // Check if the command is valid and save effect
        string currentState = this->getCurrentState();
        string nextState = cmdPcs->validate(command, currentState);
        cout << "Details of the input command: \n" << *command << endl;

        // Do corresponding operation if the command is valid
        if (nextState != "") {
            string commandName = command->getCommandName();
            istringstream iss(commandName);
            vector<string> result;
            string word;
            while (getline(iss, word, ' ')) {
                result.push_back(word);
            }
            string behavior = result[0];

            if (behavior == "loadmap") {
                cout << "Please enter the name of the map file you wish to use: ";
                string line;
                string command = "";

                cin >> line;

                stringstream stream(line);

                string filename;

                stream >> command >> filename;
                Maploader maploader(filename);

                this->map = new Map(maploader.load());
            }
            else if (behavior == "validatemap") {
                if (this->map->validate()) {
                    cout << "Map validated successfully" << endl;
                }
                else {
                    cout << "Map is not valid. Terminating program" << endl;
                    exit(0);
                }
            }
            else if (behavior == "gamestart") {
                if (this->players.size() < 2) {
                    cout << "At least two players are necessary to start the game, please add more players" << endl;
                }
                else {
                    // TODO: Finish the game start part
                }
            }
            else if (behavior == "addplayer") {
                int num = (int)this->players.size();
                if (num == 6) {
                    cout << "A maximum of 6 players are allowed in this game" << endl;
                    cout << "Please input command \"gamestart\" to start the game now." << endl;
                }
                else {
                    Player* player = new Player();
                    players.push_back(player);
                }
            }

        }
        this->transition(nextState);
        delete command;
        command = NULL;
        cout << "\nInput any letter to continue" << endl;
        string ctn;
        getline(cin, ctn);
        cout << endl;
    }

    // TODO - allocate territories fairly to players


    vector<Player*> orderedPlayers; // TODO - Possibly change this to a pointer to a vector of players for usage outside this method

    while (players.size() != 0) {
        int index = rand() % players.size();
        orderedPlayers.push_back(players[index]);
    }

    cout << "Determined the order of play" << endl;
    for (int i = 0; i < orderedPlayers.size(); i++) {
        cout << i << ": " << orderedPlayers[i]->playerID << endl;
    }

    for (int i = 0; i < orderedPlayers.size(); i++) {
        orderedPlayers[i]->addArmies(50);
    }

    cout << "Added 50 armies to each player's reinforcement pool" << endl;

    Deck deck{};
    for (int i = 0; i < orderedPlayers.size(); i++) {
        deck.draw(orderedPlayers[i]->getHand());
        deck.draw(orderedPlayers[i]->getHand());
    }

    cout << "Drew two cards from the deck for each player" << endl;

    setCurrentState(ISSUE_ORDERS);

    return true;

}

void GameEngine::reinforcementPhase() {
    int reinforcementAmount;
    int numPlayers = (int)players.size();
    int continentBonus = 0;
    // loop for each player
    cout << "Reinforcement Phase " << endl;
    for (int i = 0; i < numPlayers; i++) {
        reinforcementAmount = (int)map->territories.size() / 3;

        for (int j = 0; j < map->continents.size(); j++) {
            for (int k = 0; k < map->continents[j].size(); k++) {
                // TODO: check if every territory in the continent is in the player territory list

                // boolean value to see if the current territory in the continent is in the list of territories of the current player
                bool present = std::find(begin(players[i]->territories), end(players[i]->territories), map->continents[j][k]) != end(players[i]->territories);

                // if the current territory of the continent is not in the player's list of territories break the loop
                if (!present) {
                    break;
                }

                // check if we are at last index to add continent bonus 
                if (present && k == map->continents[j].size() - 1) {
                    // TODO: Add continent bonus
                    // adds continent bonus to current reinforcement amount
                    reinforcementAmount += continentBonus;
                }
            }
        }

        // Make sure the player gets a minimum of 3 reinforcement troops
        if (reinforcementAmount < 3) {
            reinforcementAmount = 3;
        }
        cout << "Player: " << players[i]->getName() << " has " << reinforcementAmount << " troops to reinforce \"";
        players[i]->addArmies(reinforcementAmount);
    }
    // set state to issue orders
}

/**
 * Players issue orders and place them in their order list
 */
void GameEngine::issueOrdersPhase() {
    // inform current game play phrase
    cout << "Issue Orders Phase " << endl;
    // loop around through all the players and issue their orders to the order list
    std::vector<Player*>::iterator it;
    for (it = players.begin(); it != players.end(); it++) {
        Player* player = *it;
    }
}

/**
 * Execute all deploy order before other orders, then use
 * round-robin fashion to execute the rest of the orders
 */
void GameEngine::executeOrdersPhase() {

    bool allOrderExecuted = false;
    int orderListLength = 0;  // length after executing deploy
    // inform current game play phrase
    cout << "Order Execution Phase " << endl;
    //execute deploy order first
    for (auto currPlayer : players) {
        OrdersList* currOrderList = currPlayer->getOrderList();
        // loop through the list to find deploy order
        for (Orders* order : currOrderList->getCurrentOrdersList()) {
            if (order->getCurrentOrder() == "Deploy") {
                order->validate();
                order->execute();
                currPlayer->getOrderList()->removeOrder(order);
            }
        }

        // TODO execute other orders
    }
}

/**
 * Continue the loop(reinforcement, issue orders, execution) until
 * a player owns all the territories, then the winner is announced.
 * If any player owns < 1 territory, the player got removed from the game
 */
void GameEngine::mainGameLoop() {

    bool gameIsFinished = false;
    int gameRound = 0;
    int numOfAllTerritories = 0;

    if (map != nullptr) {
        numOfAllTerritories = (int)map->territories.size();
    }
    while (!gameIsFinished) {

        for (auto& player : players) {
            // if a player owns all the territories, announce the player and end the game
            if (player->territories.size() == numOfAllTerritories) {
                cout << "The player is " << player->getName() << "! Congratulations!" << endl;
                //exit the loop
                gameIsFinished = true;
            }

            // if a player owns 0 territory, remove from the game
            if (player->territories.empty()) {
                // TODO remove the player and reduce player list size
                cout << player->getName() << " is removed from the game for having 0 territory" << endl;
            }
        }

        // reinforcement phase: skip for the first round
        if (gameRound > 0) {
            reinforcementPhase();
        }
        // order issuing phase
        issueOrdersPhase();
        // order execution phase
        executeOrdersPhase();
        gameRound++;
    }
}


