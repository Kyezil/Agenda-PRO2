/**
 * \file agenda.cc
 * \brief Implementació agenda
 */
#include "agenda.hh"
using namespace std;

Agenda::Agenda() {
    clock_ = {origin,tasks_.begin()};
}

void Agenda::set_rellotge(Data data) {
    clock_ = {data, tasks_.lower_bound(data)};
}

bool Agenda::add_tasca(Data data, Tasca t) {
    pair<instant,bool> ans = tasks_.insert(make_pair(data,t));
    if (ans.second and (++ans.first == clock_.second))
        clock_.second = --ans.first;
    return ans.second;
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

void Agenda::consulta() {
    instant it = clock_.second;
    menu_.clear();
    int i = 1;
    while (it != tasks_.end()) {
        print_menu_item(i, it);
        menu_.push_back(it);
        ++i, ++it;
    }
}

void Agenda::passat() const {
    instant it = tasks_.begin();
    int i = 1;
    while (it != clock_.second) {
        print_menu_item(i, it);
        it++, i++;
    }
}

// PRIVATE
bool Agenda::ordre_instant::operator()(const instant &a, const instant &b) const {
    return (a->first < b->first);
}

void Agenda::print_menu_item(int i, const instant& it) const {
    cout << i << ' ';
    Tasca::print_titol(it->second, cout);
    cout << ' ' << it->first << ' ';
    Tasca::print_etiquetes(it->second, cout);
    cout << '\n';
}
