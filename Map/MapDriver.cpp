//
// Created by Salman Hussain Ali on 12/02/2023.
//

#include "Map.h"

int main(){
    Maploader maploader = {"../europe.txt"};

    Map map = maploader.load();

    for(int i = 0; i < map.territories.size(); i ++){
        cout << map.territories.at(i) << endl;
    }

    if(map.validate()) {
        cout << "Map is valid" << endl;
    } else {
        cout << "Invalid" << endl;
    }
    return 0;
}
