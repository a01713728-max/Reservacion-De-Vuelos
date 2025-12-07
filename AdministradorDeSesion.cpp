#include "AdministradorDeSesion.h"
#include <iostream>
#include "Usuario.h"
#include <string>
#include <limits>
using namespace std;

/*bool AdministradorDeSesion::RegistrarUsuario(string nombre, string correo, string password)
{
    vector<shared_ptr<Usuario>> usuarios = ObtenerUsuarios();
    bool admin;
    // Generar ID
    id = usuarios.empty() ? 1 : usuarios.back()->getId() + 1;

    ofstream outputFile("usuarios.txt", ios::app);

    if (!outputFile.is_open())
        return false;
    cout << "¿El usuario sera Administrador(1/0)?";
    cin >> admin;
    if (admin) {
        outputFile << id << " " << nombre << " " << correo << " " << password << " " << 1 << endl;
    }
    else {
        outputFile << id << " " << nombre << " " << correo << " " << password << " " << 0 << endl;
    };


    outputFile.close();

    cout << "Usuario registrado exitosamente." << endl;
    return true;
}*/