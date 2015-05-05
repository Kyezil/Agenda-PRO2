/** \file main.cc
 *  \brief Programa principal
 */

#include "agenda.hh"
#include "comanda.hh"
using namespace std;

int main (){
    Agenda agenda;
    Comanda comanda;
    bool be;
    while (comanda.llegir(be)) {
        if (comanda.es_insercio()) {
            if (comanda.nombre_dates()!=0) {
                if (not agenda.es_passat({comanda.data(1),comanda.hora()}) and (not agenda.existeix({comanda.data(1),comanda.hora()}))){
                    agenda.add_tasca(comanda.titol(), {Dia(comanda.data(1)), Hora(comanda.hora())});
                }
                else cout << "No s'ha realitzat" << endl;
            }
            else {
                if (not agenda.existeix({comanda.data(1),comanda.hora()})){
                    agenda.add_tasca(comanda.titol(), {agenda.get_dia(), Hora(comanda.hora())});
                }
                else cout << "No s'ha realitzat" << endl;
            }
        }
        else if (comanda.es_consulta()){
            if (comanda.nombre_dates()==0){
                if (not comanda.te_expressio()) agenda.consulta();
                else agenda.consulta(comanda.expressio());
            }
            else if (comanda.nombre_dates()==1) {
                if (not comanda.te_expressio()) agenda.consulta(comanda.data(1));
                else  agenda.consulta(Dia(comanda.data(1)), comanda.expressio());
            }
            else {
                if (not comanda.te_expressio()) agenda.consulta(Dia(comanda.data(1)), Dia(comanda.data(2)));
                else agenda.consulta(Dia(comanda.data(1)), Dia(comanda.data(2)), comanda.expressio());
            }
        }
        else if (comanda.es_passat()) agenda.passat();
        else if (comanda.es_modificacio()){
            if (comanda.te_titol()) {
                if (not agenda.es_passat({comanda.data(1),comanda.hora()}) and (not agenda.existeix({comanda.data(1),comanda.hora()})))
                    agenda.set_titol(comanda.tasca(), comanda.titol());
                else cout << "No s'ha realitzat" << endl;
            }
            for (int i = 0; i < comanda.nombre_etiquetes(); ++i) {
                if (agenda.es_modificable(comanda.tasca())) agenda.add_etiqueta(comanda.tasca(), comanda.etiqueta(i));
                else cout << "No s'ha realitzat" << endl;
            }
            if (comanda.te_hora()) {
                if (agenda.es_modificable(comanda.tasca()))
                    agenda.set_data(comanda.tasca(), {agenda.get_dia(),Hora(comanda.hora())});
                else cout << "No s'ha realitzat" << endl;
            }
            if (comanda.nombre_dates()!=0){
                if (agenda.es_modificable(comanda.tasca())){
                    agenda.set_data(comanda.tasca(), {Dia(comanda.data(1)),agenda.get_hora()});
                }
                else cout << "No s'ha realitzat" << endl;
            }
        }
        else if (comanda.es_rellotge()) {
            if (comanda.es_consulta()) agenda.print_rellotge();
            if (comanda.nombre_dates()!=0) {
                if (not agenda.es_passat({comanda.data(1),comanda.hora()})){
                    agenda.set_rellotge({Dia(comanda.data(1)),agenda.get_hora()});
                }
                else cout << "No s'ha realitzat" << endl;
            }
            if (comanda.te_hora()) {
                if (not agenda.es_passat({agenda.get_dia(),comanda.hora()})){
                    agenda.set_rellotge({agenda.get_dia(),Hora(comanda.hora())});
                }
                else cout << "No s'ha realitzat" << endl;
            }
        }
        else if (comanda.es_esborrat()) {
            if (comanda.tipus_esborrat() == "tasca") {
                if (agenda.es_modificable(comanda.tasca())) agenda.del_tasca(comanda.tasca());
                else cout << "No s'ha realitzat" << endl;
            }
            else if (comanda.tipus_esborrat() == "etiquetes") {
                if (agenda.es_modificable(comanda.tasca())) agenda.del_etiquetes(comanda.tasca());
                else cout << "No s'ha realitzat" << endl;
            }
            else if (comanda.tipus_esborrat() == "etiqueta" ) {
                if (agenda.es_modificable(comanda.tasca())) agenda.del_etiqueta(comanda.tasca(), comanda.etiqueta(0));
                else cout << "No s'ha realitzat" << endl;
            }
        }
    }
}
