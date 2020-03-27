#pragma once

#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Tupla {
    private:
        int ID;
        vector<string> atributos;
    public:
        Tupla();
        Tupla(int, vector<string>);
        string toString();
};

Tupla :: Tupla() {
}

Tupla :: Tupla(int id, vector<string> att) {
    ID = id;
    atributos = att;
}

string Tupla :: toString() {
    string attributes;
    attributes += to_string(ID);
    attributes += "\t";
    for (size_t i = 0; i < atributos.size(); i++) {
        attributes += atributos[i];
        attributes += "\t\t";
    }
    return attributes;
}