#include "Player.h"

int main(){

    // create territories that a player owns (randomly)
    vector<Territory *> terre1;
    vector<Territory *> terre2;

    // create players
    Player *p1 = new Player("p1", terre1, new Hand());

    // territories to be attacked by player 1
    vector<Territory *> attack = p1->toAttack();
    p1->printAttackList(attack);

    // territories to be defended by player 1
    vector<Territory *> defend = p1->toDefend();
    p1->printDefendList(defend);

    // issue order for player 1
    p1->issueOrder();
}
