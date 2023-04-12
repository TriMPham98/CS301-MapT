//
// Created by Varick Erickson on 4/19/2021.
//

#include <iostream>
#include <vector>
#include "MapT.h"

int main(void) {
    MapT<int, string> map;

    map.Add(95381, "Turlock");
    map.Add(90210, "Beverly Hills");
    map.Add(60629, "Chicago");
    map.Add(79936, "El Paso");
    map.Add(90011, "Los Angeles");

    cout << map[95381] << endl;
    cout << map[90210] << endl << endl;

    // Replace
    cout << "After replacing the value for the key" << endl;
    map.Add(90210, "B. Hills");
    cout << map[90210] << endl;

    map.Remove(90210);

    try {
        cout << map[90210] << endl;
    }
    catch (KeyDoesNotExist err) {
        cout << 90210 << ": Key does not exist" << endl;
    }

    cout << endl;
    cout << "Keys" << endl;
    map.ResetIterator();
    for (int i = 0; i < map.Size(); i++) {
        cout << "Key:\t" << map.GetNextPair().first << endl;
    }

    cout << endl;
    cout << "Key/Value pairs" << endl;
    map.ResetIterator();
    for (int i = 0; i < map.Size(); i++) {
        pair<int, string> currPair = map.GetNextPair();
        cout << "Key/Value:\t" << currPair.first << "/" << currPair.second << endl;
    }

    return 0;
}