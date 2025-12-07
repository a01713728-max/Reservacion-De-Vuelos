#include "Vuelo.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

bool Vuelo::RegistrarVuelo(const string& fecha,
    const string& hora,
    const string& origen,
    const string& destino,
    const string& noAvion)
{
    // Calcular ID
    int nuevoId = 1;
    ifstream temp("vuelos.txt");
    if (temp.is_open()) {
        string linea;
        while (getline(temp, linea)) {
            if (!linea.empty() && linea.find("ID ") != 0) {
                stringstream ss(linea);
                ss >> nuevoId;
                nuevoId++;
            }
        }
        temp.close();
    }

    // Guardar con espacios (NO comas)
    ofstream archivo("vuelos.txt", ios::app);
    if (!archivo.is_open()) return false;

    if (archivo.tellp() == 0) {
        archivo << "ID Fecha Hora Origen Destino NoAvion\n";
    }

    archivo << nuevoId << " "
        << fecha << " "
        << hora << " "
        << origen << " "
        << destino << " "
        << noAvion << "\n";

    archivo.close();
    cout << "Vuelo registrado correctamente.\n";
    return true;
}

vector<Vuelo> Vuelo::ObtenerTodosLosVuelos()
{
    vector<Vuelo> lista;
    ifstream archivo("vuelos.txt");
    if (!archivo.is_open()) return lista;

    string linea;
    bool primera = true;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        if (primera && linea.find("ID ") == 0) {
            primera = false;
            continue;
        }

        stringstream ss(linea);
        int id;
        string fecha, hora, origen, destino, noAvion;

        if (ss >> id >> fecha >> hora >> origen >> destino >> noAvion) {
            lista.emplace_back(id, fecha, hora, origen, destino, noAvion);
        }
    }
    archivo.close();
    return lista;
}

void Vuelo::Mostrar() const
{
    cout << "[" << id << "]\n";
    cout << "  Avion     : " << noAvion << "\n";
    cout << "  Origen    : " << origen << "\n";
    cout << "  Destino   : " << destino << "\n";
    cout << "  Fecha     : " << fecha << "\n";
    cout << "  Hora      : " << hora << "\n";
    cout << "--------------------------------\n";
}