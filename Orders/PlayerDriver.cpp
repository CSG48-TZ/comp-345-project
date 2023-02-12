#include "Player.h"

int main(){

    // create territories that a player owns (randomly)
    vector<Territory *> terre1;
    vector<Territory *> terre2;

    // create players
    Player* p1 = new Player("Dax", 1, terre1, new Hand());

    // territories to be attacked by player 1
    vector<Territory *> attack = p1->toAttack();
    p1->printAttackList(attack);

    // territories to be defended by player 1
    vector<Territory *> defend = p1->toDefend();
    p1->printDefendList(defend);

    string orderType = "";
    int random;
    srand((int)time(0));

    // issue order for player 1
    for (int i = 0; i < 10; i++) {
        random = rand() % 6;

        switch (random) {
        case 0:
            p1->issueOrder("Deploy", rand() % 6, p1->playerID, rand() % 200 + 1, rand() % 120, rand() %120, i);
            break;
        case 1:
            p1->issueOrder("Bomb", rand() % 6, p1->playerID, rand() % 200 + 1, rand() % 120, rand() % 120, i);
            break;
        case 2:
            p1->issueOrder("Blockade", rand() % 6, p1->playerID, rand() % 200 + 1, rand() % 120, rand() % 120, i);
            break;
        case 3:
            p1->issueOrder("Advance", rand() % 6, p1->playerID, rand() % 200 + 1, rand() % 120, rand() % 120, i);
            break;
        case 4:
            p1->issueOrder("Airlift", rand() % 6, p1->playerID, rand() % 200 + 1, rand() % 120, rand() % 120, i);
            break;
        case 5:
            p1->issueOrder("Negociate", rand() % 6, p1->playerID, rand() % 200 + 1, rand() % 120, rand() % 120, i);
            break;
        default:
            break;
        }
    }
    
    return 0;
}
