//
// Created by Salman Hussain Ali on 02/02/2023.
//

#include "Map.h"

// Territory class implementation

// Constructor with parameters
Territory::Territory(int id, string name, int continent, int number1, int number2) {
    this->id = id;
    this->name = name;
    this->continent = continent;
    this->number1 = number1;
    this->number2 = number2;
    this->numArmies = 0;
}

// Copy constructor for Territory class
Territory::Territory(const Territory& territory) {
    this->name = territory.name;
    this->visited = territory.visited;
    this->numArmies = territory.numArmies;
    this->number1 = territory.number1;
    this->number2 = territory.number2;
    this->continent = territory.continent;
    this->id = territory.id;
    this->owner = territory.owner;
    vector<Territory *> adjacent;
    for(int i = 0; i < edges.size(); i ++){
        adjacent.push_back(edges.at(i));
    }
    this->edges = adjacent;
}

// Change owner of territory
void Territory::changeOwner(int *newOwner) {
    this->owner = newOwner;
}

// Add number of armies in territory
void Territory::addArmies(int number) {
    this->numArmies = this->numArmies + number;
}

// Adds pointer to Territory object to edge list
void Territory::addEdge(Territory *adjacent) {
    this->edges.push_back(adjacent);
}

// Destructor for territory object
void Territory::~Territory(){
    edges.clear();
}

// Stream insertion operator for Territory
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

// Assignment operator for Territory
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
Map::Map(vector <vector<Territory *>>& continents, vector<Territory *>& territories) {
    this->continents = continents;
    this->territories = territories;
}

// Copy constructor for Map class
Map::Map(const Map& map){
    for(int i = 0; i < territories.size(); i ++){
        Territory * territory = new Territory(*territories.at(i));
        territories.push_back(territory);
        continents.at(territory->continent).push_back(territory);
    }
}

// Adds a territory to the map
void Map::addTerritory(Territory *territory) {
    this->territories.push_back(territory); // Adds the territory to territory list

    int numContinent = territory->continent;

    this->continents.at(numContinent).push_back(territory); // Adds the territory to the continents list
}

bool Map::validate() {
    unordered_map<string,int> duplicates ; // Maps the territory name to its continent value

    bool dfs = DFS(this->territories.at(0), duplicates);

    if(!dfs){
        return false;
    }

    for(int index = 0; index < territories.size(); index ++){
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
bool Map::DFS(Territory * territory, unordered_map<string, int> &duplicate){
    territory->visited = true;

    if( duplicate.find(territory->name) == duplicate.end()){
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

// Destructor for Map object
Map::~Map() {
    continents.clear();
    territories.clear();
}

// Stream insertion operator for Map object
ostream& operator<<(ostream& out, Map& map){
    out<< "All territories: " << endl;
    for(int i = 0; i < map.territories.size(); i ++){
        out << map.territories.at(i)->name << endl;
    }
    return out;
}

// Assignment operator for Map object
Map Map::operator=(const Map& map){
    this->territories = map.territories;
    this->continents = map.continents;

    return *this;
}

//
// Maploader implementation
//

// Constructor for Maploader object
Maploader::Maploader(string filename) {
    this->filename = filename;
}

string Maploader::getFileName() {
    return filename;
}

// Destructor for maploader
Maploader::~Maploader() {
}

// Stream insertion operator for Maploader object
ostream& operator<<(ostream& out, Maploader& maploader){
    out<< "Maploader filename: " << maploader.getFileName() << endl;

    return out;
}

// Assignment operator for Maploader object
Maploader Maploader::operator=(const Maploader& maploader){
    this->filename = maploader.filename;
}

// Copy constructor for Maploader object
Maploader::Maploader(const Maploader &maploader) {
    this->filename = maploader.filename;
}

// Loads the map and returns a reference to a Map object
Map& Maploader::load() {

    ifstream infile(filename);

    vector<Territory *> territoriesVector;
    vector<vector<Territory*>> continentsVector;

    string line;
    bool continents = false;
    bool territories = false;
    bool edges = false;

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
        } else if(continents){
            vector<Territory *> countries;
            continentsVector.push_back(countries);
        }
    }

    cout << "Loaded map" << endl;

    Map map = {continentsVector, territoriesVector};

    return map;
}