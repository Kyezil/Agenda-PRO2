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
    Tasca t1 ("sopar");
    t1.add_etiqueta("miam");
    t1.add_etiqueta("arròs");
    ag.add_tasca({{2,2,1},{21,0}}, t1);
    cout << "PASSAT\n";
    ag.passat();
    cout << "FUTUR\n";
    ag.consulta();
}
