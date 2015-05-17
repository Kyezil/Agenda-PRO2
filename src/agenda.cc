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

bool Agenda::add_tasca(Data data, string titol, const set<string>& etiq) {
    pair<instant,bool> ans = tasks_.emplace(make_pair(data,titol));
    if (ans.second) { //si s'ha pogut inserir
        // afegeix etiquetes i actualitza tags
        for (auto tag : etiq) {
            ans.first->second.add_etiqueta(tag);
            tags_[tag].insert(ans.first);
        }
        // actualitza rellotge
        if (++ans.first == clock_.second)
            clock_.second = --ans.first;
    }
    return ans.second;
}


void Agenda::set_titol(const int id, string titol) {
    list<instant>::iterator it = menu_.begin();
    advance(it, id - 1);
    (*it)->second.set_titol(titol);
}

void Agenda::set_data(const int id, Data data) {
    list<instant>::iterator it = menu_.begin();
    advance(it, id - 1);
    (*it)->first = data;
    instant nou = tasks_.find(data);
    cword inici, fi;
    nou->second.begin_etiquetes(inici);
    nou->second.end_etiquetes(fi);
    while(inici != fi) {
        tags_[*inici].erase(*it);
        tags_[*inici].insert(nou);
        ++inici;
    }
    *it = nou;
}

void Agenda::add_etiqueta(const int id, string etiqueta) {
    list<instant>::iterator it = menu_.begin();
    advance(it, id - 1);
    (*(*it)).second.add_etiqueta(etiqueta);
    tags_[etiqueta].insert(*it);
}
void Agenda::del_etiqueta(const int id, string etiqueta) {
    list<instant>::iterator it = menu_.begin();
    advance(it, id - 1);
    (*it)->second.del_etiqueta(etiqueta);
    tags_[etiqueta].erase(*it);
}
void Agenda::del_etiquetes(const int id) {
    list<instant>::iterator it = menu_.begin();
    advance(it, id - 1);
    cword inici, fi;
    (*it)->second.begin_etiquetes(inici);
    (*it)->second.end_etiquetes(fi);
    while(inici != fi) {
        tags_[(*inici)].erase(*it);
        ++inici;
    }
    (*it)->second.del_etiquetes();
}
void Agenda::del_tasca(const int id) {
    list<instant>::iterator it = menu_.begin();
    advance(it, id - 1);
    cword inici, fi;
    (*it)->second.begin_etiquetes(inici);
    (*it)->second.end_etiquetes(fi);
    while(inici != fi) {
        tags_[(*inici)].erase(*it); // (*it) es element a esborrar
        ++inici;
    }
    tasques.erase(*it); // (*it) es iterador del element a esborrar
    *it = tasques.end();
}

bool Agenda::is_passat(const Data& data) const {
    return (data < clock_.first);
}

bool Agenda::is_modificable(const int id) const {
    bool modi = ((0 < id) and (id < menu_.size()));
    if (modi) {
        list<instant>::iterator it = menu_.begin();
        advance(it, id - 1);
        modi = ((*it) != menu_.end());
        if (modi) {
            modi = ((*it)->first >= clock.first);
        }
    }
    return modi;
}

Dia Agenda::get_dia() const {
    return clock_.first.first;
}

Hora Agenda::get_hora() const {
    return clock_.first.second;
}

void Agenda::consulta(Dia dia1, Dia dia2, string expressio) {
    instant it = lower_bound({dia1, Hora(0,0)});
    instant end = upper_bound({dia2, Hora(23,59)});
    menu_.clear();
    int i = 1;
    while (it != end) {
        print_menu_itme(i, it);
        menu_.push_back(it);
        ++i;
        ++it;
    }
}

void Agenda::consulta(Dia dia, string expressio) {
    instant it = lower_bound({dia1, Hora(0,0)});
    instant end = upper_bound({dia1, Hora(23,59)});
    menu_.clear();
    int i = 1;
    while (it != end) {
        print_menu_item(i, it);
        menu_.push_back(it);
        ++i;
        ++it;
    }
}

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
