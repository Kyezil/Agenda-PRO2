#include <iostream>
#include "tasca.hh"
using namespace std;

int main() {
    Tasca t ("la meva tasca");
    Tasca::print_titol(t, cout);
    cout << endl;
    t.set_titol("canvi de nom");
    Tasca::print_titol(t, cout);
    cout << endl;
    Tasca::print_etiquetes(t, cout);
    cout << endl;
    t.add_etiqueta("arbre");
    t.add_etiqueta("poma");
    Tasca::print_etiquetes(t, cout);
    cout << endl;
    t.del_etiqueta("arbre");
    Tasca::print_etiquetes(t, cout);
    cout << endl;
    t.add_etiqueta("arbre");
    Tasca::print_etiquetes(t, cout);
    cout << endl;
    t.del_etiquetes();
    Tasca::print_etiquetes(t, cout);
    cout << endl;
}
