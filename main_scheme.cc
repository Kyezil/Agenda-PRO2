#include "agenda.hh"
#include "comanda.hh" 

using namespace std; 

int main (){

Agenda agenda("variables? "); 
Comanda comanda;

while (true) {
  
if (comanda.llegir()) {
  if (comanda.es_insercio()) {
      //amb data i hora
      if (comanda.nombre_dates()!=0) {
	  agenda.insereix_amb_data(comanda.titol(), comanda.data(0), comanda.hora());
      }
      //nomes hora (es posa al dia actual)
      else {
	  agenda.insereix_sense_data(comanda.titol(), comanda.hora());
      }
  }
  
  else if (comanda.es_consulta()){
        
        //totes les futures
	if (comanda.nombre_dates()==0){
	    if (not comanda.te_expressio()) agenda.consulta();
	    else agenda.consulta(comanda.expressio());
	}
	
	//tasques d'un dia
	else if (comanda.nombre_dates()==1) {
	     if (not comanda.te_expressio()) agenda.consulta(comanda.data(0); 
	     else agenda.consulta(comanda.data(0), comanda.expressio());
	}
	//tasques de A a B
	else {
	      if (not comanda.te_expressio()) agenda.consulta(comanda.data(0), comanda.data(1), comanda.expressio());
	      else agenda.consulta(comanda.data(0),comanda.data(1));
	      
	}
  }

  
  else if (comanda.es_passat()){
    agenda.escriu_passat();
  }
  
  else if (comanda.es_modificacio()){
    
	//text
	
	if (comanda.te_titol()) {
	    agenda.canviar_titol(comanda.tasca(), comanda.titol()); 
	}
	
	//afegir etiquetes
	
	for (int i = 0; i < comanda.nombre_etiquetes(); ++i) {
	    agenda.afegir_etiqueta(comanda.tasca(), comanda.etiqueta(i));
	}

	//hora
	
	if (comanda.te_hora()) {
	    agenda.canviar_hora(comanda.tasca(), comanda.hora()); 
	}
	
	//data
	
	if (comanda.nombre_dates()!=0){
	     agenda.canviar_data(comanda.tasca(), comanda.data()); 
	}
  }
  
  else if (comanda.es_rellotge()) {
	
	//consultar temps
	
	if (comanda.es_consulta()){
	    agenda.consulta_rellotge();
	}
	
	//fixar data i/o hora
	
	if (comanda.nombre_dates()!=0) {
	    agenda.avanca_data(comanda.data());
	}
	
	if (comanda.te_hora) {
	    agenda.avanca_hora(comanda.hora());
	}
  }
  
  else if (comanda.es_esborrat()) {
	
	if (comanda.tipus_esborrat() == "tasca") {
	    agenda.esborrar_tasca(comanda.tasca()); 
	}
	else if (comanda.tipus_esborrat() == "etiquetes") {
	    for (int i = 0; i < comanda.nombre_etiquetes(); ++i) {
		agenda.esborrar_etiqueta(comanda.tasca(), comanda.etiqueta(i)); 
	    }
	}
	else if (comanda.tipus_esborrat() == "etiqueta" ) {
	     agenda.esborrar_etiqueta(comanda.tasca(), comanda.etiqueta(0));  
	}    
  }
  
  else break;
}
}
}
