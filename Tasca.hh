/**
 * \file  Tasca.hh
 * \brief Especificació de la classe Tasca
 */
#ifndef _TASCA_HH_
#define _TASCA_HH_
#include <string>
#include <set>
using namespace std;

class Tasca {
    private:
        string titol;
        /// \invariant \b etiquetes no conté elements repetits
        set<string> etiquetes; 
    public:
        /** \brief Constructor per defecte
         *  \pre true
         *  \post el p.i és una tasca sense etiquetes
         */
        Tasca();

        /** \brief Constructor de tasca amb titol
         *  \pre true
         *  \post el p.i és una tasca de \b titol = \e titol
         */
        Tasca(string titol);

        /** \brief Modifica el títol de la tasca
         *  \pre true
         *  \post el \b titol del p.i és \e titol
         */
        void modificar_titol(string titol);

        /** \brief Afegeix una etiqueta a la tasca
         *  \pre true
         *  \post el p.i té una etiqueta \e etiq
         */
        void afegir_etiqueta(string etiq);

        /** \brief Esborrar una etiqueta de la tasca
         *  \pre true
         *  \post el p.i no té com a etiqueta \e etiq
         */
        void esborrar_etiqueta(string etiq);
};
#endif
