/**
 * \file  Tasca.hh
 * \brief Especificació de la classe Tasca
 */
#ifndef _TASCA_HH_
#define _TASCA_HH_
#include <string>
#include <set>
#include "Data.hh"

class Tasca {
    private:
        string titol;

        /// \invariant \b etiquetes no conté etiquetes repetides
        set<string> etiquetes; 
    public:
        /** \brief Modifica el títol de la tasca
         *  \pre true
         *  \post el títol del p.i és \e titol
         */
        modificar_titol(string& titol);


        /** \brief Afegeix una etiqueta a la tasca
         *  \pre true
         *  \post el p.i té una etiqueta \e etiq
         */
        afegir_etiqueta(string& etiq);

        /** \brief Esborrar una etiqueta de la tasca
         *  \pre true
         *  \post el p.i no té com a etiqueta \e etiq
         */
        esborrar_etiqueta(string& etiq);
}
#endif
