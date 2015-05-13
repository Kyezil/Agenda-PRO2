/**
* \file agenda.cc
* \brief Implementació agenda
*/
#include "agenda.hh"
#include "tasca.hh"
#include <iostream>
using namespace std;

Agenda::Agenda(){}

void Agenda::set_rellotge(Data data){
  rellotge = {data, tasques.lower_bound(data)};
}

void Agenda::add_tasca(string titol, Data data){
  tasques.insert({data, Tasca(titol)});
}

void Agenda::set_titol(int id, string titol){
  menu[id].second->set_titol(titol);
}

void Agenda::set_data(int id, Data data){
// no se
}
Tasca(titol)
void Agenda::add_etiqueta(int id, string etiqueta){
  menu[id].second->add_etiqueta(etiqueta);
}

void Agenda::del_etiqueta(int id, string etiqueta){
  menu[id].second->del_etiqueta(etiqueta);
}

void Agenda::del_etiquetes(int id){
  menu[id].second->del_etiquetes(); // no existeix, shauria d'afegir a tasca
}

void Agenda::del_tasca(int id){
    
}

bool Agenda::existeix(Data data) const{
  return (tasques.find(data) != tasques.end());
}

bool Agenda::es_passat(Data data) const{
  return (data < rellotge.first);
}

bool Agenda::es_modificable(int id) const{}

void Agenda::print_rellotge() const{
  cout << rellotge.first;
}

Dia Agenda::get_dia() const{
  return rellotge.first.first;
}

Hora Agenda::get_hora() const{
  return rellotge.first.second;
}

void Agenda::consulta(Dia dia1, Dia dia2, string expressio){
    if (dia1 < dia2) {
        if (dia1 < rellotge.first.first) {
            consulta_directa({rellotge.first, {dia2, Hora(23, 59)},
                                     expressio);
        }
        else {
            consulta_directa({dia1, Hora(0, 0)}, {dia2, Hora(23,59)},
                                     expressio);
        }
    }
    else if (not dia2 < dia1) {
        if (dia1 < rellotge.first.first) {
            consulta_directa(rellotge.first, expressio);
        }
        else {
            consulta_directa({dia1, Hora(0, 0)}, {dia1, Hora(23, 59)},
                                    expressio);
        }

    }
}

void Agenda::consulta(Dia dia, string expressio){
    consulta_directa({dia1, Hora(0, 0)}, {dia1, Hora(23, 59)}, expressio);
}

void Agenda::passat(){
    map<Data, Tasca>::iterator it = tasques.begin();
    int i = 1; 
    while (it != tasques.end()){
        cout << i << ' '; 
        Tasca::print_titol(*it, cout);
        cout << ' ' << rellotge.first << ' ' << rellotge.second;
        Tasca::print_etiquetes(*it, cout);
        cout << endl; 
        it++;
        i++;
    }   
    
}
void Agenda::consulta(){
    
}
