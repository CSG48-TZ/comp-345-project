//
// Created by Salman Hussain Ali on 02/02/2023.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>

using namespace std;

#ifndef COMP345_MAP_H
#define COMP345_MAP_H
class Territory{// TODO- Add a copy constructor
public:
    string name;
    int id;
    int continent;
    Player * owner;
    bool visited; // Created for validate()
    int numArmies;
    vector<Territory *> edges;

    Territory(int id, string name, int continent, int number1, int number2);
    void changeOwner(Player * newOwner);
    void addEdge(Territory * adjacent);
    void addArmies(int num);
    ~Territory();
    ostream& operator<<(ostream& out, const Territory& territory);
    Territory operator=(const Territory& territory);
    Territory(const Territory& territory);

private:
    int number1;
    int number2;
};

// TODO - Remove when Part 2 is uploaded
class Player{};

class Map{ // TODO- Add a copy constructor, assignment operator, and stream insertion operator
public:
    vector<vector<Territory *>> continents; // Continents are by index. Each index of the vector contains a vector of
                                            // territories belonging to that continent

    vector<Territory *> territories; // Cumulative list of all the territories

    bool validate();
    void addTerritory(Territory * territory);
    Map(vector<vector<Territory *>> * continents, vector<Territory *> territories);
    Map(const Map& map);
    bool DFS(Territory * territory, unordered_map<string, int> * duplicate);
    int continentDFS(Territory * territory);
    ~Map();
    ostream& operator<<(ostream& out, const Map& map);
    Map operator=(const Map& map);
};

class Maploader{// TODO- Add a copy constructor, assignment operator, and stream insertion operator
public:
    string filename;
    Maploader(string filename);

    Map * load();

    ~Maploader();

    ostream& operator<<(ostream& out, const Maploader& maploader);

    Maploader operator=(const Maploader& maploader);

    Maploader(const Maploader& maploader);
};
#endif //COMP345_MAP_H
