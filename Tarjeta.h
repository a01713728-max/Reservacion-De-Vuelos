#pragma once
#include <string>

class Tarjeta {
public:
    static bool validarLuhn(const std::string& numeroTarjeta);
};



