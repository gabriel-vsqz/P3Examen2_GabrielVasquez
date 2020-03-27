#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <time.h>

#include "Tupla.hpp"
#include "Relacion.hpp"

vector<Relacion> relaciones;

void cargarRelaciones() {
    ifstream archivoRelaciones("Relaciones.txt", ios::in);
    if(!archivoRelaciones) {
        cout << "No hay ninguna relación hasta el momento.\n";
    } else {
        string nombre, encabezados, separador;
        while(archivoRelaciones >> nombre >> separador >> encabezados) {
            vector<string> headers;
            string headerActual;
            for (int i = 0; i < encabezados.length(); i++) {
                if (encabezados[i] == ',') {
                    headers.push_back(headerActual);
                    headerActual = "";
                } else {
                    headerActual += encabezados[i];
                }
            }
            Relacion r(nombre, headers);
            relaciones.push_back(r);
        }
    }
}

void crearRelacion() {
    cout << "----- Datos de la Relación -----\n";
    vector<string> encabezados;
    string nombre, encabezado;
    int n_encabezados;
    cout << "Nombre de la relación: ";
    cin >> nombre;
    cout << "¿Cúantos encabezados desea que su relación tenga?: ";
    cin >> n_encabezados;
    encabezados.push_back("ID");
    for (int i = 0; i < n_encabezados; i++) {
        cout << ": ";
        cin >> encabezado;
        encabezados.push_back(encabezado);
    }
    
    Relacion relacion(nombre, encabezados);
    relaciones.push_back(relacion);
    
    ofstream archivoRelaciones("Relaciones.txt", ios::app);
    archivoRelaciones << relacion.getNombre() + " - ";
    for (int i = 0; i < encabezados.size(); i++) {
        if (i == encabezados.size() - 1) {
            archivoRelaciones << encabezados[i] + "\n";   
        } else {
            archivoRelaciones << encabezados[i] + ",";
        }
    }

    ofstream nuevaRelacion(nombre + ".txt", ios::out);
    for (int i = 0; i < encabezados.size(); i++) {
        nuevaRelacion << encabezados[i] << "\t";
    } nuevaRelacion << "\n";
}

void verEstado(int posicion) {
    
}

void listarRelaciones() {
    ifstream archivoRelaciones("Relaciones.txt", ios::in);
    if(!archivoRelaciones) {
        cout << "No hay ninguna relación hasta el momento.\n";
    } else {
        cout << "----- Lista de Relaciones en Memoria -----\n";
        int contador = 1;
        string nombre, encabezados, separador;
        while(archivoRelaciones >> nombre >> separador >> encabezados) {
            cout << contador << ". " << nombre << endl;//Nombre: " << nombre << "\t" << " Encabezados: " << encabezados << endl;
            contador++;
        }
        cout << endl;

        int posicion_relacion;
        cout << "¿De qué relación desea ver el estado?: ";
        cin >> posicion_relacion;
        while(posicion_relacion < 1 || posicion_relacion > relaciones.size()) {
            cout << "El número que ingresó no corresponde a las relaciones mostradas en la lista.\n";
            cout << "Intente de nuevo: ";
            cin >> posicion_relacion;
        }
        verEstado(posicion_relacion);
    }
}

int main() {
    cargarRelaciones();
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