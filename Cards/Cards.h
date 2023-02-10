#pragma once
#include <iostream>
#include <string>
using namespace std;

class Hand;
class Deck;

class Card {
    int cardType;

public:
        // Default Constructor
        Card();
        // Destructor
        ~Card();
        // Copy constructor
        Card(int);
        void play(Hand*,int,Deck*);
        int getType();
        void setType(int);
};

class Hand {
    Card* cardHand[7];
    int cardAmount;

public:
        // Default Constructor
        Hand();
        void del();
        Card* getCard(int);
        bool addCard(Card*);
        void removeCard(int);
        void showHand();
};

class Deck {
    Card* cardDeck[50];
    int deckAmount;

public:
        // Default Constructor
        Deck();
        void del();
        void returnCard(Card*);
        void draw(Hand*);
        int getSize();
};