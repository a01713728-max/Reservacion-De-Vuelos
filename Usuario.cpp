#include "Usuario.h"
#include "AdministradorDeSesion.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

int Usuario::IniciarSesion()
{
    AdministradorDeSesion adminSesion;
    int idUsuario = 0;
    string  idUsuarioString;

    cout << "Correo: ";
    cin >> correo;
    cout << "Password: ";
    cin >> password;

    vector<shared_ptr<Usuario>> usuarios = ObtenerUsuarios();

    // Validar credenciales
    for (const auto& usuario : usuarios)
    {
        if (usuario->ValidarInicioSesion(correo, password))
        {
            idUsuario = usuario->getId();

            break;
        }
    }

    // Si no existe, se detiene
    if (idUsuario == 0)
    {
        cout << "\nCredenciales invalidas.\n";
        return 0;
    }

    // Registrar sesión
    if (adminSesion.login(correo, password, usuarios))
    {
        cout << "\nInicio de sesion exitoso para: " << correo << "\n";
        idUsuarioString = to_string(idUsuario);
        if (idUsuarioString[0] == '2') {
            return 3;
        };

        return 1;
    }

    cout << "\nError al iniciar sesion.\n";
    return 0;
}

int Usuario::getId() const
{


    return id;
}
int Usuario::getId_2() const
{

    string s = to_string(id);

    int segundo = s[1] - '0';
    return segundo;
}

string Usuario::getCorreo() const
{
    return correo;
}

bool Usuario::RegistrarUsuario(string nombre, string correo, string password)
{
    vector<shared_ptr<Usuario>> usuarios = ObtenerUsuarios();
    bool admin;
    // Generar ID
    id = usuarios.empty() ? 1 : usuarios.back()->getId_2() + 1;

    ofstream outputFile("usuarios.txt", ios::app);

    if (!outputFile.is_open())
        return false;
    cout << "¿El usuario sera Administrador(1/0)?";
    cin >> admin;
    if (admin) {
        outputFile << 2 << id << " " << nombre << " " << correo << " " << password << endl;
    }
    else {
        outputFile << 1 << id << " " << nombre << " " << correo << " " << password << endl;
    };


    outputFile.close();

    cout << "Usuario registrado exitosamente." << endl;
    return true;
}

vector<shared_ptr<Usuario>> Usuario::ObtenerUsuarios()
{
    vector<shared_ptr<Usuario>> usuariosReg;
    ifstream inputFile("usuarios.txt");

    if (!inputFile.is_open())
        return usuariosReg;

    string line;
    while (getline(inputFile, line))
    {
        stringstream ss(line);
        vector<string> datos;
        string palabra;

        while (ss >> palabra)
            datos.push_back(palabra);

        if (datos.size() == 4)
        {
            usuariosReg.push_back(make_shared<Usuario>(
                stoi(datos[0]), datos[1], datos[2], datos[3]
            ));
        }
    }

    return usuariosReg;
}