#include "Cliente.h"
#include "Vuelo.h"
#include "Reservacion.h"
#include "Tarjeta.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <windows.h>
#include <limits> 

using namespace std;

// Función para imprimir un boleto en pantalla y guardarlo en un archivo
void imprimirBoleto(const Reservacion& r, const Vuelo& v) {
    // Generar contenido del boleto
    std::string contenido;
    contenido += "-------------------------------\n";
    contenido += "Fecha : " + v.getFecha() + "\n";
    contenido += "Hora : " + v.getHora() + "\n";
    contenido += "Origen : " + v.getOrigen() + "\n";
    contenido += "Destino : " + v.getDestino() + "\n";
    contenido += "No. Avion : " + v.getNoAvion() + "\n";
    contenido += "Estado : " + std::string(r.pagado ? "Pagado" : "Pendiente") + "\n";
    contenido += "Asientos: ";
    for (int j = 0; j < 10; ++j) {
        if (r.asientos[j] == '1') contenido += std::to_string(j + 1) + " ";
    }
    contenido += "\n-------------------------------\n\n";

    // Imprimir en pantalla
    cout << contenido;

    // Guardar en archivo
    std::ofstream archivo("boleto_" + std::to_string(r.idUsuario) + "_" + std::to_string(r.idVuelo) + ".txt");
    if (archivo.is_open()) {
        archivo << contenido;
        archivo.close();
        cout << "Boleto guardado en archivo .txt exitosamente.\n";
    }
    else {
        cout << "Error al guardar el boleto en archivo.\n";
    }
}

// Obtener vuelo por ID
Vuelo Vuelo::ObtenerVueloPorId(int idVuelo) {
    for (const auto& v : ObtenerTodosLosVuelos()) {
        if (v.getId() == idVuelo)
            return v;
    }
    return Vuelo();
}

// ---------------------- MÉTODOS DEL CLIENTE ----------------------

void Cliente::ReservarVuelo(int idUsuario) {
    vector<Vuelo> vuelos = Vuelo::ObtenerTodosLosVuelos();
    if (vuelos.empty()) {
        cout << "No hay vuelos registrados.\n";
        return;
    }

    cout << "=== VUELOS DISPONIBLES ===\n";
    for (auto& v : vuelos) {
        string combinada = Reservacion::asientosCombinados(v.getId());
        int libres = count(combinada.begin(), combinada.end(), '0');
        if (libres > 0) v.Mostrar();
    }

    int eleccion;
    cout << "Escribe el número del vuelo que deseas seleccionar: ";
    cin >> eleccion;
    cin.ignore();

    auto it = find_if(vuelos.begin(), vuelos.end(), [eleccion](Vuelo& v) { return v.getId() == eleccion; });
    if (it == vuelos.end()) {
        cout << "Número de vuelo no válido.\n";
        return;
    }

    Vuelo vueloSeleccionado = *it;
    string asientos = Reservacion::asientosCombinados(vueloSeleccionado.getId());

    int asientoElegido = 0;
    while (true) {
        cout << "Asientos disponibles:\n";
        for (int i = 0; i < 10; ++i) {
            if (asientos[i] == '0')
                cout << "\033[32;107m[" << i + 1 << "]\033[0m ";
            else
                cout << "\033[31;107m[" << i + 1 << "]\033[0m ";
        }
        cout << "\nSeleccione el número de asiento (1-10): ";
        cin >> asientoElegido;
        cin.ignore();
        if (asientoElegido < 1 || asientoElegido > 10) {
            cout << "Número de asiento inválido. Intenta de nuevo.\n";
            continue;
        }
        if (asientos[asientoElegido - 1] == '1') {
            cout << "Ese asiento ya está ocupado. Elige otro.\n";
            continue;
        }
        break;
    }

    // Crear reservación
    Reservacion r(idUsuario, vueloSeleccionado.getId());
    r.asientos[asientoElegido - 1] = '1';
    if (r.guardar()) {
        cout << "¡Asiento reservado exitosamente!\n";
    }
    else {
        cout << "Error al guardar la reservación.\n";
    }
    system("color F9");
}

void Cliente::PagarVuelos(int idUsuario) {
    vector<Reservacion> todas = Reservacion::obtenerTodas();
    vector<Reservacion> pendientes;

    for (const auto& r : todas) {
        if (r.idUsuario == idUsuario && !r.pagado) {
            pendientes.push_back(r);
        }
    }

    if (pendientes.empty()) {
        cout << "No tienes vuelos pendientes de pago.\n";
        return;
    }

    cout << "     VUELOS PENDIENTES DE PAGO\n\n";

    int numeroReserva = 1;
    for (const auto& r : pendientes) {
        cout << "Reservacion No. " << numeroReserva++ << endl;
        vector<Vuelo> vuelos = Vuelo::ObtenerTodosLosVuelos();
        for (const auto& v : vuelos) {
            if (v.getId() == r.idVuelo) {
                v.Mostrar();
                break;
            }
        }
        cout << " Asiento(s) reservado(s): ";
        for (int j = 0; j < 10; ++j) {
            if (r.asientos[j] == '1') cout << (j + 1) << " ";
        }
        cout << "\n--------------------------------\n";
    }

    int opcion;
    cout << "Escribe el numero de la RESERVACION que deseas pagar (1-"
        << pendientes.size() << ", 0 para cancelar): ";
    cin >> opcion;
    cin.ignore();

    if (opcion < 1 || (size_t)opcion > pendientes.size()) {
        cout << "Pago cancelado.\n";
        return;
    }

    // Validación de tarjeta
    string tarjeta;
    cout << "\n=== PAGO CON TARJETA ===\n";
    cout << "Ingresa tu numero de tarjeta (sin espacios): ";
    getline(cin, tarjeta);

    while (!Tarjeta::validarLuhn(tarjeta)) {
        cout << "\n Tarjeta invalida. Intenta nuevamente.\n";
        cout << "Ingresa tu numero de tarjeta (sin espacios): ";
        getline(cin, tarjeta);
    }

    cout << "Tarjeta valida. Procesando pago...\n";
    Sleep(1000);

    // Realizar pago
    Reservacion seleccionada = pendientes[opcion - 1];
    if (Reservacion::pagarReservacionesIndividual(idUsuario, seleccionada.idVuelo, seleccionada.asientos)) {
        cout << "Reservacion pagada exitosamente.\n";

        // Imprimir boleto inmediatamente en pantalla y guardar en archivo
        Vuelo v = Vuelo::ObtenerVueloPorId(seleccionada.idVuelo);
        imprimirBoleto(seleccionada, v);
    }
    else {
        cout << "Error al procesar el pago.\n";
    }
}

void Cliente::ImprimirBoletos(int idUsuario) {
    vector<Reservacion> todas = Reservacion::obtenerTodas();
    bool tieneBoletos = false;

    for (const auto& r : todas) {
        if (r.idUsuario == idUsuario && r.pagado) {
            Vuelo v = Vuelo::ObtenerVueloPorId(r.idVuelo);
            imprimirBoleto(r, v);
            tieneBoletos = true;
        }
    }

    if (!tieneBoletos) {
        cout << "No tienes boletos pagados para mostrar.\n";
    }
}

