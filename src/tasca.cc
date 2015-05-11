/**
 *  \file tasca.cc
 *  \brief Implementació tasca
 */
#include "tasca.hh" 

Tasca::Tasca(string titol): titol(titol){
} 
void Tasca::modificar_titol(string titol){
  this->titol=titol; 
}
void Tasca::afegir_etiqueta(string etiq){
 etiquetes.insert(etiq); 
}
void Tasca::esborrar_etiqueta(string etiq){
  etiquetes.erase(etiq);
}
