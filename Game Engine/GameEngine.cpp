#include "../Game Engine/GameEngine.h"
#include <iostream>
#include <string>
#include <iomanip>

TournamentMode::TournamentMode() {
	this->tourMaxTurn = 500;
	this->tourGameNum = 0;
}
TournamentMode::~TournamentMode() {
	if (tourStrategies.size() != 0) {
		tourStrategies.clear();
	}
	if (tourMaps.size() != 0) {
		tourMaps.clear();
	}
}

TournamentMode::TournamentMode(TournamentMode* other) {
	this->tourGameNum = other->tourGameNum;
	this->tourMaps = other->tourMaps;
	this->tourMaxTurn = other->tourMaxTurn;
	this->tourStrategies = other->tourStrategies;
}
TournamentMode& TournamentMode::operator=(const TournamentMode& other) {
	this->tourGameNum = other.tourGameNum;
	this->tourMaps = other.tourMaps;
	this->tourMaxTurn = other.tourMaxTurn;
	this->tourStrategies = other.tourStrategies;
	return *this;
}
ostream& operator<<(ostream& out, const TournamentMode& mode) {
	out << "Tournament Mode state is " << to_string(mode.tourGameNum) << endl;
	return out;
}

string TournamentMode::stringToLog() {
	string message = "Tournament mode:\nM: ";
	for (int i = 0; i < this->tourMaps.size(); i++) {
		message = message + this->tourMaps[i] + ", ";
	}

	message += "\nP: ";
	for (int i = 0; i < this->tourStrategies.size(); i++) {
		message = message + this->tourStrategies[i] + ", ";
	}

	message += "\nG: ";
	message += to_string(this->tourGameNum);
	message += "\nP: ";
	message += to_string(this->tourMaxTurn);

	message += "\n\nResults\n\n";

	// Print the result


	for (int i = 0; i < this->tourMaps.size(); i++) {
		message += this->tourMaps[i];
		message += ":\n";
		for (int j = 0; j < tourGameNum; j++) {
			int index = i * this->tourMaps.size() + j;
			message = message + "\tGame " + to_string(i + 1) + ":\t" + this->winnerStrategies[index] + "\n";
		}
		message += "\n";
	}

	return message;
}


void TournamentMode::generateLogFile() {
	notify(this);
}


// Implementation of Constructors
GameEngine::GameEngine() {
	currentState = new State(START);
	this->initializeCommandProcessor();
	this->map = NULL;
	this->mode = new TournamentMode();
}

// copy constructor
GameEngine::GameEngine(const GameEngine& engine) {
	this->currentState = engine.currentState;
	this->cmdPcs = engine.cmdPcs;
	this->map = engine.map;
	this->mode = new TournamentMode();
}

// assignment operator
GameEngine& GameEngine::operator=(const GameEngine& engine) {
	this->currentState = engine.currentState;
	this->cmdPcs = engine.cmdPcs;
	this->mode = engine.mode;
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
	delete mode;
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
	else if (state == "tournament") {
		state = "start";
		*currentState = State::START;
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

		if (nextState == "tournament") {
			cout << "Tournament mode starts." << endl;
			this->initializeTourMode(command);
			return true;
		}

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

					for (int i = 0; i < numTerritories; i++) { // Iterates through all the territories
						players[playersIndex % players.size()]->addOwnedTerritory(this->map->territories.at(i));
						playersIndex++;
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
			else if (behavior == "addplayer" && result.size() == 2) {
				string ps = result[1];
				PlayerStrategy* playstrat;
				if (ps == "h" || ps == "H") {
					playstrat = new HumanPlayerStrategy();
				}
				else if (ps == "a" || ps == "A") {
					playstrat = new AggressivePlayerStrategy();
				}
				else if (ps == "b" || ps == "B") {
					playstrat = new BenevolentPlayerStrategy();
				}
				else if (ps == "n" || ps == "N") {
					playstrat = new NeutralPlayerStrategy();
				}
				else if (ps == "c" || ps == "C") {
					playstrat = new CheaterPlayerStrategy();
				}
				else {
					cout << "Please enter a correct argument for the player strategy: " << endl;
					cout << "h or H : Human " << endl;
					cout << "a or A : Aggressive " << endl;
					cout << "b or B : Benevolent " << endl;
					cout << "n or N : Neutral " << endl;
					cout << "c or C : Cheater " << endl;
					continue;
				}
				int num = (int)this->players.size();
				if (num == 6) {
					cout << "A maximum of 6 players are allowed in this game" << endl;
					cout << "Please input command \"gamestart\" to start the game now." << endl;
					continue;
				}
				else {

					Player* player = new Player(result[1], playersID, playstrat);
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
	for (Player* player : players) {
		while (player->issueOrder()) {
			cout << "Issuing order for " << player->pName << endl;
		}
	}
	string nextstate = "executeorders";
	this->transition(nextstate);

}


//Helper function for the neutral player
void GameEngine::gatherAndCombinePlayers() {
	for (Territory* t : this->map->territories) { //Go through ALL territories belongs to the current player
		if ((t->owner->pName) == "neutralplaceholder") { ///if the owner name of that territory is the placeholdername 
			bool flag = false;
			for (Player* p : players) { //go through all the players playeing
				if (p->isNeutral() && p != t->owner) { //look for our neutral player
					delete t->owner;
					t->owner = nullptr;
					t->changeOwner(p); //give him our territory
					flag = true; // set the flag as true if we find a neutral player in the current playerlist
				}
			}

			if (!flag) {
				// If no neutral player in the player list now, add what we created to the player list
				t->owner->setName("n");
				int playerID = this->players.size();
				t->owner->setPlayerID(playerID);
				players.push_back(t->owner);
				flag = true;
			}
		}
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
	int id = 0;
	for (int i = 0; i < players.size(); i++) {
		for (Orders* o : players[i]->orderList->getCurrentOrdersList()) {
			if (o->getCurrentOrder() == "Deploy") {
				if (o->execute()) {
					players[i]->orderList->removeOrder(o);
				}
				else {
					cout << "Order " << o->toString() << " is invalid! Romved from the list.";
					players[i]->orderList->removeOrder(o);
				}
			}
		}
	}

	for (int i = 0; i < players.size(); i++) {
		for (Orders* o : players[i]->orderList->getCurrentOrdersList()) {
			if (o->execute()) {
				// For blockade
				if (o->getCurrentOrder() == "Blockade") {
					this->gatherAndCombinePlayers();
				}

				if (o->getOrderTargetPlayer()->isNeutral())
				{
					cout << "Neutral player was attacked. Switching to aggressive" << endl;
					o->getOrderTargetPlayer()->playerStrategy = new AggressivePlayerStrategy();
				}
				players[i]->orderList->removeOrder(o);
			}
			else {
				cout << "Order " << o->toString() << " is invalid! Romved from the list.";
				players[i]->orderList->removeOrder(o);
			}
		}
		// During the order execution, if a player owns all the territories, announce the player and end the game
		if (players[i]->territories.size() == (int)map->territories.size() || players.size() == 1) {
			cout << "The player is " << players[i]->getName() << "! Congratulations!" << endl;
			// Add winner strategy
			string winnerStrategy = players[i]->getPlayerStrategy()->getStrategyName();
			this->mode->winnerStrategies.push_back(winnerStrategy);

			//exit the loop
			string nextState = "win";
			this->transition(nextState);
			break;
		}
	}

	if (this->getCurrentState() == "executeorders") {
		string nextstate = "assignreinforcement";
		this->transition(nextstate);
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
	// end the game if current state is WIN
	while (this->getCurrentState() != "win" && gameRound <= this->mode->tourMaxTurn) {
		for (auto& player : players) {
			// if a player owns 0 territory, remove from the game
			if (player->territories.empty()) {
				cout << player->getName() << " is removed from the game for having 0 territory" << endl;
				vector<Player*>::iterator it = players.begin();
				while (it != players.end()) {
					if (player == *it) {
						it = players.erase(it);
						break;
					}
					else {
						++it;
					}
				}
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

	if (this->getCurrentState() != "win") {
		string nextState = "win";
		this->transition(nextState);
		string winnerStrategy = "Draw";
		this->mode->winnerStrategies.push_back(winnerStrategy);
	}
	if (this->mode->tourGameNum == 0) {
		// Decide the next state by command if it's the general mode
		while (true) {
			cout << "Please input \"replay\" or \"quit\" to restart or end the game. " << endl;
			Command* command = this->cmdPcs->getCommand();
			if (command == NULL) {
				cout << "No command was input.System Exit. " << endl;
				break;
			}
			// Check if the command is valid and save effect
			string currentState = this->getCurrentState();
			string nextState = cmdPcs->validate(command, currentState);
			cout << "Details of the input command: \n" << *command << endl;

			// Finish the infinite loop if we can move to an acceptable state
			if (nextState == "start" || nextState == "exit program") {
				this->transition(nextState);
				break;
			}
		}
	}



}

void GameEngine::runGame() {
	while (this->getCurrentState() == "start") {
		this->startupPhase();

		// If the tournament mode is not initialized, then use the general mode
		if (this->mode->tourGameNum == 0) {
			this->mainGameLoop();
		}
		else {
			// If the game engine is on the tournament mode, play the game
			for (int j = 0; j < this->mode->tourMaps.size(); j++) {

				for (int i = 0; i < this->mode->tourGameNum; i++) {
					this->tournamentModeStartUp(j);
					this->mainGameLoop();
					for (Player* p : players) {
						delete p;
						p = nullptr;
					}
					players.clear();
				}
			}
			this->mode->generateLogFile();
			while (true) {
				cout << "Please input \"replay\" or \"quit\" to restart or end the game. " << endl;
				Command* command = this->cmdPcs->getCommand();
				if (command == NULL) {
					cout << "No command was input.System Exit. " << endl;
					break;
				}
				// Check if the command is valid and save effect
				string currentState = this->getCurrentState();
				string nextState = cmdPcs->validate(command, currentState);
				cout << "Details of the input command: \n" << *command << endl;

				// Finish the infinite loop if we can move to an acceptable state
				if (nextState == "start" || nextState == "exit program") {
					this->transition(nextState);
					break;
				}
			}
		}
	}
}

void GameEngine::tournamentModeStartUp(int mapID) {
	string filename = this->mode->tourMaps[mapID];
	Maploader maploader(filename);
	this->map = maploader.load();
	cout << "Map" << filename << " has been loaded" << endl;

	if (this->map->validate()) {
		cout << "Map validated successfully" << endl;
	}
	else {
		cout << "Map invalid. Game stop." << endl;
		exit(0);
	}

	PlayerStrategy* playstrat;
	for (int i = 0; i < this->mode->tourStrategies.size(); i++) {
		string ps = this->mode->tourStrategies[i];
		if (ps == "h" || ps == "H") {
			playstrat = new HumanPlayerStrategy();
		}
		else if (ps == "a" || ps == "A") {
			playstrat = new AggressivePlayerStrategy();
		}
		else if (ps == "b" || ps == "B") {
			playstrat = new BenevolentPlayerStrategy();
		}
		else if (ps == "n" || ps == "N") {
			playstrat = new NeutralPlayerStrategy();
		}
		else if (ps == "c" || ps == "C") {
			playstrat = new CheaterPlayerStrategy();
		}
		else {
			cout << "Incorrect strategy. Ignored. " << endl;
			continue;
		}
		int num = (int)this->players.size();
		if (num == 6) {
			cout << "A maximum of 6 players are allowed in this game" << endl;
			cout << "Please input command \"gamestart\" to start the game now." << endl;
			continue;
		}
		else {
			Player* player = new Player(ps, i, playstrat);
			players.push_back(player);
			cout << "Added player: " << ps << " with id: " << i << endl;
		}
	}


	if (this->players.size() < 2) {
		cout << "At least two players are necessary to start the game. Game cannot be started. " << endl;
		exit(0);
	}
	else {
		// Allocates one territory to each player. Each territory allocated are equidistant from each other
		int numTerritories = (int)this->map->territories.size();
		int gap = numTerritories / (int)players.size();
		int playersIndex = 0;

		for (int i = 0; i < numTerritories; i++) { // Iterates through all the territories
			players[playersIndex % players.size()]->addOwnedTerritory(this->map->territories.at(i));
			playersIndex++;
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
	string nextState = "assignreinforcement";
	this->transition(nextState);


}

void GameEngine::initializeTourMode(Command* commandObj) {
	string command = commandObj->getCommandName();

	string space = " ";
	string restOfCommand = command.substr(command.find(space) + 1, command.size());

	vector<string> params;
	stringstream ss(restOfCommand);
	string param;
	while (getline(ss, param, ' ')) {
		params.push_back(param);
	}

	// Split the map command into parameters using "," as a delimiter
	stringstream ssm(params[1]);
	string map;
	while (getline(ssm, map, ',')) {
		this->mode->tourMaps.push_back(map);
	}

	// Split the player strategy command into parameters using "," as a delimiter
	stringstream sss(params[3]);
	string strategy;
	while (getline(sss, strategy, ',')) {
		this->mode->tourStrategies.push_back(strategy);
	}

	this->mode->tourGameNum = stoi(params[5]);
	this->mode->tourMaxTurn = stoi(params[7]);
}
