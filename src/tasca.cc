/**
 *  \file tasca.cc
 *  \brief Implementació Tasca
 */
#include "tasca.hh"

Tasca::Tasca(string titol): title_(titol) {}

void Tasca::set_titol(string titol) {
    title_ = titol; 
}

void Tasca::add_etiqueta(string etiq) {
    tags_.insert(etiq); 
}

void Tasca::del_etiqueta(string etiq) {
    tags_.erase(etiq);
}

void Tasca::del_etiquetes() {
    tags_.clear();
}

Tasca::tag_iterator Tasca::begin_etiquetes() {
    return tags_.begin();
}

Tasca::tag_iterator Tasca::end_etiquetes() {
    return tags_.end();
}

void Tasca::print_titol(const Tasca& t, ostream& out) {
    out << t.title_;
}

void Tasca::print_etiquetes(const Tasca& t, ostream& out) {
    tag_iterator it = t.tags_.begin();
    while (it != t.tags_.end()) {
        out << ' ' << *it;
        ++it;
    }
}
