#include "Agenda.hh"
#include "Comanda.hh" 
#include "Data.hh"

using namespace std; 

int main (){

Agenda agenda(); 
Comanda comanda;

while (comanda.llegir()) {
  if (comanda.es_insercio()) {
     if (comanda.nombre_dates()!=0) {
      	/*  \pre la data no es del passat i no existeix cap tasca amb la mateixa data a la agenda
         *  \post a agenda s'ha afegit una tasca amb el títol i la data especificats 
         */
	  agenda.add_tasca(comanda.titol(), {Data(comanda.data(0)), Hora(comanda.hora())});
      }
      else {
       	/*  \pre no existeix cap tasca a la data actual 
         *  \post a agenda s'ha afegit una tasca amb el títol especificat al dia actual i 
	       *        l'hora especificada
         */
	  agenda.add_tasca(comanda.titol(), {agenda.get_dia(), Hora(comanda.hora())});
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
		agenda.consulta(comanda.data(0));
	      }	
	      else {
	        /*  \pre true
		 *  \post s'ha generat i es mostra per pantalla un menú amb les tasques del dia especificat 
		 *        que compleixen l'expressio
		 */
		agenda.consulta({comanda.data(0),agenda.get_hora()}, comanda.expressio());
	      }
	}
	else {
	      if (not comanda.te_expressio()) {
		/*  \pre true
		 *  \post s'ha generat i es mostra per pantalla un menú amb les tasques entre els dies especificats
		 */
		  agenda.consulta({comanda.data(0),agenda.get_hora()}, {comanda.data(1),agenda.get_hora()});
	      }
	      else { 
		/*  \pre true
		 *  \post s'ha generat i es mostra per pantalla un menú amb les tasques entre els dies especificats 
		 *        que compleixen l'expressio
		 */
		  agenda.consulta({comanda.data(0),agenda.get_hora()},{comanda.data(1), agenda.get_hora()}, comanda.expressio());
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
	    agenda.set_titol(comanda.tasca(), comanda.titol()); 
	}
	for (int i = 0; i < comanda.nombre_etiquetes(); ++i) {
      /*  \inv la tasca té les primeres i etiquetes especificades
       *  \pre la tasca existeix i no és del passat
	     *  \post la tasca té l'etiqueta especificada
	     */
	    agenda.add_etiqueta(comanda.tasca(), comanda.etiqueta(i));
	}
	if (comanda.te_hora()) {
	    /*  \pre la tasca existeix i no és del passat
	     *  \post la tasca té l'hora especificada 
	     */
	     agenda.set_data(comanda.tasca(), {agenda.get_dia(),Hora(comanda.hora())}); 
	}
	if (comanda.nombre_dates()!=0){
	    /*  \pre la tasca existeix i no és del passat
	     *  \post la tasca té la data especificada
	     */
	     agenda.set_data(comanda.tasca(), {Dia(comanda.data()),agenda.get_hora()}); 
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
	    agenda.set_rellotge({Dia(comanda.data()),agenda.get_hora()});
	}
	if (comanda.te_hora) {
   	  /*  \pre  la hora no és passada
	     *  \post el rellotge marca la hora especificada 
       */
	    agenda.set_rellotge({agenda.get_dia(),Dia(comanda.data())});
	}
  }
  else if (comanda.es_esborrat()) {
	if (comanda.tipus_esborrat() == "tasca") {
        /*  \pre la tasca existeix i no és del passat
         *  \post la agenda no conté la tasca
	       */
	    agenda.del_tasca(comanda.tasca()); 
	}
	else if (comanda.tipus_esborrat() == "etiquetes") {
        /*  \pre la tasca existeix i no és del passat
         *  \post la tasca no té etiquetes
	       */
	    agenda.del_etiquetes(comanda.tasca()); 
	    }
	}
	else if (comanda.tipus_esborrat() == "etiqueta" ) {
        /*  \pre la tasca existeix i no és del passat
         *  \post la agenda no conté la etiqueta especificada
	       */
	     agenda.del_etiqueta(comanda.tasca(), comanda.etiqueta(0));  
	}    
  }
}
