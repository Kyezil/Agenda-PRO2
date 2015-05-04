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
      	/*  \pre la data no es del passat i no existeix cap tasca amb la mateixa data a la agenda
         *  \post a agenda s'ha afegit una tasca amb el títol i la data especificats 
         */
	if (not agenda.es_passat({comanda.data(1),comanda.hora()}) and (not existeix({comanda.data(1),comanda.hora()})){
	  agenda.add_tasca(comanda.titol(), {Dia(comanda.data(1)), Hora(comanda.hora())});
	}
	else cout << "Hi ha hagut un error" << endl;
      }
      else {
       	/*  \pre no existeix cap tasca a la data actual 
         *  \post a agenda s'ha afegit una tasca amb el títol especificat al dia actual i 
	       *        l'hora especificada
         */
	if (not existeix({comanda.data(1),comanda.hora()})){
	  agenda.add_tasca(comanda.titol(), {agenda.get_dia(), Hora(comanda.hora())});
	}
	else cout << "Hi ha hagut un error" << endl;
      }
  }
  else if (comanda.es_consulta()){
	if (comanda.nombre_dates()==0){
	    if (not comanda.te_expressio()) {
		/*  \pre true
		 *  \post s'ha generat i es mostra per pantalla un menú amb les tasques no passades
		 */
		agenda.consulta();
	    } 
	    else {
		/*  \pre true
		 *  \post s'ha generat i es mostra per pantalla un menú amb les tasques no passades amb 
		 *        etiquetes que compleixen l'expressio
		 */
		agenda.consulta(comanda.expressio());
	    }
	}
	else if (comanda.nombre_dates()==1) {
	     if (not comanda.te_expressio()) {
		/*  \pre true
		 *  \post s'ha generat i es mostra per pantalla un menú amb les tasques del dia especificat
		 */
		agenda.consulta(comanda.data(1));
	      }	
	      else {
	        /*  \pre true
		 *  \post s'ha generat i es mostra per pantalla un menú amb les tasques del dia especificat 
		 *        que compleixen l'expressio
		 */
		agenda.consulta(Dia(comanda.data(1)), comanda.expressio());
	      }
	}
	else {
	      if (not comanda.te_expressio()) {
		/*  \pre true
		 *  \post s'ha generat i es mostra per pantalla un menú amb les tasques entre els dies especificats
		 */
		  agenda.consulta(Dia(comanda.data(1)), Dia(comanda.data(2)));
	      }
	      else { 
		/*  \pre true
		 *  \post s'ha generat i es mostra per pantalla un menú amb les tasques entre els dies especificats 
		 *        que compleixen l'expressio
		 */
		   agenda.consulta(Dia(comanda.data(1)), Dia(comanda.data(2)), comanda.expressio());
	      }
       }
  }
  else if (comanda.es_passat()){
    /* \pre true
     * \post es mostren totes les tasques del passat 
     */
    agenda.passat();
  }
  else if (comanda.es_modificacio()){
	if (comanda.te_titol()) {
	    /*  \pre la tasca existeix i no és del passat
	     *  \post la tasca té el títol especificat
	     */
	    if (not agenda.es_passat({comanda.data(1),comanda.hora()}) and (not existeix({comanda.data(1),comanda.hora()})){
	    agenda.set_titol(comanda.tasca(), comanda.titol()); 
	    }
	    else cout << "Hi ha hagut un error" << endl; 
	}
	for (int i = 0; i < comanda.nombre_etiquetes(); ++i) {
      /*  \inv la tasca té les primeres i etiquetes especificades
       *  \pre la tasca existeix i no és del passat
	     *  \post la tasca té l'etiqueta especificada
	     */
	    if (agenda.es_modificable(comanda.tasca())){
	    agenda.add_etiqueta(comanda.tasca(), comanda.etiqueta(i));
	    }
	    else cout << "Hi ha hagut un error" << endl;   
	    }
	if (comanda.te_hora()) {
	    /*  \pre la tasca existeix i no és del passat
	     *  \post la tasca té l'hora especificada 
	     */
	    if (agenda.es_modificable(comanda.tasca())){
	     agenda.set_data(comanda.tasca(), {agenda.get_dia(),Hora(comanda.hora())}); 
	    }
	    else cout << "Hi ha hagut un error" << endl;
	}
	if (comanda.nombre_dates()!=0){
	    /*  \pre la tasca existeix i no és del passat
	     *  \post la tasca té la data especificada
	     */
	    if (agenda.es_modificable(comanda.tasca())){
	     agenda.set_data(comanda.tasca(), {Dia(comanda.data(1)),agenda.get_hora()}); 
	    }   
	    else cout << "Hi ha hagut un error" << endl;
	}
  }
  else if (comanda.es_rellotge()) {
	
	if (comanda.es_consulta()){
	    /*  \pre true
	     *  \post s'ha escrit el rellotge pel canal de sortida estàndar
	     */
	    agenda.print_rellotge();
	}
	if (comanda.nombre_dates()!=0) {
	    /*  \pre  la data no és passada
	     *  \post el rellotge marca la data especificada 
       */
	    if (not agenda.es_passat({comanda.data(1),comanda.hora()})){
	    agenda.set_rellotge({Dia(comanda.data(1)),agenda.get_hora()});
	    }
	    else cout << "Hi ha hagut un error" << endl;
	}
	if (comanda.te_hora()) {
   	  /*  \pre  la hora no és passada
	     *  \post el rellotge marca la hora especificada 
       */ 
	    if (not agenda.es_passat({agenda.get_dia(),comanda.hora()})){
	    agenda.set_rellotge({agenda.get_dia(),Hora(comanda.hora())});
	    }
	    else cout << "Hi ha hagut un error" << endl;
	}
  }
  else if (comanda.es_esborrat()) {
	if (comanda.tipus_esborrat() == "tasca") {
        /*  \pre la tasca existeix i no és del passat
         *  \post la agenda no conté la tasca
	       */
	if (agenda.es_modificable(comanda.tasca())){
	    agenda.del_tasca(comanda.tasca()); 
	}
	else cout << "Hi ha hagut un error" << endl;
	}
	else if (comanda.tipus_esborrat() == "etiquetes") {
        /*  \pre la tasca existeix i no és del passat
         *  \post la tasca no té etiquetes
	       */
	if (agenda.es_modificable(comanda.tasca())){
	    agenda.del_etiquetes(comanda.tasca()); 
	}
	else cout << "Hi ha hagut un error" << endl;
	}
	else if (comanda.tipus_esborrat() == "etiqueta" ) {
        /*  \pre la tasca existeix i no és del passat
         *  \post la agenda no conté la etiqueta especificada
	       */
	if (agenda.es_modificable(comanda.tasca())){
	     agenda.del_etiqueta(comanda.tasca(), comanda.etiqueta(0));  
	}
	else cout << "Hi ha hagut un error" << endl;
	}
  }
  }
}
