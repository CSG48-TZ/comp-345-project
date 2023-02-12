//
// Created by Salman Hussain Ali on 12/02/2023.
//

#include "Map.h"

int main(){
    Maploader maploader = {"../test.txt"};

    Map map = maploader.load();

    cout << "Entering loop " << endl;

    for(int i = 0; i < map.territories.size(); i ++){
        cout << i << "Name: "<< map.territories.at(i)->name << endl;
        //cout << map.territories.at(i)->name << endl;
    }

    if(map.validate()) {
        cout << "Map is valid" << endl;
    } else {
        cout << "Invalid" << endl;
    }
    return 0;
}
