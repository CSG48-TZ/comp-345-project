//
// Created by Salman Hussain Ali on 02/02/2023.
//

#include "Map.h"

// Territory class implementation

Territory::Territory(string name, int continent, int number1, int number2) {
    this->name = name;
    this->continent = continent;
    this->number1 = number1;
    this->number2 = number2;
    this->numArmies = 0;
}

Territory::Territory(const Territory &territory) {
    this->name = territory.name;
    this->visited = territory.visited;
    this->numArmies = territory.numArmies;
    this->number1 = territory.number1;
    this->number2 = territory.number2;
    this->continent = territory.continent;
    this->id = territory.id;
    this->owner = territory.owner;
    this.edges;// TODO
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

void Territory::~Territory(){
    delete name;
    delete visited;
    delete continent;
    delete numArmies;
    delete owner; // Not sure if this is right
    delete number1;
    delete number2;
    delete id;
    delete edges;

    name = NULL;
    visited = NULL;
    continent = NULL;
    numArmies = NULL;
    owner = NULL; // Not sure this is right
    number1 = NULL;
    number2 = NULL;
    id = NULL;
    edges = NULL;
}

ostream& operator<<(ostream& out, Territory& territory){
    out << "Territory name: " << territory.name << endl;
    out << "Continent number: " << territory.continent << endl;
    out << "Number of armies in territory: " << territory.numArmies << endl;
    out << "Owner: " << territory.owner << endl; // TODO - add player name "owner.name"
    out << "Number 1: " << territory.continent << endl;
    out << "Number 2: " << territory.name << endl;
    out << "Territories connected to: " << endl;
    for(int i = 0; i < territory.edges.size(); i ++){
        cout << "\t" << territory.edges.at(i)->name << endl;
    }

    return out;
}

Territory Territory::operator=(const Territory& territory){
    this->name = territory.name;
    this->owner = territory.owner;
    this->numArmies = territory.numArmies;
    this->continent = territory.continent;
    this->id = territory.id;
    this->visited = territory.visited;
    this->number1 = territory.number2;
    this->number2 = territory.number2;
    this->edges = territory.edges;

    return *this;
}

// Map class implementation
Map::Map(vector <vector<Territory *>> *continents, vector<Territory *> territories) {
    this->continents = continents;
    this->territories = territories;
}

Map::Map(const Map& map){ // TODO

}

void Map::addTerritory(Territory *territory) {
    this->territories.push_back(territory); // Adds the territory to territory list

    int numContinent = territory->continent;

    this->continents.at(numContinent).push_back(territory); // Adds the territory to the continents list
}

bool Map::validate() {
    unordered_map<string,int> duplicates ; // Maps the territory name to its continent value

    bool dfs = DFS(this->territories.at(0), map);

    if(!dfs){
        return false;
    }

    for(int index = 0; index < territories.size(); i ++){
        Territory * temp = territories.at(index);
        if(!temp->visited){
            cerr<< "Territory: " << temp << " is not connected to the rest of the map" << endl;
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
        cerr << "Territory: " << territory->name << " has a duplicate" << endl;
        return false; // Already found while doing DFS
    }


    for(int i = 0; i < territory->edges.size(); i ++){
        Territory * next = territory->edges.at(i);
        if(!next->visited){
            return DFS(next, duplicate);
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
        if( next->continent == continentNum  && !next->visited){
            return 1+ continentDFS(next);
        }
    }

    return 1;
}

Map::~Map() {
    delete continents;
    delete territories;

    continents = NULL;
    territories = NULL;
}

ostream& operator<<(ostream& out, Map& map){
    out<< "All territories: " << endl;
    for(int i = 0; i < map.territories.size(); i ++){
        out << map.territories.at(i)->name << endl;
    }
    return out;
}

Map Map::operator=(const Map& map){
    this->territories = map.territories;
    this->continents = map.continents;

    return *this;
}
// Maploader implementation

Maploader::Maploader(string filename) {
    this->filename = filename;
}

Maploader::~Maploader() {
    delete filename;

    filename = NULL;
}

ostream& operator<<(ostream& out, Maploader& maploader){
    out<< "Maploader filename: " << maploader.filename << endl;

    return out;
}

Maploader Maploader::operator=(const Maploader& maploader){
    this->filename = maploader.filename;
}

Maploader::Maploader(const Maploader &maploader) {
    this->filename = maploader.filename;
}

Map *Maploader::load() {

    ifstream infile("europe.txt");

    vector<Territory *> territoriesVector;
    vector<vector<Territory*>> continentsVector;

    string line;
    bool continents = false;
    bool territories = false;
    bool edges = false;

    int numContinents = 0;

    while(getline(infile, line)){
        if(line == ""){
            continue;
        }

        if(line == "[continents]"){
            continents = true;
        }else if(line == "[countries]"){
            territories = true;
        }else if(line == "[borders]"){
            edges = true;
        }

        stringstream s(line);

        if(edges){
            int sourceIndex;
            int count = 0;
            int id;
            while(s >> id){
                id --;
                if(count == 0){ // Extracts source territory
                    sourceIndex = id;
                }else{
                    Territory * source = territoriesVector.at(sourceIndex);
                    source->addEdge(territoriesVector.at(id));
                }
                count ++;
            }

        } else if(territories){
            int id;
            string name;
            int continent;
            int num1;
            int num2;

            s >> id >> name >> continent >> num1 >> num2;

            id --;
            continent --;

            Territory * territory = new Territory(id, name, continent, num1, num2);

            cout << "Added territory: " << name << endl;

            territoriesVector.push_back(territory);
            continentsVector.at(continent).push_back(territory);
        } else if( continents){
            vector<Territory *> countries;
            continentsVector.push_back(countries);
        }
    }

    cout << "Loaded map" << endl;

    Map * map = new Map(continentsVector, territoriesVector);

    return map;
}