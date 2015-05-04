/**
 * \file  tasca.hh
 * \brief Classe Tasca
 */
#ifndef TASCA_HH
#define TASCA_HH
/// \cond HIDE
#include <string>
#include <set>
/// \endcond
using namespace std;

/** \class Tasca
 *  \brief Representa una tasca amb etiquetes associades
 */
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
         *  \param [in] titol Títol de la tasca a crear
         *  \pre true
         *  \post el p.i és una tasca de titol \e titol
         */
        Tasca(string titol);

        /** \brief Modifica el títol de la tasca
         *  \param [in] titol Nou títol de la tasca
         *  \pre true
         *  \post el titol del p.i és \e titol
         */
        void modificar_titol(string titol);

        /** \brief Afegeix una etiqueta a la tasca
         *  \param [in] etiq Etiqueta a afegir
         *  \pre true
         *  \post el p.i té una etiqueta \e etiq
         */
        void afegir_etiqueta(string etiq);

        /** \brief Esborrar una etiqueta de la tasca
         *  \param [in] etiq Etiqueta a esborrar
         *  \pre true
         *  \post el p.i no té com a etiqueta \e etiq
         */
        void esborrar_etiqueta(string etiq);
};
#endif
