#pragma once
#include <string>
#include <vector>

class Reservacion {
public:
    int idUsuario;
    int idVuelo;
    std::string asientos; // "0000000000"
    bool pagado;

    Reservacion(int uid, int vid, const std::string& as = "0000000000", bool p = false)
        : idUsuario(uid), idVuelo(vid), asientos(as), pagado(p) {
    }

    // Guardar reservación en archivo
    bool guardar();

    // Obtener todas las reservaciones desde archivo
    static std::vector<Reservacion> obtenerTodas();

    // Obtener reservaciones de un vuelo y combinarlas en la cadena de asientos
    static std::string asientosCombinados(int idVuelo);

    // Marcar reservaciones de un usuario como pagadas
    static void pagarReservaciones(int idUsuario);

    // Cambiado de void a bool para que pueda usarse en un if
    static bool pagarReservacionesIndividual(int idUsuario, int idVuelo, const std::string& asientos);
};
