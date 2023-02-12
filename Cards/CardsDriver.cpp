#include "Cards.h"
#include "../Orders/Orders.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
    // initialize a hand and a deck
    Hand* hand = new Hand();
    Deck* deck = new Deck();
    OrdersList orderList(4);
    cout << "The deck has " << deck->getSize() << " cards in it.\n";
    cout << "The hand has: ";
    hand->showHand();
    cout << "\n";
    // drawing 4 cards from the deck into the hand
    deck->draw(hand);
    deck->draw(hand);
    deck->draw(hand);
    deck->draw(hand);

    // displaying deck size and hand after drawing 4 cards
    cout << "After drawing cards, the hand now looks like: ";
    hand->showHand();
    cout << "\n";
     cout << "The deck now has " << deck->getSize() << " cards in it.\n";
    // displaying deck size and hand after playing 2 cards
    hand->getCard(0)->play(hand, 0, deck, &orderList);
    hand->getCard(1)->play(hand, 1, deck, &orderList);
    
    cout << "After playing 2 cards, the hand now looks like: ";
    hand->showHand();
    cout << "\n";
    cout << "The deck now has " << deck->getSize() << " cards in it.\n";

    hand->del();
    deck->del();
    delete deck;
    deck = NULL;
    delete hand;
    hand = NULL;
}