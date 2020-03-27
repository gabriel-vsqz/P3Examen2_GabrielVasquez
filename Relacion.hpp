#pragma once

#include <vector>
#include <string>
#include "Tupla.hpp"

using namespace std;

class Relacion {
    private:
        vector<string> encabezados;
        vector<Tupla> tuplas;
        string nombre;
    public:
        Relacion();
        Relacion(string, vector<string>);
        string getNombre();
        vector<string> getEncabezados();
        void setTupla(Tupla t);
        vector<Tupla> getTuplas();
};

Relacion :: Relacion() {
}

Relacion :: Relacion (string name, vector<string> headers) {
    nombre = name;
    encabezados = headers;
}

string Relacion :: getNombre() {
    return nombre;
}

vector<string> Relacion :: getEncabezados() {
    return encabezados;
}

void Relacion :: setTupla(Tupla nuevo) {
    tuplas.push_back(nuevo);
}

vector<Tupla> Relacion :: getTuplas() {
    return tuplas;
}