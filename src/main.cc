/** \file main.cc
 *  \brief Programa principal
 */
/// \cond HIDE
#include <set>
/// \endcond HIDE
#include "agenda.hh"
#include "comanda.hh"
#include "data.hh"
using namespace std;

void nop(bool ok = false) {
    if (not ok) cout << "No s'ha realitzat\n";
}

int main (){
    Agenda ag;
    Comanda com;
    bool be;
    while (com.llegir(be)) {
        if (com.es_insercio()) {
            // genera data
            Data d;
            if (com.nombre_dates() == 0) d.first = ag.get_dia();
            else d.first = Dia(com.data(1));
            d.second = Hora(com.hora());
            bool ok = false;
            if(not ag.is_passat(d)) {
                // genera etiquetes si cal
                if (com.nombre_etiquetes() > 0) {
                    set<string> etiquetes;
                    for (int i = 1; i <= com.nombre_etiquetes(); ++i)
                        etiquetes.insert(com.etiqueta(i));
                    ok = ag.add_tasca(d, com.titol(), etiquetes);
                }
                else ok = ag.add_tasca(d, com.titol());
            }
            nop(ok);
        }
    }
}
