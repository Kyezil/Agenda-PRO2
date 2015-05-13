/**
 * \file  tasca.hh
 * \brief Classe Tasca
 */
#ifndef TASCA_HH
#define TASCA_HH
/// \cond HIDE
#include <string>
#include <set>
#include <ostream>
/// \endcond
using namespace std;

/** \class Tasca
 *  \brief Representa una tasca amb etiquetes associades
 *  \invariant
 *  - Una tasca no té etiquetes repetides
 */
class Tasca {
    private:
        string title_;
        set<string> tags_; 
    public:
        /** \brief Constructor per defecte
         *  \pre true
         *  \post el p.i és una tasca sense etiquetes
         */
        Tasca();

        /** \brief Constructor de tasca amb titol
         *  \param [in] titol títol de la tasca a crear
         *  \pre true
         *  \post el p.i és una tasca de titol \e titol sense etiquetes
         */
        Tasca(string titol);

        /** \brief Modifica el títol de la tasca
         *  \param [in] titol nou títol de la tasca
         *  \pre true
         *  \post el titol del p.i és \e titol
         */
        void set_titol(string titol);

        /** \brief Afegeix una etiqueta a la tasca
         *  \param [in] etiq etiqueta a afegir
         *  \pre true
         *  \post el p.i té una etiqueta \e etiq
         */
        void add_etiqueta(string etiq);

        /** \brief Esborrar una etiqueta de la tasca
         *  \param [in] etiq etiqueta a esborrar
         *  \pre true
         *  \post el p.i no té com a etiqueta \e etiq
         */
        void del_etiqueta(const string etiq);

        /** \brief Esborrar totes les etiquetes de la tasca
         *  \pre true
         *  \post el p.i no té etiquetes
         */
        void del_etiquetes();
        
        /** \brief Escriure el titol de la tasca
         *  \param [in] t tasca de la qual volem escriure el títol
         *  \param [out] out flux de sortida
         *  \pre true
         *  \post a \e out s'ha escrit el títol del p.i.
         */
        static void print_titol(const Tasca &t, ostream &out);
        
        /** \brief Escriu les etiquetes de la tasca
         *  \param [in] t tasca de la qual volem escriure les etiquetes
         *  \param [out] out flux de sortida
         *  \pre true
         *  \post a \e out s'han escrit les etiquetes del p.i. per ordre alfabètic
         */
        static void print_etiquetes(const Tasca &t, ostream &out);
};
#endif
