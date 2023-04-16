#include <iostream>
#include <string>
#include "PlayerStrategies.h"
#include "../GameEngine/GameEngine.h"

using namespace std;

/*
 * (1) different players can be assigned different strategies that lead to different behavior using the Strategy design pattern;
 * (2) the strategy adopted by a player can be changed dynamically during play,
 * (3) the human player makes decisions according to user interaction, and computer players make decisions automatically,
 *  which are both implemented using the strategy pattern.
 */
int main() {

    cout << "***Player Strategies Demonstration***" << endl;
    // set up game engine
    GameEngine gameEngine = GameEngine();

    // create new players and assign corresponding strategies
    // p1 - p4 are computer players
    cout << "Player creation and strategies assignment in progress..." << endl;
    vector<Player*> players;
    Player* p1 = new Player("Aggressive Player", 1);
    Player* p2 = new Player("Benevolent Player", 2);
    Player* p3 = new Player("Neutral Player", 3);
    Player* p4 = new Player("Cheater Player", 4);
    Player* p5 = new Player("Human Player", 5);

    // assign player strategies
    p1->playerStrategy = new AggressivePlayerStrategy;
    p2->playerStrategy = new BenevolentPlayerStrategy;
    p3->playerStrategy = new NeutralPlayerStrategy;
    p4->playerStrategy = new CheaterPlayerStrategy;
    p5->playerStrategy = new HumanPlayerStrategy;

    // push the players to the player vector
    players.push_back(p1);
    players.push_back(p2);
    players.push_back(p3);
    players.push_back(p4);
    players.push_back(p5);

    // print players info and corresponding strategies
    vector<Player*>::iterator it;
    cout << "Strategies has been assigned successfully" << endl;
    for(it = players.begin(); it !=players.end(); it++){
        cout << "Player:" << (*it)->getName() << endl;
        cout << "Strategy: " << (*it)->getPlayerStrategy() << endl;
        cout << " " << endl;
    }

    //PAUSE
    cout << "\nPress any key to continue..";
    cin.get();

    // launch the game
    cout << "Game started!" << endl;
    gameEngine.mainGameLoop();

    // memory arrangement to prevent memory leak
    for(auto p:players){
        delete p;
    }
    players.clear();
}