/**
 * \file agenda.cc
 * \brief Implementació agenda
 */
#include "agenda.hh"
using namespace std;

Agenda::Agenda(){}
void Agenda::set_rellotge(Data data){}
void Agenda::add_tasca(string titol, Data data){}
void Agenda::set_titol(int id, string titol){}
void Agenda::set_data(int id, Data data){}
void Agenda::add_etiqueta(int id, string etiqueta){}
void Agenda::del_etiqueta(int id, string etiqueta){}
void Agenda::del_etiquetes(int id){}
void Agenda::del_tasca(int id){}
bool Agenda::existeix(Data data) const{}
bool Agenda::es_passat(Data data) const{}
bool Agenda::es_modificable(int id) const{}
void Agenda::print_rellotge() const{}
Dia Agenda::get_dia() const{}
Hora Agenda::get_hora() const{}
void Agenda::consulta(Dia dia1, Dia dia2, string expressio){}
void Agenda::consulta(Dia dia, string expressio){}
void Agenda::consulta(){}
