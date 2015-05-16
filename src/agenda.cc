/**
 * \file agenda.cc
 * \brief Implementació agenda
 */
#include "agenda.hh"
using namespace std;

Agenda::Agenda() {
    clock_ = {{{1,1,0},{12,18}}, tasks_.begin()};
}

void Agenda::set_rellotge(Data data) {
    clock_ = {data, tasks_.lower_bound(data)};
}

void Agenda::add_tasca(Data data, Tasca t) {
    pair<instant,bool> it = tasks_.insert(make_pair(data,t));
    if (clock_.second == tasks_.end()) clock_.second = it.first;
}

void Agenda::set_titol(const int id, string titol) {}
void Agenda::set_data(const int id, Data data) {}
void Agenda::add_etiqueta(const int id, string etiqueta) {}
void Agenda::del_etiqueta(const int id, string etiqueta) {}
void Agenda::del_etiquetes(const int id) {}
void Agenda::del_tasca(const int id) {}

bool Agenda::existeix(const Data& data) const {
    return (tasks_.find(data) != tasks_.end());
}

bool Agenda::is_passat(const Data& data) const {
    return (data < clock_.first);
}

bool Agenda::is_modificable(const int id) const {}

void Agenda::print_rellotge() const {
    cout << clock_.first;
}

Dia Agenda::get_dia() const {
    return clock_.first.first;
}

Hora Agenda::get_hora() const {
    return clock_.first.second;
}

void Agenda::consulta(Dia dia1, Dia dia2, string expressio) {}
void Agenda::consulta(Dia dia, string expressio) {}
void Agenda::consulta() {}

void Agenda::passat() const {
    map<Data, Tasca>::const_iterator it = tasks_.begin();
    int i = 1;
    while (it != clock_.second) {
        cout << i << ' ';
        Tasca::print_titol(it->second, cout);
        cout << ' ' << it->first << ' ';
        Tasca::print_etiquetes(it->second, cout);
        cout << '\n';
        it++, i++;
    }
}
