/**
 * \file agenda.cc
 * \brief Implementació agenda
 */
#include "agenda.hh"
using namespace std;

Agenda::Agenda(){}
void Agenda::set_rellotge(Data data) {}
void Agenda::add_tasca(Data data, Tasca t) {}
void Agenda::set_titol(const int id, string titol) {}
void Agenda::set_data(const int id, Data data) {}
void Agenda::add_etiqueta(const int id, string etiqueta) {}
void Agenda::del_etiqueta(const int id, string etiqueta) {}
void Agenda::del_etiquetes(const int id) {}
void Agenda::del_tasca(const int id) {}
bool Agenda::existeix(const Data& data) const {}
bool Agenda::is_passat(const Data& data) const {}
bool Agenda::is_modificable(const int id) const {}
void Agenda::print_rellotge() const {}
Dia Agenda::get_dia() const {}
Hora Agenda::get_hora() const {}
void Agenda::consulta(Dia dia1, Dia dia2, string expressio) {}
void Agenda::consulta(Dia dia, string expressio) {}
void Agenda::consulta() {}
