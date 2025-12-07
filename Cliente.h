#pragma once
#include "Usuario.h"

class Cliente : protected Usuario
{
public:
    // Método para reservar un vuelo
    void ReservarVuelo(int idUsuario);  // Cambiado a void y con parámetro

    // Método para pagar los vuelos reservados
    void PagarVuelos(int idUsuario);    // Añadido parámetro
    void ImprimirBoletos(int idUsuario);
};