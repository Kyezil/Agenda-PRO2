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
        if (com.es_rellotge()) {
            if (com.es_consulta()) cout << make_pair(ag.get_dia(), ag.get_hora()) << '\n';
            else {
                Data d;
                if (com.nombre_dates() == 0) d.first = ag.get_dia();
                else d.first = com.data(1);
                if (com.te_hora()) d.second = com.hora();
                else d.second = ag.get_hora();
                if (not ag.is_passat(d)) ag.set_rellotge(d);
                else nop();
            }
        }
        else if (com.es_passat()) ag.passat();
        else if(com.es_consulta()) {
            if (com.nombre_dates() == 0 and not com.te_expressio()) ag.consulta();
            // TODO es poden ajuntar varies però de moment per provar
        }
        else if (com.es_insercio()) {
            // genera data
            Data d;
            if (com.nombre_dates() == 0) d.first = ag.get_dia();
            else d.first = com.data(1);
            d.second = com.hora();
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
        ag.print_map_data_tasca();
        ag.print_map_tags();
    }
}
