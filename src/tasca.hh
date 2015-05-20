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
 *  \invariant 
 *  - Una tasca no té etiquetes repetides
 */
class Tasca {
    private:
        string titol;
        set<string> etiquetes; 
    public:
        typedef set<string>::const_iterator tag_iterator;//< iterador per les etiquetes

        /** \brief Constructor per defecte
         *  \pre true
         *  \post el p.i és una tasca sense etiquetes */
        Tasca();

        /** \brief Constructor de tasca amb titol
         *  \param [in] titol títol de la tasca a crear
         *  \pre true
         *  \post el p.i és una tasca de titol \e titol sense etiquetes */
        Tasca(string titol);

        /** \brief Modifica el títol de la tasca
         *  \param [in] titol nou títol de la tasca
         *  \pre true
         *  \post el titol del p.i és \e titol */
        void set_titol(string titol);

        /** \brief Afegeix una etiqueta a la tasca
         *  \param [in] etiq etiqueta a afegir
         *  \pre true
         *  \post el p.i té una etiqueta \e etiq */
        void add_etiqueta(string etiq);

        /** \brief Esborrar una etiqueta de la tasca
         *  \param [in] etiq etiqueta a esborrar
         *  \pre true
         *  \post el p.i no té com a etiqueta \e etiq */
        void del_etiqueta(const string etiq);

        /** \brief Esborrar totes les etiquetes de la tasca
         *  \pre true
         *  \post el p.i no té etiquetes */
        void del_etiquetes();

        /** \brief Obté un iterador al principi de les etiquetes
         *  \pre true
         *  \post retorna un iterador a la primera de les etiquetes,
         *                end_etiqueta() si no n'hi ha */
        tag_iterator begin_etiquetes();

        /** \brief Obté un iterator al final de les etiquetes
         *  \pre true
         *  \post retorna un iterador al l'element següent a l'última etiqueta */
        tag_iterator end_etiquetes();

        /** \brief Mostrar el títol de la tasca
         *  \param[in] t tasca de la qual volem escriure el títol
         *  \param[out] out flux de sortida
         *  \pre true
         *  \post s'ha escrit el titol del p.i a \e out */
        static void print_titol(const Tasca& t, ostream& out);

        /** \brief Mostrar les etiquetes de la tasca
         *  \param[in] t tasca, les etiquetes de la qual s'han de mostrar
         *  \param[out] out flux de sortida
         *  \pre true
         *  \post s'han escrit a \e out les etiquetes del p.i en ordre lexicogràfic */
        static void print_etiquetes(const Tasca& t, ostream& out);
};
#endif
