/** \file data.cc
 *  \brief Implementació de Data (Dia i Hora)
 */
#include "data.hh"

Dia::Dia(string s) :
dia(stoi(s.substr(0,2))), mes(stoi(s.substr(3,2))), any(stoi(s.substr(6,2))) {}

bool Dia::operator<(const Dia &d) const {
    return (any < d.any) or (mes < d.mes) or (dia < d.dia);
}

void Dia::print(const Dia& d, ostream& os) {
    if (d.dia < 10) os << 0;
    os << d.dia << '.';
    if (d.mes < 10) os << 0;
    os << d.mes << '.';
    if (d.any < 10) os << 0;
    os << d.any;
}

Hora::Hora(string s) : hora(stoi(s.substr(0,2))) , minut(stoi(s.substr(3,2))) {}

bool Hora::operator<(const Hora &h) const {
    return (hora < h.hora) or (minut < h.minut);
}

void Hora::print(const Hora& h, ostream& os) {
    if (h.hora < 10) os << 0;
    os << h.hora << ':';
    if (h.minut < 10) os << 0;
    os << h.minut;
}


ostream& operator<<(ostream& os, const Data& d) {
    Dia::print(d.first, os);
    os << ' ';
    Hora::print(d.second, os);
    return os;
}
