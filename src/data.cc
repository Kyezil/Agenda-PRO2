/** \file data.cc
\brief Implementació de Data (Dia i Hora)
*/

#include "data.hh"

Dia::Dia(string s) {
  dia = (s[0] - '0')*10 + s[1] - '0';
  mes = (s[3] - '0')*10 + s[4] - '0';
  any = (s[6] - '0')*10 + s[7] - '0';
}

bool Dia::operator<(const Dia &D) const {
  if (any < D.any) return true;
  else if (mes < D.mes) return true;
  else return (dia < D.dia);
}

Hora::Hora(string s) {
  hora = (s[0] - '0')*10 + s[1] - '0';
  minut = (s[3] - '0')*10 + s[4] - '0';
}

bool Hora::operator<(const Hora &d) const {
  if (hora < d.hora) return true;
  else return (minut < d.minut);
}
