#include "Menu.h"
#include <iostream>
#include <string>
#include <limits>
#include <chrono>
#include <thread>
#include "Vuelo.h"
#include "Cliente.h"
using namespace std;

// -------------------- Pantalla de inicio --------------------
void Menu::MostrarPantallaInicio() const
{
    system("mode con cols=200 lines=80"); // Ajusta tamaño de consola
    system("color F9"); // Fondo blanco con texto azul

    cout <<
        R"(                                                                                                                        
                        


                                                                                                 
                                                                                                                         
                             ##              ##                                                                        
                         ####                  ####                                                                    
                         ####                  ####                                                                    
                       ##                    ##    ##                                                                  
                       ####    ######..  ######  ####                                                                  
                     ##            ########      ##  ##      ##                    ++++##++                          
                       mm    ##    ########                ##  ##  ##########--####::  ##  ######  ####..              
                         ##    ####    ####      ##  MM    ##  ##  ##  ####  --    ##  ##  ##  ##  MM                  
                           ##    ##      ##      --MM    MM######  ##    ##    ++  ##  ##  ##      ##                  
                       ##  ##                            ##      ######@@##    ####    ##    ####  ####               
                   @@##  @@                        ##                                                                  
                     ##      ##              ##          ######  ######    @@##  ####--####  ##########               
                           ##mm  ##      ##  ####        ######  ######    ####  ####..####  --##    ####             
                             ####mm##  MM######                                                                        
                                   ##  ##                                                                                                                                                                                                    
)" << endl;

    this_thread::sleep_for(chrono::seconds(5)); // Pausa de 4 segundos
    system("color 07");   // Restablece colores
    system("cls");        // Limpia la pantalla
}

// -------------------- Menú administrador --------------------
void Menu::MostrarMenuAdmin() {
    int opcion;
    Usuario usuario;
    string nombre;
    string correo;
    string password;
    do
    {
        cout << "-----------------------" << endl;
        cout << "| 1.Registrar Usuario |" << endl;
        cout << "|---------------------|" << endl;
        cout << "| 2.Registra Vuelos   |" << endl;
        cout << "|---------------------|" << endl;
        cout << "| 3.Salir             |" << endl;
        cout << "-----------------------" << endl;
        cout << "Seleccione una opcion: " << endl;

        if (!(cin >> opcion)) {
            cout << "Entrada invalida. Limpiando el buffer." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcion = 0;
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion)
        {
        case 1:
            cout << "nombre" << endl;
            cin >> nombre;
            cout << "correo" << endl;
            cin >> correo;
            cout << "password" << endl;
            cin >> password;
            usuario.RegistrarUsuario(nombre, correo, password);
            break;
        case 2: {
            string fecha, hora, origen, destino, noAvion;

            cout << "\n    REGISTRAR NUEVO VUELO \n";
            cout << "Fecha (ej. 15/12/2025): ";
            getline(cin, fecha);
            cout << "Hora (ej. 14:30): ";
            getline(cin, hora);
            cout << "Origen: ";
            getline(cin, origen);
            cout << "Destino: ";
            getline(cin, destino);
            cout << "No. Avion (ej. Boeing-737): ";
            getline(cin, noAvion);

            Vuelo::RegistrarVuelo(fecha, hora, origen, destino, noAvion);

            cout << "\nPresiona ENTER para continuar...";
            cin.get();
            break;
        }

        default:
            cout << "Saliste con exito" << endl;
            opcion = 3;
            break;
        };
    } while (opcion != 3);
};

// -------------------- Menú principal --------------------
void Menu::MostrarMenuPrincipal() {
    Usuario usuarioActual;
    int opcion;

    do {
        system("color F9");
        cout << "           AEROTEC" << endl;
        cout << "------------------------------" << endl;
        cout << "| 1. Iniciar Sesion          |" << endl;
        cout << "|----------------------------|" << endl;
        cout << "| 2. Salir de la Aplicacion  |" << endl;
        cout << "------------------------------" << endl;
        cout << "Seleccione una opcion: " ;

        if (!(cin >> opcion)) {
            cout << "Entrada invalida. Limpiando el buffer." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcion = 0;
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
        case 1: {
            cout << "\n   INICIAR SESION" << endl;
            int respuesta;
            respuesta = usuarioActual.IniciarSesion();
            if (respuesta == 1) {
                int idUsuario = usuarioActual.getId(); // obtener ID del usuario
                MostrarMenu(idUsuario); // pasar el id al menú
            }
            else if (respuesta == 3) {
                MostrarMenuAdmin();
            };
            break;
        }
        default:
            cout << "\nGracias por usar el sistema. Saliendo..." << endl;
            opcion = 2;
            break;
        }

    } while (opcion != 2);
};

// -------------------- Menú de usuario --------------------
void Menu::MostrarMenu(int idUsuario) const
{
    int opcionMenu;
    do {
        cout << "\n";
        cout << " MENU PRINCIPAL DEL CLIENTE \n";
        cout << "---------------------------\n";
        cout << "| 1 - Reservar vuelo      |\n";
        cout << "|-------------------------|" << endl;
        cout << "| 2 - Pagar boleto        |\n";
        cout << "|-------------------------|" << endl;
        cout << "| 3 - Salir               |\n";
        cout << "---------------------------" << endl;

        cout << "Seleccione una opcion: ";
        cin >> opcionMenu;

        switch (opcionMenu)
        {
        case 1: {
            system("cls");
            Cliente clienteActual;
            clienteActual.ReservarVuelo(idUsuario);  // ? Añade idUsuario
            cout << "Presiona ENTER para volver...";
            cin.ignore();
            cin.get();
            break;
        }
        case 2: {
            system("cls");
            Cliente clienteActual;
            clienteActual.PagarVuelos(idUsuario);    // ? Añade idUsuario
            cout << "Presiona ENTER para volver...";
            cin.ignore();
            cin.get();
            break;
        }
        case 3:
            cout << "\nSaliendo del menú..." << endl;
            break;
        default:
            cout << "\nOpción no valida. Intente de nuevo." << endl;
            cout << "Presione ENTER para continuar...";
            cin.ignore();
            cin.get();
            break;
        }
    } while (opcionMenu != 3);
};

