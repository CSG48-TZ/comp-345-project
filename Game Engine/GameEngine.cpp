#include "GameEngine.h"
#include "Map.h"
#include "Cards.h"
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


// Implementation of the startup phase
// Returns true if startup completed without any issues
// Returns false if an error occurs
bool GameEngine::startupPhase() {
    // TODO - replace all cin instances with commandProcessor methods
    // TODO - replace with a call to loadmap <filename>
    cout << "Please enter the name of the map file you wish to use: ";
    string line;
    string command = "";

    cin >> line ;

    stringstream stream(line);

    string filename;

    stream >> command >> filename;
    Maploader maploader(filename);

    Map map = maploader.load();

    setCurrentState(MAP_LOADED);

    // TODO - replace with a call to validatemap command

    if(map.validate()){
        cout << "Map validated successfully" << endl;
        setCurrentState(MAP_VALIDATED);
    }else{
        cout << "Map is not valid. Terminating program" << endl;
        exit(0);
    }

    //

    int numPlayers = 0;
    vector<Player *> players;

    while(numPlayers < 2 || command != "gamestart"){
        if(numPlayers == 6) {
            cout << "A maximum of 6 players are allowed in this game" << endl;
            cout << "Starting game" << endl;
            break;
        } else if(numPlayers < 2){
            cout << "At least two players are necessary to start the game, please add more players" << endl;
            cin >> command;
            if(command == "addplayer"){
                numPlayers ++;
                Player * player = new Player();
                players.push_back(player);
            }
        } else if( command == "addplayer"){
            numPlayers ++;
            Player * player = new Player();
            players.push_back(player);
        }
    }

    setCurrentState(PLAYERS_ADDED);

    while(command != "gamestart") {
        cin >> command;
    }

    // TODO - allocate territories fairly to players


    vector<Player *> orderedPlayers; // TODO - Possibly change this to a pointer to a vector of players for usage outside this method

    while(players.size()!= 0){
        int index = rand()%players.size();
        orderedPlayers.push_back(players[index]);
    }

    cout << "Determined the order of play" << endl;
    for(int i = 0 ; i < orderedPlayers.size(); i ++){
        cout << i << ": " << orderedPlayers[i]->playerID << endl;
    }

    for(int i = 0; i < orderedPlayers.size(); i ++){
        orderedPlayers[i]->addArmies(50);
    }

    cout << "Added 50 armies to each player's reinforcement pool" << endl;

    Deck deck{};
    for(int i = 0 ; i < orderedPlayers.size(); i ++){
        deck.draw(orderedPlayers[i]->getHand());
        deck.draw(orderedPlayers[i]->getHand());
    }

    cout << "Drew two cards from the deck for each player" << endl;

    setCurrentState(ISSUE_ORDERS);

}

bool GameEngine::reinforcementPhase(){
    int reinforcementAmount;
    int numPlayers = players.size();
    int continentBonus;
    // loop for each player
    cout << "Reinforcement Phase \"";
    for (int i = 0; i< numPlayers;i++){
        
        reinforcementAmount = map->territories.size()/3;
       
        for (int j = 0; j < map->continents.size(); j++){
            for (int k = 0; k < map->continents[j].size(); k++){ 
                // TODO: check if every territory in the continent is in the player territory list
                
                // boolean value to see if the current territory in the continent is in the list of territories of the current player
                bool present = std::find(begin(players[i]->territories), end(players[i]->territories), map->continents[j][k]) != end(players[i]->territories);
                
                // if the current territory of the continent is not in the player's list of territories break the loop
                if (!present){
                    break;
                }

                // check if we are at last index to add continent bonus 
                if (present && k == map->continents[j].size()-1) {
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
}

/**
 * Players issue orders and place them in their order list
 */
void GameEngine::issueOrdersPhase() {
    
    // inform current game play phrase
    cout << "Issue Orders Phase " << endl;
    
    // loop around through all the players and issue their orders to the order list
    std::vector<Player*>::iterator it;
    for(it = players.begin(); it != players.end(); it++){
        Player* player = *it;
        // TODO need to specify the parameters
        player->issueOrder();
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
    
    if(map != nullptr){
        numOfAllTerritories = map->territories.size();
    }
    while(!gameIsFinished){
               
        for (auto & player : players) {
            // if a player owns all the territories, announce the player and end the game
            if(player->territories.size() == numOfAllTerritories){
                cout << "The player is " << player->getName() << "! Congratulations!" << endl;
                //exit the loop
                gameIsFinished = true;
            }
            
            // if a player owns 0 territory, remove from the game
            if(player->territories.empty()){
                // TODO remove the player and reduce player list size
                cout << player->getName() << " is removed from the game for having 0 territory" << endl;
            }
        }
        
        // reinforcement phase: skip for the first round
        if(gameRound > 0){
            reinforcementPhase();
        }
        // order issuing phase
        issueOrdersPhase();
        // order execution phase
        executeOrdersPhase();
        gameRound++;
    }
}


int main() {
    GameEngine *g = new GameEngine();
    Player * p1 = new Player();
    Player * p2 = new Player();
    g->reinforcementPhase();
}
