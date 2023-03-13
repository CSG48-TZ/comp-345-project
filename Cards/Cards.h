#pragma once
#include "../Orders/Orders.h"
#include <iostream>
#include <string>
using namespace std;

class Hand;
class Deck;
class OrdersList;

class Card {
    int cardType;

public:
        // Default Constructor
        Card();
        // Destructor
        ~Card();
        // copy constructor
        Card(const Card& card);
        // assignment operator
        Card& operator=(const Card& card);
        // stream insertion operator
        friend std::ostream& operator<<(std::ostream& out, const Card& card);
        Card(int);
        void play(Hand*, int, Deck*, OrdersList*);
        int getType();
        void setType(int);
};

class Hand {
    Card* cardHand[7];
    int cardAmount;
    static const int MAX_AMOUNT_OF_CARDS = 7;

public:
       // Default Constructor
        Hand();
        // Destructor
        ~Hand();
        // copy constructor
        Hand(const Hand& hand);
        // assignment operator
        Hand& operator=(const Hand& hand);
        // stream insertion operator
        friend std::ostream& operator<<(std::ostream& out, const Hand& hand);
        void del();
        Card* getCard(int);
        bool addCard(Card*);
        void removeCardAtIndex(int);
        void removeCardOfType(int type);
        void showHand();
        int contains(int type);
};

class Deck {
    static const int MAX_AMOUNT_IN_DECK = 50;
    Card* cardDeck[MAX_AMOUNT_IN_DECK];
    int deckAmount;

public:
        // Default Constructor
        Deck();
        // Destructor
        ~Deck();
        // copy constructor
        Deck(const Deck& deck);
        // assignment operator
        Deck& operator=(const Deck& deck);
        // stream insertion operator
        friend std::ostream& operator<<(std::ostream& out, const Deck& deck);
        void del();
        void returnCard(Card*);
        void draw(Hand*);
        int getSize();
};