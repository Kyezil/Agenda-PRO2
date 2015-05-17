/** \file data.cc
 *  \brief Implementació de Data (Dia i Hora)
 */
#include "data.hh"

Dia::Dia(int d, int m, int a) : dia(d), mes(m), any(a) {}

Dia::Dia(string s) :
dia(stoi(s.substr(0,2))), mes(stoi(s.substr(3,2))), any(stoi(s.substr(6,2))) {}

void Dia::print(const Dia& d, ostream& os) {
    if (d.dia < 10) os << 0;
    os << d.dia << '.';
    if (d.mes < 10) os << 0;
    os << d.mes << '.';
    if (d.any < 10) os << 0;
    os << d.any;
}

bool operator<(const Dia &lhs, const Dia& rhs) {
    if (lhs.any != rhs.any) return (lhs.any < rhs.any);
    else if (lhs.mes != rhs.mes) return (lhs.mes < rhs.mes);
    else return (lhs.dia < rhs.dia);
}
bool operator==(const Dia& lhs, const Dia& rhs) {
    return not (lhs < rhs) and not (rhs < lhs);
}
bool operator!=(const Dia& lhs, const Dia& rhs) {
    return (lhs < rhs) or (rhs < lhs);
}
bool operator>(const Dia& lhs, const Dia& rhs) {
    return (rhs < lhs);
}
bool operator<=(const Dia& lhs, const Dia& rhs) {
    return not (rhs < lhs);
}
bool operator>=(const Dia& lhs, const Dia& rhs) {
    return not (lhs < rhs);
}

Hora::Hora(int h, int m) : hora(h), minut(m) {}

Hora::Hora(string s) : hora(stoi(s.substr(0,2))) , minut(stoi(s.substr(3,2))) {}

bool operator<(const Hora &lhs, const Hora &rhs) {
        if (lhs.hora != rhs.hora) return (lhs.hora < rhs.hora);
    else return (lhs.minut < rhs.minut);
}
bool operator==(const Hora& lhs, const Hora& rhs) {
    return not (lhs < rhs) and not (rhs < lhs);
}
bool operator!=(const Hora& lhs, const Hora& rhs) {
    return (lhs < rhs) or (rhs < lhs);
}
bool operator>(const Hora& lhs, const Hora& rhs) {
    return (rhs < lhs);
}
bool operator<=(const Hora& lhs, const Hora& rhs) {
    return not (rhs < lhs);
}
bool operator>=(const Hora& lhs, const Hora& rhs) {
    return not (lhs < rhs);
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
