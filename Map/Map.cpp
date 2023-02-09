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

    int numContinent = territory->continent;

    this->continents.at(numContinent).push_back(territory); // Adds the territory to the continents list
}

bool Map::validate() {
    unordered_map<string,int> duplicates ; // Maps the territory name to its continent value

    bool dfs = DFS(this->territories.at(0), map);

    if(dfs == false){
        return false;
    }

    for(int index = 0; index < territories.size(); i ++){
        Territory * temp = territories.at(index);
        if(temp->visited == false){
            cout<< "Territory: " << temp << " is not connected to the rest of the map" << endl;
            return false;
        } else {
            temp->visited = false; // Resets visited to false for continentDFS
        }
    }

    for(int index = 0; index < continents.size(); index ++){
        int territoriesFound = continentDFS(continents.at(index).at(0));

        if(territoriesFound != continents.at(index).size()){
            return false;
        }
    }

    return true;
}

// Goes through the map and marks the territories iterated through as visited and checks if two territories
// have the same name
bool Map::DFS(Territory * territory, unordered_map<string, int> * duplicate){
    territory->visited = true;

    if( duplicate.find(territory->name) == duplicate->end()){
        duplicate[territory->name] = territory->continent; // Not found so insert it into the map
    }
    else{
        cout << "Territory: " << territory->name << " has a duplicate" << endl;
        return false; // Already found while doing DFS
    }


    for(int i = 0; i < territory->edges.size(); i ++){
        Territory * next = territory->edges.at(i);
        if(next->visited == false){
            return DFS(next);
        }
    }

    return true;
}

// Returns number of territories found within a continent
int Map::continentDFS(Territory * territory){
    territory->visited = true;
    int continentNum = territory->continent;

    for(int i = 0; i < territory->edges.size(); i ++){
        Territory * next = territory->edges.at(i);
        if( next->continent == continentNum  && next->visited == false){
            return 1+ continentDFS(next);
        }
    }

    return 1;
}