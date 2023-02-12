//
// Created by Salman Hussain Ali on 02/02/2023.
//
#ifndef COMP345_MAP_H
#define COMP345_MAP_H

#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include "../Player/Player.h"

using namespace std;

class Player;

class Territory{// TODO- Add a copy constructor
public:
    string name;
    int id;
    int continent;
    Player* owner;
    bool visited; // Created for validate()
    int numArmies;
    vector<Territory *> edges;

    Territory(int id, string name, int continent, int number1, int number2);
    void changeOwner(Player* newOwner);
    void addEdge(Territory * adjacent);
    void addArmies(int num);
    ~Territory();
    Territory operator=(const Territory& territory);
    Territory(const Territory& territory);
    void setDuplicate();
    bool isDuplicate();

private:
    int number1;
    int number2;
    bool duplicate;
};

class Map{
public:
    vector<vector<Territory *>> continents; // Continents are by index. Each index of the vector contains a vector of
                                            // territories belonging to that continent

    vector<Territory *> territories; // Cumulative list of all the territories

    bool validate();
    void addTerritory(Territory * territory);
    Map(vector<vector<Territory *>>& continents, vector<Territory *>& territories);
    Map(const Map& map);
    ~Map();
    Map operator=(const Map& map);

private:
    void DFS(Territory * territory, unordered_map<string, int>& duplicate);
    int continentDFS(Territory * territory);
};

class Maploader{
public:
    Maploader(string filename);
    Map load();
    ~Maploader();
    void operator=(const Maploader& maploader);
    Maploader(const Maploader& maploader);
    string getFileName();

private:
    string filename;
};
#endif //COMP345_MAP_H
