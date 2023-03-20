#include "../Game Engine/GameEngine.h"
#include <iostream>
#include <string>

// Implementation of Constructors
GameEngine::GameEngine() {
    currentState = new State(START);
    this->initializeCommandProcessor();
    this->map = NULL;
}

// copy constructor
GameEngine::GameEngine(const GameEngine& engine) {
    this->currentState = engine.currentState;
    this->cmdPcs = engine.cmdPcs;
    this->map = engine.map;
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
    cout << "State transitioned to: " << state << endl;
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
    cout << "\nPlease enter a command line argument that enables the user to choose between accepting the "
        << "commands from the console(-console) or from a file(-file <filename>): ";
    while (true) {
        string cla;
        getline(cin, cla);
        istringstream iss(cla);
        vector<string> result;
        string word;
        while (getline(iss, word, ' ')) {
            result.push_back(word);
        }
        string arg = result[0];
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
    int playersID = 0;
    while (*currentState != State::ASSIGN_REINFORCEMENT) {
        // Ask for input command
        Command* command = this->cmdPcs->getCommand();
        if (command == NULL) {
            cout << "No command was input." << endl;
            exit(0);
            return false;
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

            if (behavior == "loadmap" && result.size() == 2) {
                string filename = result[1];
                Maploader maploader(filename);
                this->map = maploader.load();
                cout << "Map" << filename << " has been loaded" << endl;
            }
            else if (behavior == "validatemap") {
                if (this->map->validate()) {
                    cout << "Map validated successfully" << endl;
                }
                else {
                    cout << "Map is not valid. Please re-input the command to load a new map" << endl;
                    nextState = "start";
                    this->transition(nextState);
                    continue;
                }
            }
            else if (behavior == "gamestart") {
                if (this->players.size() < 2) {
                    cout << "At least two players are necessary to start the game, please add more players" << endl;
                    continue;
                }
                else {

                    // Allocates one territory to each player. Each territory allocated are equidistant from each other
                    int numTerritories = (int)this->map->territories.size();
                    int gap = numTerritories / (int)players.size();
                    int playersIndex = 0;

                    for(int i = 0; i < numTerritories; i ++){ // Iterates through all the territories
                        players[playersIndex % players.size()]->addOwnedTerritory(this->map->territories.at(i));
                        playersIndex ++;
                    }

                    // Randomizes the order of players
                    vector<Player*> orderedPlayers;
                    while (players.size() != 0) {
                        int index = rand() % players.size();
                        orderedPlayers.push_back(players[index]);
                        players.erase(players.begin() + index);
                    }

                    // Assigns orderedPlayers vector to GameEngine object's players member
                    this->players = orderedPlayers;

                    cout << "Determined the order of play is shown below: " << endl << endl;
                    for (int i = 0; i < orderedPlayers.size(); i++) {

                        cout << "Player #" << i + 1 << " with ID:" << orderedPlayers[i]->playerID << " and name: " << orderedPlayers[i]->pName << endl;

                    }


                    // Adds 50 armies to each player's reinforcement pool
                    for (int i = 0; i < orderedPlayers.size(); i++) {
                        orderedPlayers[i]->addArmies(50);
                    }

                    cout << "\nAdded 50 armies to each player's reinforcement pool..." << endl << endl;

                    // Draws two cards from the deck for each player
                    Deck deck{};
                    for (int i = 0; i < orderedPlayers.size(); i++) {
                        deck.draw(orderedPlayers[i]->getHand());
                        deck.draw(orderedPlayers[i]->getHand());
                    }

                    cout << "\nDrew two cards from the deck for each player..." << endl << endl;

                    for (int i = 0; i < orderedPlayers.size(); i++) {
                        cout << "Player #" << i + 1 << " with ID:" << orderedPlayers[i]->playerID << " and name: " << orderedPlayers[i]->pName << " has this hand:" << endl;
                        orderedPlayers[i]->getHand()->showHand();
                        cout << "\n\n";
                    }
                }
            }
            else if (behavior == "addplayer") {
                int num = (int)this->players.size();
                if (num == 6) {
                    cout << "A maximum of 6 players are allowed in this game" << endl;
                    cout << "Please input command \"gamestart\" to start the game now." << endl;
                    continue;
                }
                else {

                    Player* player = new Player(result[1],playersID);
                    players.push_back(player);
                    cout << "Added player: " << result[1] << " with id: " << playersID << endl;
                    playersID++;
                }
            }
            else {
                cout << "Invalid Command. Please input another command." << endl;
                continue;
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
    return true;

}

void GameEngine::reinforcementPhase() {
    int reinforcementAmount;
    int numPlayers = (int)players.size();
    int continentBonus = 0;
    // loop for each player
    cout << "Reinforcement Phase " << endl;
    for (int i = 0; i < numPlayers; i++) {
        reinforcementAmount = (int)players.at(i)->territories.size() / 3;

        for (int j = 0; j < map->continents.size(); j++) {
            for (int k = 0; k < map->continents[j].size(); k++) {
                // TO check : check if every territory in the continent is in the player territory list

                // boolean value to see if the current territory in the continent is in the list of territories of the current player
                bool present = std::find(begin(players[i]->territories), end(players[i]->territories), map->continents[j][k]) != end(players[i]->territories);

                // if the current territory of the continent is not in the player's list of territories break the loop
                if (!present) {
                    break;
                }

                // check if we are at last index to add continent bonus 
                if (present && k == map->continents[j].size() - 1) {
                    // adds continent bonus to current reinforcement amount
                    reinforcementAmount += map->bonuses[j];
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
    string nextstate = "issueorders";
    this->transition(nextstate);
}

/**
 * Players issue orders and place them in their order list
 */
void GameEngine::issueOrdersPhase() {
    // inform current game play phrase
    cout << "Issue Orders Phase " << endl;
    Player* player;
    Player* player2;
    int territoryID = 0;
    std::vector<Player*>::iterator it;
    std::vector<Player*>::iterator it2;

    cout << "\nISSUING ORDERS\n\nPlayers will now modify their attack and defend lists...\n\n";
    for (it = players.begin(); it != players.end(); it++) {
        player = *it;
        cout << "Player " << player->pName << " have the folloring territories: \n";
        for (Territory* terr : player->territories) {
            cout << "- " << terr->name << " with ID: " << terr->id << " and has " << terr->numArmies << " armies in the territory.\n";
        }
        cout << "\n\n";
    }


    // loop around through all the players and issue their orders to the order list

    for (it = players.begin(); it != players.end(); it++) {
        player = *it;
        territoryID = 0;
        while (territoryID != -1) {
            cout << "\nPlayer " + player->pName << ", specify a territory ID to attack, -1 when you are done: ";
            cin >> territoryID; //TODO edge cases like hello input or !@#$!@$QW you know
            if (territoryID != -1) {
                for (Territory* terr : map->territories) {
                    if (territoryID == terr->id) {
                        if(terr->owner == player) {
                            cout << "\nCannot add territory to list: Player " << terr->owner->pName << " owns the territory - " << terr->id << ".\n";
                        }
                        else if(terr->owner != NULL) {
                            player->addToAttack(terr);
                        }
                        else {
                            cout << "\nCannot add territory to list: Nobody owns the territory - " << terr->id << ".\n";
                        }
                        break;
                    }
                }
            }
        }
        territoryID = 0;
        while (territoryID != -1) {
            cout << "\nPlayer " + player->pName << ", specify a territory ID to defend, -1 when you are done: ";
            cin >> territoryID; //TODO edge cases like hello input or !@#$!@$QW you know
            if (territoryID != -1) {
                for (Territory* terr : map->territories) {
                    if (territoryID == terr->id) {
                        if (terr->owner != player) {
                            cout << "\nCannot add territory to list: Player " << terr->owner->pName << " does not own the territory - " << terr->id << ".\n";
                        }
                        else if (terr->owner != NULL) {
                            player->addToDefend(terr);
                        }
                        else {
                            cout << "\nCannot add territory to list: Nobody owns the territory - " << terr->id << ".\n";
                        }
                        break;
                    }
                }
            }
        }
    }
    
    int armycountselected = 0;

    for (it = players.begin(); it != players.end(); it++) {
        player = *it;
        
        while(player->reinforcementPool > 0) {
            for (Territory* t : player->toDefend()) {
                cout << "\nPlayer " + player->pName << " still has " << player->reinforcementPool << " armies to deploy, select how many you wish to deploy to territory id #" << t->id << ": ";
                cin >> armycountselected;
                if (armycountselected <= player->reinforcementPool) {
                    player->issueOrder("Deploy", player, armycountselected, t, t);
                    player->addArmies(-armycountselected);
                }
                else {
                    cout << "\nPlayer " + player->pName << " doesn't have enough armies in their reinforcement pool. Army available to deploy remaining:  " << player->reinforcementPool;
                }
            }
        }


    }
    string orderToIssue;
    int selection = 0;
    int targetID, terrID, targetTerrID;
    Territory* sourceTerr;
    Territory* targetTerr;
    Player* targetPlayer;

    for (it = players.begin(); it != players.end(); it++) {
        player = *it;
        targetPlayer = player;
        cout << "\n\n*********************************************************************************\n";
        cout << "\nPlayer " << player->pName << ", your ID is: " << player->playerID << " and you have the following cards in hand: \n";
        player->getHand()->showHand();
        cout << "\n\nThe following is the list of current players: \n";
        for (int i = 0; i < players.size(); i++) {
            cout << "Player #" << i + 1 << " with ID:" << players[i]->playerID << " and name: " << players[i]->pName << endl;
        }
        cout << "\n\nYou own the following territories: \n";
        for (it2 = players.begin(); it2 != players.end(); it2++) {
            player2 = *it2;
            cout << "Player " << player2->pName << " have the folloring territories: \n";
            for (Territory* terr : player2->territories) {
                cout << "- " << terr->name << " with ID: " << terr->id << " and has " << terr->numArmies << " armies in the territory.\n";
            }
            cout << "\n\n";
        }
        cout << "*********************************************************************************\n\n\n";
        while (selection != 6) {
            cout << "\nPlayer " << player->pName << " please select an order: \n";
            cout << "1 - Advance\n";
            cout << "2 - Airlift\n";
            cout << "3 - Blockade\n";
            cout << "4 - Bomb\n";
            cout << "5 - Negociate\n";
            cout << "6 - No more orders\n";
            cin >> selection;
            if (selection != 6) {
                cout << "Army amount: ";
                cin >> armycountselected;
                cout << "Target Player ID: ";
                cin >> targetID;
                cout << "Source Territory ID: ";
                cin >> terrID;
                cout << "Target Territory ID: ";
                cin >> targetTerrID;

                sourceTerr = map->getTerritoryFromID(terrID);
                targetTerr = map->getTerritoryFromID(targetTerrID);

                for (int i = 0; i < this->players.size(); i++) {
                    if (this->players.at(i)->playerID == targetID) {
                        targetPlayer = this->players.at(i);
                    }
                }

                switch (selection) {
                case 1:
                    player->issueOrder("Advance", targetPlayer, armycountselected, targetTerr, sourceTerr);
                    break;
                case 2:
                    if (player->getHand()->contains(0) <= 0) {
                        cout << "\nPlayer does not have an Airlift card. Cannot issue order.\n";
                    }
                    else {
                        player->issueOrder("Airlift", targetPlayer, armycountselected, targetTerr, sourceTerr);
                        //player->getHand()->removeCardOfType(0);
                    }
                    break;
                case 3:
                    if (player->getHand()->contains(1) <= 0) {
                        cout << "\nPlayer does not have an Blockade card. Cannot issue order.\n";
                    }
                    else {
                        player->issueOrder("Blockade", targetPlayer, armycountselected, targetTerr, sourceTerr);
                        //player->getHand()->removeCardOfType(1);
                    }
                    break;
                case 4:
                    if (player->getHand()->contains(2) <= 0) {
                        cout << "\nPlayer does not have an Bomb card. Cannot issue order.\n";
                    }
                    else {
                        player->issueOrder("Bomb", targetPlayer, armycountselected, targetTerr, sourceTerr);
                        //player->getHand()->removeCardOfType(2);
                    }
                    break;
                case 5:
                    if (player->getHand()->contains(3) <= 0) {
                        cout << "\nPlayer does not have an Negociate card. Cannot issue order.\n";
                    }
                    else {
                        player->issueOrder("Negociate", targetPlayer, armycountselected, targetTerr, sourceTerr);
                        //player->getHand()->removeCardOfType(3);
                    }
                    break;
                default:
                    cout << "\nWrong selection please try again.\n";
                }
            }
            
        }
        selection = 0;
    }
    string nextstate = "executeorders";
    this->transition(nextstate);

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
    int id = 0;
    for (int i = 0; i < players.size(); i++) {
        for (Orders* o : players[i]->orderList->getCurrentOrdersList()) {
            if (o->getCurrentOrder() == "Deploy") {
                if (o->execute()) {
                    players[i]->orderList->removeOrder(o);
                }
            }
        }
    }

    for (int i = 0; i < players.size(); i++) {
        for (Orders* o : players[i]->orderList->getCurrentOrdersList()) {
            if (o->execute()) {
                players[i]->orderList->removeOrder(o);
            }
        }
    }

    //TODO Check if player controls all territory -> winstate.

    string nextstate = "assignreinforcement";
    this->transition(nextstate);
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
                cout << "The winner is " << player->getName() << "! Congratulations!" << endl;
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


