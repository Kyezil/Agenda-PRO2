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

pair<Agenda::instant, bool> Agenda::p_add_tasca(const Data& data, const Tasca& t) {
    pair<instant,bool> ins = tasks_.emplace(make_pair(data, t));
    if (ins.second) { //si s'ha pogut inserir
        // afegeix etiquetes i actualitza tags
        Tasca::tag_iterator tag = ins.first->second.begin_etiquetes();
        while (tag != ins.first->second.end_etiquetes()) {
            tags_[*tag].insert(ins.first);
            ++tag;
        }
        // actualitza rellotge
        if (++ins.first == clock_.second)
            clock_.second = --ins.first;
    }
    return ins;
}

bool Agenda::add_tasca(const Data &data, const Tasca& t) {
    return p_add_tasca(data, t).second;
}


//void Agenda::set_titol(const int id, string titol) {}
//void Agenda::set_data(const int id, Data data) {}
//void Agenda::add_etiqueta(const int id, string etiqueta) {}
//void Agenda::del_etiqueta(const int id, string etiqueta) {}
//void Agenda::del_etiquetes(const int id) {}
//void Agenda::del_tasca(const int id) {}

bool Agenda::is_passat(const Data& data) const {
    return (data < clock_.first);
}

//bool Agenda::is_modificable(const int id) const {}

Dia Agenda::get_dia() const {
    return clock_.first.first;
}

Hora Agenda::get_hora() const {
    return clock_.first.second;
}

//void Agenda::consulta(Dia dia1, Dia dia2, string expressio) {}
//void Agenda::consulta(Dia dia, string expressio) {}

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
    cinstant it = tasks_.begin();
    int i = 1;
    while (it != clock_.second) {
        print_menu_item(i, it);
        it++, i++;
    }
}

void Agenda::print_map_data_tasca() {
    cinstant it = tasks_.begin();
    cout << "======== MAP PRINCIPAL =======\n";
    while (it != tasks_.end()) {
        cout << it->first << ' ';
        Tasca::print_titol(it->second,cout);
        cout << ' ';
        Tasca::print_etiquetes(it->second, cout);
        cout << '\n';
        ++it;
    }
    cout << endl;
}

void Agenda::print_map_tags() {
    map<string, set<instant, ordre_instant> >::const_iterator it = tags_.begin();
    cout << "======== ETIQUETES =======\n";
    while (it != tags_.end()) {
        cout << "-- " << it->first << " --\n";
        for (auto ins : it->second) {
            cout << ' ';
            Tasca::print_titol(ins->second, cout);
            cout << '\n';
        }
        ++it;
    }
}

// PRIVATE
bool Agenda::ordre_instant::operator()(const instant &a, const instant &b) const {
    return (a->first < b->first);
}

void Agenda::print_menu_item(int i, const cinstant& it) const {
    cout << i << ' ';
    Tasca::print_titol(it->second, cout);
    cout << ' ' << it->first << ' ';
    Tasca::print_etiquetes(it->second, cout);
    cout << '\n';
}
