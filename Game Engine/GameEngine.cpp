#include "GameEngine.h"
#include <iostream>
#include <string>
using namespace std;

// Implementation of Constructors
GameEngine::GameEngine(){
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
    this->currentState= engine.currentState;
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
void GameEngine::setCurrentState(State state) {
    *currentState = state;
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

// Implementation of the startup phase
// Returns true if startup completed without any issues
// Returns false if an error occurs
bool GameEngine::startupPhase() {
    // TODO - replace all cin instances with commandProcessor methods
    // TODO - replace with a call to loadmap <filename>
    cout << "Please enter the name of the map file you wish to use: ";
    string line;
    string command = "";

    cin >> line;

    stringstream stream(line);

    string filename;

    stream >> command >> filename;
    Maploader maploader(filename);

    Map map = maploader.load();

    setCurrentState(MAP_LOADED);

    // TODO - replace with a call to validatemap command

    if (map.validate()) {
        cout << "Map validated successfully" << endl;
        setCurrentState(MAP_VALIDATED);
    }
    else {
        cout << "Map is not valid. Terminating program" << endl;
        exit(0);
    }

    //

    int numPlayers = 0;
    vector<Player*> players;

    while (numPlayers < 2 || command != "gamestart") {
        if (numPlayers == 6) {
            cout << "A maximum of 6 players are allowed in this game" << endl;
            cout << "Starting game" << endl;
            break;
        }
        else if (numPlayers < 2) {
            cout << "At least two players are necessary to start the game, please add more players" << endl;
            cin >> command;
            if (command == "addplayer") {
                numPlayers++;
                Player* player = new Player();
                players.push_back(player);
            }
        }
        else if (command == "addplayer") {
            numPlayers++;
            Player* player = new Player();
            players.push_back(player);
        }
    }

    setCurrentState(PLAYERS_ADDED);

    while (command != "gamestart") {
        cin >> command;
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

}

bool GameEngine::reinforcementPhase() {
    int reinforcementAmount;
    int numPlayers = players.size();
    int continentBonus = 0;
    // loop for each player
    cout << "Reinforcement Phase \"";
    for (int i = 0; i < numPlayers; i++) {
        reinforcementAmount = map->territories.size() / 3;

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

    // setCurrentState("issueorders");
    return true;
}

bool GameEngine::issueOrdersPhase() {
    return false;
}

bool GameEngine::executeOrdersPhase() {
    return false;
}

void GameEngine::mainGameLoop() {
}


