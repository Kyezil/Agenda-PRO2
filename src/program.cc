/** \file main.cc
 *  \brief Programa principal
 */
/// \cond HIDE
#include <cassert>
/// \endcond HIDE
#include "agenda.hh"
#include "tasca.hh"
#include "data.hh"
#include "comanda.hh"
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
            if (com.nombre_dates() == 0) {
                if (com.te_expressio()) ag.consulta(com.expressio());
                else if (com.nombre_etiquetes() == 0) ag.consulta();
                else ag.consulta(com.etiqueta(1));
            }
            else if (com.nombre_dates() == 1) {
                if(com.te_expressio())
                    ag.consulta(Dia(com.data(1)), com.expressio());
                else if (com.nombre_etiquetes() == 0)
                    ag.consulta(Dia(com.data(1)));
                else
                    ag.consulta(Dia(com.data(1)), com.etiqueta(1));
            }
            else {
                assert(com.nombre_dates() == 2);
                if (com.te_expressio())
                    ag.consulta(Dia(com.data(1)), Dia(com.data(2)), com.expressio());
                else if (com.nombre_etiquetes() == 0)
                    ag.consulta(Dia(com.data(1)), Dia(com.data(2)));
                else
                    ag.consulta(Dia(com.data(1)), Dia(com.data(2)), com.etiqueta(1));
            }
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
                    Tasca &&temp (com.titol());
                    for (int i = 1; i <= com.nombre_etiquetes(); ++i)
                        temp.add_etiqueta(com.etiqueta(i));
                    ok = ag.add_tasca(d, temp);
                }
                else ok = ag.add_tasca(d, Tasca(com.titol()));
            }
            nop(ok);
        }
        else if (com.es_modificacio()) {
            bool ok = true;
            if (com.nombre_dates() == 0 and com.te_hora()) ok = ag.set_hora(com.tasca(), com.hora());
            else if (com.nombre_dates() != 0) {
                if (com.te_hora()) ok = ag.set_data(com.tasca(), make_pair(Dia(com.data(1)), Hora(com.hora())));
                else ok = ag.set_dia(com.tasca(), com.data(1));
            }
            if (ok and com.te_titol())
                ok = ag.set_titol(com.tasca(), com.titol());
            for (int i = 1; ok and i <= com.nombre_etiquetes(); ++i)
                ok = ag.add_etiqueta(com.tasca(), com.etiqueta(i));
            nop(ok);
        }
        else if (com.es_esborrat()) {
            if (com.tipus_esborrat() == "etiqueta")
                nop(ag.del_etiqueta(com.tasca(), com.etiqueta(1)));
            else if (com.tipus_esborrat() == "etiquetes")
                nop(ag.del_etiquetes(com.tasca()));
            else if (com.tipus_esborrat() == "tasca")
                nop(ag.del_tasca(com.tasca()));
        }
    }
}
