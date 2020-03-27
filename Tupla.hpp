#pragma once

#include <vector>
#include <string>

using namespace std;

class Tupla {
    private:
        int ID;
        vector<string> atributos;
    public:
        Tupla();
        Tupla(int, vector<string>);
};

Tupla :: Tupla() {
}

Tupla :: Tupla(int id, vector<string> att) {
    ID = id;
    atributos = att;
}