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
    if(archivoRelaciones) {
        string nombre, encabezados, separador;
        while(archivoRelaciones >> nombre >> separador >> encabezados) {
            vector<string> headers;
            string headerActual;
            for (int i = 0; i < encabezados.size(); i++) {
                if (encabezados[i] == ',') {
                    headers.push_back(headerActual);
                    headerActual = "";
                } else {
                    headerActual += encabezados[i];
                }
            }
            headers.push_back(headerActual);
            Relacion r(nombre, headers);

            ifstream archivoTuplas(nombre + ".txt", ios::in);
            if (archivoTuplas) {
                string auxiliar;
                while (archivoTuplas >> auxiliar) {
                    vector<string> attributes, aux_attributes;
                    string att;
                    for (int i = 0; i < auxiliar.size(); i++) {
                        if (auxiliar[i] == ',') {
                            attributes.push_back(att);
                            att = "";
                        } else {
                            att += auxiliar[i];
                        }
                    }
                    attributes.push_back(att);
                    for (int i = 1; i < attributes.size(); i++) {
                        aux_attributes.push_back(attributes[i]);
                    }
                    
                    Tupla t(stoi(attributes[0]), aux_attributes);
                    r.setTupla(t);
                }
            }

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
}

void verEstado(int posicion) {
    Relacion r = relaciones[posicion - 1];
    int n_headers = r.getEncabezados().size();
    
    cout << "\nEstado de la relación " << r.getNombre() << ":\n\n";
    for (int i = 0; i < n_headers; i++) {
        cout << r.getEncabezados()[i];
        if (r.getEncabezados()[i] == "ID") {
            cout << "\t";
        } else {
            cout << "\t\t";
        }
    }
    cout << "\n";

    for (int i = 0; i < r.getTuplas().size(); i++) {
        cout << r.getTuplas()[i].toString();
        cout << endl;
    }
}

void listarRelaciones(bool ask) {
    ifstream archivoRelaciones("Relaciones.txt", ios::in);
    if(!archivoRelaciones) {
        cout << "No hay ninguna relación hasta el momento.\n";
    } else {
        cout << "----- Lista de Relaciones en Memoria -----\n";
        int contador = 1;
        string nombre, encabezados, separador;
        while(archivoRelaciones >> nombre >> separador >> encabezados) {
            cout << contador << ". " << nombre << endl;
            contador++;
        }
        cout << endl;

        if (ask) {
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
}

void agregarTupla() {
    listarRelaciones(false);
    int posicion_relacion;
    cout << "¿En qué relación desea ingresar la tupla?: ";
    cin >> posicion_relacion;
    Relacion r = relaciones[posicion_relacion - 1];
    
    vector<string> atributos;
    srand(time(NULL));
    int random = 1000 + rand()%(9998);
    cout << "\nAgregando tupla a la relación " + r.getNombre() << endl;
    for (int i = 1; i < r.getEncabezados().size(); i++) {
        string att;
        cout << r.getEncabezados()[i] << ": ";
        cin >> att;
        atributos.push_back(att);
    }
    Tupla tupla(random, atributos);
    r.setTupla(tupla);

    ofstream archivoActual(r.getNombre() + ".txt", ios::app);
    archivoActual << random << ",";
    for (int i = 0; i < atributos.size(); i++) {
        if (i == atributos.size() - 1) {
            archivoActual << atributos[i] + "\n";
        } else {
            archivoActual << atributos[i] + ",";
        }
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
                listarRelaciones(true);
            } break;

            case 3: {
                agregarTupla();
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