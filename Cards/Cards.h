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
        // copy constructor
        Card(const Card& card);
        // assignment operator
        Card& operator=(const Card& card);
        // stream insertion operator
        friend std::ostream& operator<<(std::ostream& out, const Card& card);
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
        void removeCard(int);
        void showHand();
};

class Deck {
    Card* cardDeck[50];
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