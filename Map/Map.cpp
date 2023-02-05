//
// Created by Salman Hussain Ali on 02/02/2023.
//

#include "Map.h"

// Territory class implementation

Territory::Territory(string name, int continent, int number1, int number2) {
    this->name = name;;
    this->continent = continent;
    this->number1 = number1;
    this->number2 = number2;
    this->numArmies = 0;
}

void Territory::changeOwner(int *newOwner) {
    this->owner = newOwner;
}

void Territory::addArmies(int number) {
    this->numArmies = this->numArmies + number;
}

void Territory::addEdge(Territory *adjacent) {
    this->edges.push_back(adjacent);
}

// Map class implementation

Map::Map(vector <vector<Territory *>> *continents, vector<Territory *> territories) {
    this->continents = continents;
    this->territories = territories;
}

void Map::addTerritory(Territory *territory) {
    this->territories.push_back(territory); // Adds the territory to territory list

    int numContinent = territory->continent - 1;    // Have to decrease value of continent because it starts at 1
                                                    // in text file

    this->continents.at(numContinent).push_back(territory); // Adds the territory to the continents list
}

bool Map::validate() {
    // 1) 3) Create a hashmap and do a DFS on the graph. When visiting a territory, add its name to the hashmap
    // and mark it as visited. If name is already in the hashmap,(name exists twice) so return false. When DFS is done, iterate over all
    // the territories in the vector and check if each one has been visited. While iterating, if a territory has been
    // visited, mark it as unvisited(in case validate is called again).
    // 2) BFS on random territory in continent and mark the territories from the same continent as visited. While doing
    // the BFS add a static variable counter and when the counter is the same as size of the continent, return true
}