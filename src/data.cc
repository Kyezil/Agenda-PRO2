/** \file data.cc
 *  \brief Implementació de Data (Dia i Hora)
 */
#include "data.hh"

Dia::Dia(string s) {
    dia = (s[0] - '0')*10 + s[1] - '0';
    mes = (s[3] - '0')*10 + s[4] - '0';
    any = (s[6] - '0')*10 + s[7] - '0';
}

bool Dia::operator<(const Dia &d) const {
    return (any < d.any) or (mes < d.mes) or (dia < d.dia);
}

Hora::Hora(string s) {
    hora = (s[0] - '0')*10 + s[1] - '0';
    minut = (s[3] - '0')*10 + s[4] - '0';
}

bool Hora::operator<(const Hora &h) const {
    return (hora < h.hora) or (minut < h.minut);
}
