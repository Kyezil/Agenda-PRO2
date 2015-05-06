/**
 * \file agenda.hh
 * \brief Classe Agenda
 */

#ifndef AGENDA_HH
#define AGENDA_HH

/// \cond HIDE
#include <map>
#include <string>
#include <vector>
/// \endcond
#include "tasca.hh"
#include "data.hh"
using namespace std;

/** \class Agenda
 *  \brief Representa una agenda amb un conjunt de tasques amb etiquetes
    \invariant 
    - No hi han tasques amb la mateixa data
    - No es poden modificar les tasques del passat
     
    \par Notació
    -# Una data és "del passat" o "passada" si és anterior al rellotge del p.i.
    -# Una tasca és "del passat" si la seva data associada ho és.
 */
class Agenda {
    private:
        pair<Data, map<Data,Tasca>::const_iterator> rellotge;
        map<Data, Tasca> tasques;
        map<string, map<Data, Tasca*> > etiquetes;
        map<Data, Tasca*> menu_map;
        vector<pair<Data, Tasca*> > menu;

    public:
        /** \brief Constructor d'una agenda per defecte
         *  \pre true
         *  \post el p.i és una agenda buida amb rellotge
         */
        Agenda();

        //Modificadores
        /** \brief Avança el rellotge
         *  \param[in] data data fins on avançar
         *  \pre no es_passat(data)
         *  \post si el rellotge del p.i marca \e data */
        void set_rellotge(Data data);

        /** \brief Afegeix una tasca
         *  \param[in] titol títol de la tasca a afegir
         *  \param[in] data data de la tasca a afegir
         *  \pre no es_passat(data) i no existeix(data)
         *  \post el p.i conté una tasca amb títol \e titol i data \e data */
        void add_tasca(string titol, Data data);

        /** \brief Canvia el títol d'una tasca del menú
         *  \param[in] id nº de la tasca al menú
         *  \param[in] titol nou títol de la tasca
         *  \pre es_modificable(id)
         *  \post la tasca \e id del menú té com a títol \e titol */
        void set_titol(int id, string titol);

        /** \brief Canvia la data d'una tasca del menú
         *  \param[in] id nº de la tasca al menú
         *  \param[in] data nova data de la tasca
         *  \pre  es_modificable(id) i no existeix(data)
         *  \post la tasca \e id del menú té com a data \e data */
        void set_data(int id, Data data);

        /** \brief Afegeix una etiqueda a una tasca del menú
         *  \param[in] id nº de la tasca al menú
         *  \param[in] etiqueta etiqueta a afegir
         *  \pre  es_modificable(id)
         *  \post la tasca \e id del menú té l'etiqueta \e etiqueta
         */
        void add_etiqueta(int id, string etiqueta);

        /** \brief Esborra una etiqueda d'una tasca del menú
         *  \param[in] id nº de la tasca al menú
         *  \param[in] etiqueta etiqueta a esborrar
         *  \pre  es_modificable(id)
         *  \post la tasca \e id no té l'etiqueta \e etiqueta
         */
        void del_etiqueta(int id, string etiqueta);

        /** \brief Esborra totes les etiquedes d'una tasca del menú
         *  \param[in] id nº de la tasca al menú
         *  \pre  es_modificable(id)
         *  \post la tasca \e id del menú no té cap etiqueta
         */
        void del_etiquetes(int id);

        /** \brief Esborra una tasca del menú
         *  \param[in] id nº de la tasca al menú
         *  \pre es_modificable(id)
         *  \post el p.i no conté la tasca \e id del menú */
        void del_tasca(int id);

        // Consultores
        /** \brief Consulta si hi ha una tasca en una data
         *  \param[in] data data de la tasca
         *  \pre true
         *  \post retorna si existeix una tasca amb data \e data */
        bool existeix(Data data) const;

        /** \brief Consulta si una data és passada
         *  \param[in] data la data a evaluar
         *  \pre true
         *  \post retorna (data anterior al rellotge del p.i) */
        bool es_passat(Data data) const;

        /** \brief Consulta si es pot modificar una tasca del menú
         *  \param[in] id nº de la tasca a modificar
         *  \pre true
         *  \post retorna si es pot modificar la tasca \e id del menú */
        bool es_modificable(int id) const;

        /** \brief Consulta el rellotge
         *  \pre true
         *  \post s'ha escrit el rellotge pel canal de sortida estàndar */
        void print_rellotge() const;

        /** \brief  Obté el dia del rellotge
         *  \pre true
         *  \post retorna el dia del rellotge del p.i */
        Dia get_dia() const;

        /** \brief  Obté la hora del rellotge
         *  \pre true
         *  \post retorna el rellotge del rellotge del p.i */
        Hora get_hora() const;

        /** \brief Genera el menu per busqueda en rang i expressió
         *  \param[in] dia1 cota temporal inferior de la búsqueda
         *  \param[in] dia2 cota temporal superior de la búsqueda
         *  \param[in] expressio expressió booleana sobre les etiquetes
         *  \pre true
         *  \post el menú conté les tasques amb data en [\e data1, \e data2] no passades
         *        tal que el conjunt d'etiquetes de les quals compleix \e expressio
         *        i es mostra el menú */
        void consulta(Dia dia1, Dia dia2, string expressio = "");

        /** \brief Genera el menu corresponen a la búsqueda en un dia
         *  \param[in] dia dia en què s'ha de buscar
         *  \param[in] expressio expressió booleana sobre les etiquetes
         *  \pre true
         *  \post el menú conté les tasques no passadaes amb dia \e dia tal que
         *        el conjunt d'etiquetes de les quals compleix \e expressio
         *        i es mostra el menú */
        void consulta(Dia dia, string expressio = "");

        /** \brief Genera el menu de les tasques no passades
         *  \pre true
         *  \post el menú conté les tasques no passades i es mostra */
        void consulta();

        // Escriptura
        /** \brief Escriu totes les tasques del passat
         * \pre true
         * \post es mostren totes les tasques del passat */
        void passat() const;
};
#endif
