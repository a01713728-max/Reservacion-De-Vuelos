#pragma once
#include <string>
#include <vector>

class Vuelo
{
private:
    int id;
    std::string fecha;
    std::string hora;
    std::string origen;
    std::string destino;
    std::string noAvion;

public:
    Vuelo(int i = 0, std::string f = "", std::string h = "",
        std::string o = "", std::string d = "", std::string na = "")
        : id(i), fecha(f), hora(h), origen(o), destino(d), noAvion(na) {
    }

    int getId() const { return id; }
    std::string getFecha() const { return fecha; }
    std::string getHora() const { return hora; }
    std::string getOrigen() const { return origen; }
    std::string getDestino() const { return destino; }
    std::string getNoAvion() const { return noAvion; }

    void Mostrar() const;

    static bool RegistrarVuelo(
        const std::string& fecha,
        const std::string& hora,
        const std::string& origen,
        const std::string& destino,
        const std::string& noAvion);

    static std::vector<Vuelo> ObtenerTodosLosVuelos();

    // ⭐⭐ ESTA ES LA QUE TE FALTABA ⭐⭐
    static Vuelo ObtenerVueloPorId(int idVuelo);
};
