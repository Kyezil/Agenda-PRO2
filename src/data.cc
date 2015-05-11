/** \file data.cc
 *  \brief Implementació de Data (Dia i Hora)
 */
#include "data.hh"

Dia::Dia(string s) {
    dia = stoi(s.substr(0,2));
    mes = stoi(s.substr(3,2));
    any = stoi(s.substr(6,2));
}

bool Dia::operator<(const Dia &d) const {
    return (any < d.any) or (mes < d.mes) or (dia < d.dia);
}

Hora::Hora(string s) {
    hora = stoi(s.substr(0,2));
    minut = stoi(s.substr(3,2));
}

bool Hora::operator<(const Hora &h) const {
    return (hora < h.hora) or (minut < h.minut);
}
