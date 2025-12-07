#include "Reservacion.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

using namespace std;

// Guardar la reservación en archivo
bool Reservacion::guardar() {
    ofstream archivo("reservaciones.txt", ios::app);
    if (!archivo.is_open()) return false;

    archivo << idUsuario << " " << idVuelo << " " << asientos << " " << pagado << "\n";
    archivo.close();
    return true;
}

// Obtener todas las reservaciones desde archivo
vector<Reservacion> Reservacion::obtenerTodas() {
    vector<Reservacion> lista;
    ifstream archivo("reservaciones.txt");
    if (!archivo.is_open()) return lista;

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        stringstream ss(linea);
        int uid, vid, pag;
        string as;
        ss >> uid >> vid >> as >> pag;

        lista.push_back(Reservacion(uid, vid, as, pag != 0));
    }

    archivo.close();
    return lista;
}

// Obtener la cadena de asientos combinada de un vuelo
string Reservacion::asientosCombinados(int idVuelo) {
    string combinada = "0000000000";
    vector<Reservacion> todas = obtenerTodas();

    for (auto& r : todas) {
        if (r.idVuelo == idVuelo) {
            for (int i = 0; i < 10; ++i) {
                if (r.asientos[i] == '1') combinada[i] = '1';
            }
        }
    }
    return combinada;
}

// Marcar todas las reservaciones de un usuario como pagadas
void Reservacion::pagarReservaciones(int idUsuario) {
    vector<Reservacion> todas = obtenerTodas();
    ofstream archivo("reservaciones.txt");
    if (!archivo.is_open()) return;

    for (auto& r : todas) {
        if (r.idUsuario == idUsuario) r.pagado = true;
        archivo << r.idUsuario << " " << r.idVuelo << " " << r.asientos << " " << r.pagado << "\n";
    }

    archivo.close();
}

bool Reservacion::pagarReservacionesIndividual(int idUsuario, int idVuelo, const std::string& asientos)
{
    vector<Reservacion> todas = obtenerTodas();
    bool encontrado = false;  // variable para saber si encontramos la reservación

    ofstream archivo("reservaciones.txt");
    if (!archivo.is_open()) return false;

    for (auto& r : todas) {
        if (r.idUsuario == idUsuario &&
            r.idVuelo == idVuelo &&
            r.asientos == asientos) {
            r.pagado = true;
            encontrado = true;  // marcamos que sí se encontró y se pagó
        }
        archivo << r.idUsuario << " " << r.idVuelo << " "
            << r.asientos << " " << r.pagado << "\n";
    }

    archivo.close();
    return encontrado;  // true si se pagó, false si no
}

