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
void begin_etiquetes(cword it) {
    it = tags_.begin();
}

void end_etiquetes(cword it) {
    it = tags_.end();
}

void Tasca::print_titol(const Tasca& t, ostream& out) {
    out << t.title_;
}

void Tasca::print_etiquetes(const Tasca& t, ostream& out) {
    set<string>::const_iterator it = t.tags_.begin();
    if (it != t.tags_.end()) {
        out << *it;
        ++it;
        while (it != t.tags_.end()) {
            out << *it;
            ++it;
        }
    }
}
