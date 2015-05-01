/**
 * \file Agenda.hh
 * \brief Especificació de la classe Agenda
 */
#ifndef _AGENDA_HH_
#define _AGENDA_HH_
#include <map>
#include <string>
#include "Data.hh"
#include "Tasca.hh"
using namespace std;

class Agenda {
    /** \class Agenda
     *  \brief Representa una agenda amb un conjunt de tasques amb etiquetes
     *  \invariant
     *      1. No hi han tasques amb la mateixa data
     *      2. No es poden modificar les tasques del passat
     */
    private:
        pair<Data, map<Data,Tasca>::const_iterator> rellotge;
        map<Data, Tasca> tasques;
        map<string, map<Data, Tasca*> > etiquetes;
        map<Data, Tasca*> menu;

    public:
        /** \brief Constructor d'una agenda per defecte
         *  \pre true
         *  \post el p.i és una agenda buida amb rellotge
         */
        Agenda();

        // Modificadores
        /** \brief Avança el rellotge
         *  \param[in] data data fins on avançar
         *  \pre el rellotge del p.i és anterior a \e data
         *  \post el rellotge del p.i marca \e data
         */
        void set_rellotge(Data data);

        /** \brief Afegeix una tasca
         *  \param[in] titol títol de la tasca a afegir
         *  \param[in] data data de la tasca a afegir
         *  \pre \e data és posterior al rellotge del p.i
         *  \post el p.i conté una tasca amb títol \e titol i data \e data
         */
        void add_tasca(string titol, Data data);

        /** \brief Canvia el títol d'una tasca del menú
         *  \param[in] id nº de la tasca al menú
         *  \param[in] titol nou títol de la tasca
         *  \pre  1 <= \e id <= mida_menu
         *  \post la tasca \e id del menú té com a títol \e titol
         */
        void set_titol(int id, string titol);

        /** \brief Canvia la data d'una tasca del menú
         *  \param[in] id nº de la tasca al menú
         *  \param[in] data nova data de la tasca
         *  \pre 1 <= \e id <= mida_menu, rellotge p.i < \e data
         *  \post la tasca \e id del menú té com a data \e titol
         */
        void set_data(int id, Data data);

        /** \brief Afegeix una etiqueda a una tasca del menú
         *  \param[in] id nº de la tasca al menú
         *  \param[in] etiqueta etiqueta a afegir
         *  \pre  1 <= \e id <= mida_menu
         *  \post la tasca \e id del menú té l'etiqueta \e etiqueta
         */
        void add_etiqueta(int id, string etiqueta);

        /** \brief Esborra una etiqueda d'una tasca del menú
         *  \param[in] id nº de la tasca al menú
         *  \param[in] etiqueta etiqueta a esborrar
         *  \pre  1 <= \e id <= mida_menu
         *  \post la tasca \e id no té l'etiqueta \e etiqueta
         */
        void del_etiqueta(int id, string etiqueta);

        /** \brief Esborra totes les etiquedes d'una tasca del menú
         *  \param[in] id nº de la tasca al menú
         *  \pre  1 <= \e id <= mida_menu
         *  \post la tasca \e id del menú no té cap etiqueta
         */
        void del_etiquetes(int id);

        /** \brief Esborra una tasca del menú
         *  \param[in] id nº de la tasca al menú
         *  \pre 1 <= \e id <= mida_menu
         *  \post el p.i no conté la tasca \e id del menú
         */
        void del_tasca(int id);

        // Consultores
        /** \brief Consulta mida del menú
         *  \return mida del menu del p.i
         *  \pre true
         *  \post 0 <= mida
         */
        int mida_menu() const;

        /** \brief Consulta el rellotge
         *  \pre true
         *  \post s'ha escrit el rellotge pel canal de sortida estàndar
         */
        void get_rellotge() const;

        /** \brief Genera el menu corresponen a la búsqueda
         *  \param[in] data1 cota temporal inferior de la búsqueda
         *  \param[in] data2 cota temporal superior de la búsqueda
         *  \param[in] expressio expressió booleana sobre les etiquetes
         *  \pre rellotge del p.i < \e data1 <= \e data2
         *  \post el menú conté les tasques amb data [\e data1, \e data2[ amb un
         *  conjunt d'etiquetes que compleix \e expressio
         */
        void get_tasques(Data data1, Data data2, string expressio);

        // Escriptura
        /** \brief Escriu totes les tasques del passat
         * \pre true
         * \post es mostren totes les tasques amb data < rellotge del p.i
         */
        void get_passat() const;
#endif
