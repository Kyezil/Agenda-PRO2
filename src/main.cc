/** \file main.cc
 *  \brief Programa principal
 */

#include "agenda.hh"
#include "comanda.hh"
#include "data.hh"
using namespace std;

int main (){
    Agenda agenda;
    Comanda comanda;
    bool be;
    while (comanda.llegir(be)) {
        if (comanda.es_insercio()) {
            if (comanda.nombre_dates()!=0) {
                if (not agenda.is_passat({comanda.data(1),comanda.hora()}) and (not agenda.existeix({comanda.data(1),comanda.hora()}))){
                    agenda.add_tasca({Dia(comanda.data(1)), Hora(comanda.hora())} ,comanda.titol());
                }
                else cout << "No s'ha realitzat" << endl;
            }
            else {
                if (not agenda.existeix({comanda.data(1),comanda.hora()})){
                    agenda.add_tasca({agenda.get_dia(), Hora(comanda.hora())},comanda.titol());
                }
                else cout << "No s'ha realitzat" << endl;
            }
        }
        else if (comanda.es_consulta()){
            if (comanda.nombre_dates()==0){
                if (not comanda.te_expressio()) agenda.consulta();
                else;
            }
            else if (comanda.nombre_dates()==1) {
                if (not comanda.te_expressio());
                else;
            }
            else {
                if (not comanda.te_expressio());
                else;
            }
        }
        else if (comanda.es_passat()) agenda.passat();
        else if (comanda.es_modificacio()){
            if (comanda.te_titol()) {
                if (not agenda.is_passat({comanda.data(1),comanda.hora()}) and (not agenda.existeix({comanda.data(1),comanda.hora()})));
                else cout << "No s'ha realitzat" << endl;
            }
            for (int i = 0; i < comanda.nombre_etiquetes(); ++i) {
                if (agenda.is_modificable(comanda.tasca()));
                else cout << "No s'ha realitzat" << endl;
            }
            if (comanda.te_hora()) {
                if (agenda.is_modificable(comanda.tasca()));
                else cout << "No s'ha realitzat" << endl;
            }
            if (comanda.nombre_dates()!=0){
                if (agenda.is_modificable(comanda.tasca()));
                else cout << "No s'ha realitzat" << endl;
            }
        }
        else if (comanda.es_rellotge()) {
            if (comanda.es_consulta()) agenda.print_rellotge();
            if (comanda.nombre_dates()!=0) {
                if (not agenda.is_passat({comanda.data(1),comanda.hora()})){
                    agenda.set_rellotge({Dia(comanda.data(1)),agenda.get_hora()});
                }
                else cout << "No s'ha realitzat" << endl;
            }
            if (comanda.te_hora()) {
                if (not agenda.is_passat({agenda.get_dia(),comanda.hora()})){
                    agenda.set_rellotge({agenda.get_dia(),Hora(comanda.hora())});
                }
                else cout << "No s'ha realitzat" << endl;
            }
        }
        else if (comanda.es_esborrat()) {
            if (comanda.tipus_esborrat() == "tasca") {
                if (agenda.is_modificable(comanda.tasca()));
                else cout << "No s'ha realitzat" << endl;
            }
            else if (comanda.tipus_esborrat() == "etiquetes") {
                if (agenda.is_modificable(comanda.tasca()));
                else cout << "No s'ha realitzat" << endl;
            }
            else if (comanda.tipus_esborrat() == "etiqueta" ) {
                if (agenda.is_modificable(comanda.tasca()));
                else cout << "No s'ha realitzat" << endl;
            }
        }
    }
}
