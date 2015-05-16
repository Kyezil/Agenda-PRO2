#include <iostream>
#include "agenda.hh"
#include "tasca.hh"
using namespace std;

int main() {
    Agenda ag;
    ag.print_rellotge();
    cout << endl;
    Tasca t ("hola");
    t.add_etiqueta("hi");
    ag.add_tasca({{3,2,1},{7,5}}, t);
    ag.passat();
}
