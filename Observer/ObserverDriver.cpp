#include "LoggingObserver.h"
#include "../CommandProcess/CommandProcessing.h"
#include "../Game Engine/GameEngine.h"
#include "../Orders/Orders.h"


int main() {
    GameEngine* engine = new GameEngine();
    // Create an observer for every object
    LogObserver* gameEngineObserver = new LogObserver(engine);
    LogObserver* processorObserver = new LogObserver(engine->cmdPcs);
    while (engine->getCurrentState() != "assignreinforcement") {
        // Ask for input command
        Command* command = engine->cmdPcs->getCommand();
        LogObserver* commandObserver = new LogObserver(command);
        if (command == NULL) {
            cout << "No command was input." << endl;
            break;
        }
        // Check if the command is valid and save effect
        string currentState = engine->getCurrentState();
        string nextState = engine->cmdPcs->validate(command, currentState);

        engine->transition(nextState);

        // Memory arrangements

        delete commandObserver;
        commandObserver = NULL;
        delete command;
        command = NULL;

        cout << "\nInput any letter to continue..." << endl;
        string ctn;
        getline(cin, ctn);
        cout << endl;
        
    }

    cout << "\nCreating setup...";
    //Creating 3 players
    Player* p = new Player("Dax", 1);
    Player* t = new Player("Enemy", 2);
    Player* r = new Player("Neutral", 3);

    //Loading the map
    Maploader maploader = { "test.txt" };
    Map* map = maploader.load();

    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

    //Creating some territories for DEMO.
    Territory* playerTerr = map->territories.at(14);
    Territory* targetTerr = map->territories.at(8);
    Territory* neutralTerr = map->territories.at(23);

    Territory* t1 = map->territories.at(1);
    Territory* t2 = map->territories.at(2);
    Territory* t3 = map->territories.at(3);
    Territory* t4 = map->territories.at(4);
    Territory* t5 = map->territories.at(5);
    Territory* t6 = map->territories.at(6);

    //Adding territories to players.
    t->addOwnedTerritory(targetTerr);
    p->addOwnedTerritory(playerTerr);
    r->addOwnedTerritory(neutralTerr);

    //Adding armies to territories
    playerTerr->addArmies(500);
    targetTerr->addArmies(50);
    neutralTerr->addArmies(500);

    cout << "\nAdvance Order 0 will be issued with a territory that is not owned by the player.\nPress any key to continue..";
    cin.get();
    p->issueOrder("Advance", t, 500, targetTerr, t1);

    //Creating observers for orders
    LogObserver* orderListObserver= new LogObserver(p->getOrderList());
    LogObserver* ordersObserver = new LogObserver(p->getOrderList()->getLastOrder());
    cout << "*********************************************************************************";
    p->getOrderList()->getLastOrder()->execute();
    cout << "\n*********************************************************************************\n\n";

    // Memory Arrangement
    delete gameEngineObserver, processorObserver, orderListObserver, ordersObserver;
    gameEngineObserver, processorObserver, orderListObserver, ordersObserver = NULL;
    delete engine;
    engine = NULL;
    delete p, t, r, playerTerr, targetTerr, neutralTerr, t1, t2, t3, t4, t5, t6, map;
    p, t, r, playerTerr, targetTerr, neutralTerr, t1, t2, t3, t4, t5, t6, map = nullptr;
	return 0;
}
