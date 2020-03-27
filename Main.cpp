#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "Tupla.hpp"
#include "Relacion.hpp"

vector<Relacion> relaciones;

void crearRelacion() {
    cout << "----- Datos de la Relación -----\n";
    vector<string> encabezados;
    string nombre, encabezado;
    int n_encabezados;
    cout << "Nombre de la relación: ";
    cin >> nombre;
    cout << "¿Cúantos encabezados desea que su relación tenga?: ";
    cin >> n_encabezados;
    for (int i = 0; i < n_encabezados; i++) {
        cout << ": ";
        cin >> encabezado;
        encabezados.push_back(encabezado);
    }
    
    Relacion relacion(nombre, encabezados);
    relaciones.push_back(relacion);
    
    ofstream archivoRelaciones("Relaciones.txt", ios::app);
    archivoRelaciones << relacion.getNombre() + ": ";
    for (size_t i = 0; i < encabezados.size(); i++) {
        if (i == encabezados.size() - 1) {
            archivoRelaciones << encabezados[i] + "\n";   
        } else {
            archivoRelaciones << encabezados[i] + ",";
        }
    }
}

void listarRelaciones() {

}

int main() {
    bool pass = true;
    int opcion;
    cout << "\n---------- Gestor de Base de Datos Relacional ----------\n\n";
    while (pass) {
        cout << "---------- Menú ----------\n1. Crear Relación\n2. Ver Relaciones\n3. Insertar Tupla\n4. Salir\n: ";
        cin >> opcion;
        cout << endl;
        switch (opcion) {
            case 1: {
                crearRelacion();
            } break;

            case 2: {
                listarRelaciones();
            } break;

            case 3: {
            } break;

            case 4: {
                pass = false;
            } break;

            default: {
                cout << "Debe elegir entre una de las opciones que se le presentan.\n";
            }
        }
        cout << endl;
    }
}