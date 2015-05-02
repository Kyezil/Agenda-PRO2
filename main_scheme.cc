#include "Agenda.hh"
#include "Comanda.hh" 
#include "Data.hh"

using namespace std; 

Data string2Data (string& data, string& hora); //per implementar, no se si aquí o en un altre lloc per no embrutar

int main (){

Agenda agenda(); 
Comanda comanda;

while (true) {
if (comanda.llegir()) {
  if (comanda.es_insercio()) {
      //amb data i hora
      if (comanda.nombre_dates()!=0) {
	  agenda.add_tasca(comanda.titol(), string2Data(comanda.data(0), comanda.hora()));
      }
      //nomes hora (es posa al dia actual)
      else {
	  agenda.add_tasca(comanda.titol(), string2Data("DATA ACTUAL", comanda.hora());
      }
  }
  
  else if (comanda.es_consulta()){
        
        //totes les futures
	if (comanda.nombre_dates()==0){
	    if (not comanda.te_expressio()) agenda.get_tasques(); 
	    else agenda.get_tasques(comanda.expressio());
	}
	
	//tasques d'un dia
	else if (comanda.nombre_dates()==1) {
	     if (not comanda.te_expressio()) agenda.get_tasques(comanda.data(0)); 
	     else agenda.get_tasques(string2Data(comanda.data(0),"HORA ACTUAL"), comanda.expressio());
	}
	//tasques de A a B
	else {
	      if (not comanda.te_expressio()) agenda.get_tasques(string2Data(comanda.data(0),"HORA ACTUAL"), string2Data(comanda.data(1),"HORA ACTUAL"), comanda.expressio());
	      else agenda.get_tasques(string2Data(comanda.data(0),"HORA ACUTAL"),string2Data(comanda.data(1), "HORA ACTUAL"));
	}
  }

  else if (comanda.es_passat()){
    agenda.get_passat();
  }
  
  else if (comanda.es_modificacio()){
    
	//text
	if (comanda.te_titol()) {
	    agenda.set_titol(comanda.tasca(), comanda.titol()); 
	}
	
	//afegir etiquetes
	for (int i = 0; i < comanda.nombre_etiquetes(); ++i) {
	    agenda.add_etiqueta(comanda.tasca(), comanda.etiqueta(i));
	}

	//hora + data
	if (comanda.te_hora()) {
	    	
	    agenda.set_data(comanda.tasca(), string2Data("DATA ACTUAL",comanda.hora())); 
	}
	
	//data
	if (comanda.nombre_dates()!=0){
	     agenda.set_data(comanda.tasca(), string2Data(comanda.data(),"HORA ACTUAL")); 
	}
  }
  
  else if (comanda.es_rellotge()) {
	
	//consultar temps
	
	if (comanda.es_consulta()){
	    agenda.get_rellotge();
	}
	
	//fixar data i/o hora
	if (comanda.nombre_dates()!=0) {
	    agenda.set_rellotge(string2Data(comanda.data(),"HORA ACTUAL"));
	}
	if (comanda.te_hora) {
	    agenda.set_rellotge(string2Data("DATA ACTUAL",comanda.data()));
	}
  }
  
  else if (comanda.es_esborrat()) {
	
	if (comanda.tipus_esborrat() == "tasca") {
	    agenda.del_tasca(comanda.tasca()); 
	}
	else if (comanda.tipus_esborrat() == "etiquetes") {
	    agenda.del_etiquetes(comanda.tasca()); 
	    }
	}
	else if (comanda.tipus_esborrat() == "etiqueta" ) {
	     agenda.del_etiqueta(comanda.tasca(), comanda.etiqueta(0));  
	}    
  }
  else break;
}
}
}
