#include "Tarjeta.h"
#include <cctype>
#include <string>

bool Tarjeta::validarLuhn(const std::string& numeroTarjeta) {

    int suma = 0;
    bool alternar = false;

    // Recorremos del final al inicio
    for (int i = (int)numeroTarjeta.length() - 1; i >= 0; i--) {

        if (!isdigit(numeroTarjeta[i]))
            return false; // obligatorio que sean números

        int digito = numeroTarjeta[i] - '0';

        if (alternar) {
            digito *= 2;
            if (digito > 9) digito -= 9;
        }

        suma += digito;
        alternar = !alternar;
    }

    return (suma % 10 == 0);
}


