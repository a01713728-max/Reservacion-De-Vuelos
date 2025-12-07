#pragma once
#include <string>
#include <vector>
#include <memory>

class Usuario
{
private:
    int id;
    std::string nombre;
    std::string correo;
    std::string password;

public:
    // Constructores
    Usuario() : id(0) {}

    Usuario(int id, std::string n, std::string c, std::string p)
        : id(id), nombre(n), correo(c), password(p) {
    }

    // Getters
    int getId() const;//funcion para obtener el id del usuario
    int getId_2() const;
    std::string getCorreo() const;//funcion para obtener el correo del usuario

    // Métodos
    int IniciarSesion();
    bool RegistrarUsuario(std::string nombre, std::string correo, std::string password);
    bool ValidarInicioSesion(std::string c, std::string p) const {
        return  (correo == c && password == p);//en esta parte podemos validar si el correo y la contraseña coinciden con los almacenados, sin embargo ahora no lo queremos que lo toque el usuario
    }

    std::vector<std::shared_ptr<Usuario>> ObtenerUsuarios();
};