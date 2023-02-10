#include "Cards.h"
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

// Array of names of card types 
const string cardTypes[6] = {"Airlift", "Blockade", "Bomb", "Diplomacy", "Reinforcement", "Empty"};

// Card definitions

// Default constructor
Card::Card(){
    cardType= NULL;
}

// Copy constructor
Card::Card(int type){
    cardType = type;
}

// Destructor
Card::~Card() {
    
}

// returns an int responding to the card type
int Card::getType(){
    if (this) {
        return cardType;
    }
    else {
        // returns the index of 5 which is "Empty"
        return 5;
    }
}

// sets the card type
void Card::setType(int newType){
    cardType = newType;
}

// plays a card from hand which removes it and returns it to the deck
void Card::play(Hand* hand, int cardNum, Deck* deck) {		
	hand->removeCard(cardNum);	
	deck->returnCard(this);
}

// Hand definitions

// Default constructor
Hand::Hand(){
    for (int i =0; i < 7; i++){
        cardHand[i] = NULL;
    }
    cardAmount = 0;
}

// delete hand
void Hand::del(){
    for (int i =0; i < 7; i++){
        delete cardHand[i];
        cardHand[i] = NULL;
    }
}

// add a card to the hand (utilized in the deck draw function)
bool Hand::addCard(Card* card){
    // checks to see if the player doesn't have a full hand of cards (max is set to 7 cards)
    if (cardAmount < 7){
        cardHand[cardAmount] = card;
        cardAmount += 1;
        return true;
    }
    else {
        return false;
    }
}

// remove card from the hand
void Hand::removeCard(int cardNum) {
    cardHand[cardNum] = cardHand[cardAmount - 1];
    cardHand[cardAmount - 1] = NULL;
    cardAmount -= 1;
}

// gets card the specified card in the hand
Card* Hand::getCard(int cardNum){
    return cardHand[cardNum];
}

// displays hand
void Hand::showHand(){
    cout << cardTypes[cardHand[0]->getType()] << 
    " | "<< cardTypes[cardHand[1]->getType()] << 
    " | "<< cardTypes[cardHand[2]->getType()] << 
    " | "<< cardTypes[cardHand[3]->getType()] << 
    " | "<< cardTypes[cardHand[4]->getType()] << 
    " | "<< cardTypes[cardHand[5]->getType()] << 
    " | "<< cardTypes[cardHand[6]->getType()]; 
}

// Deck definitions

// Create the deck (deck contains 10 fo each card totalling to 50)
Deck::Deck() {
    for (int i = 0; i < 10; i++){
        cardDeck[i] = new Card(0);
    }
    for (int i = 10; i < 20; i++){
        cardDeck[i] = new Card(1);
    }
    for (int i = 20; i < 30; i++){
        cardDeck[i] = new Card(2);
    }
    for (int i = 30; i < 40; i++){
        cardDeck[i] = new Card(3);
    }
    for (int i = 40; i < 50; i++){
        cardDeck[i] = new Card(4);
    }
    // 49 because index starts at 0
    deckAmount = 50;
}

// Deletes the whole deck
void Deck::del() {
    for (int i = 0; i < 49; i++){
        delete cardDeck[i];
        cardDeck[i] = NULL;
    }
}

// Draws a random card from the deck 
void Deck::draw(Hand* hand){
    // chooses a random number within range 
    srand((unsigned)time(NULL));
    int randNum = (rand() % deckAmount-1);
    // adds the card into the hand
    hand->addCard(cardDeck[randNum]);
    // if the random number is not the last card in the deck then it swaps with the last one and deletes it
    if (randNum != deckAmount-1){
        cardDeck[randNum] = cardDeck[deckAmount-1];
        cardDeck[deckAmount-1] = NULL;
    }
    // if the random number is the last card then it deletes it
    else {
        cardDeck[randNum] = NULL;
    }
    deckAmount -= 1;
}

// Returns the card to the end of the deck and increases size
void Deck::returnCard(Card* card) {
    deckAmount += 1;
    cardDeck[deckAmount] = card;
}

// Returns the size of the deck
int Deck::getSize() {
    return deckAmount;
}