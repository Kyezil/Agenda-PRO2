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
