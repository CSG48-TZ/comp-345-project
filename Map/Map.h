//
// Created by Salman Hussain Ali on 02/02/2023.
//

#include <iostream>
#include <list>
#include <vector>

using namespace std;

#ifndef COMP345_MAP_H
#define COMP345_MAP_H
class Territory{// TODO- Add a copy constructor, assignment operator, and stream insertion operator
public:
    string name;
    int continent;
    Player * owner;

    bool visited;

    int numArmies;

    vector<Territory *> edges;

    Territory(string name, int continent, int number1, int number2);

    void changeOwner(Player * newOwner);

    void addEdge(Territory * adjacent);

    void addArmies(int num);

private:
    int number1;
    int number2;
};

// TODO - Remove when Part 2 is uploaded
class Player{};

class Map{ // TODO- Add a copy constructor, assignment operator, and stream insertion operator
public:
    bool validate(); // TODO - Implement in Map.cpp

    vector<vector<Territory *>> continents; // Continents are by index. Each index of the vector contains a vector of
                                            // territories belonging to that continent

    vector<Territory *> territories; // Cumulative list of all the territories
    void addTerritory(Territory * territory);

    Map(vector<vector<Territory *>> * continents, vector<Territory *> territories);
};

class Maploader{// TODO- Add a copy constructor, assignment operator, and stream insertion operator

};
#endif //COMP345_MAP_H
