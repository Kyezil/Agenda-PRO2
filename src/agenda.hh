/**
 * \file agenda.hh
 * \brief Classe Agenda
 */
#ifndef AGENDA_HH
#define AGENDA_HH
/// \cond HIDE
#include <map>
#include <string>
#include <sstream>
#include <list>
#include <iostream>
/// \endcond
#include "tasca.hh"
#include "data.hh"
using namespace std;

/** \class Agenda
 *  \brief Representa una agenda amb un conjunt de tasques amb etiquetes
    \par Notació
    -# Una data és "del passat" o "passada" si és anterior al rellotge intern.
    -# Una tasca és "del passat" si la seva data associada ho és.
    \invariant
    - Rellotge intern
        -# Indica el que es considera com el "present"
        -# Només es pot avançar (viatges al passat prohibits)
    - Conjunt de tasques
        -# Cada tasca té una única data i no hi ha dues tasques amb la mateixa data
        -# El rellotge intern separa les tasques passades (anteriors) de les que no ho són
        -# Una tasca passada no admet modificacions ni esborrament
 */
class Agenda {
    public:
        /** \brief Constructor d'una agenda per defecte
         *  \pre true
         *  \post el p.i és una agenda buida amb rellotge al 20.04.15 00:00 */
        Agenda();

        //Modificadores
        /** \brief Avança el rellotge
         *  \param[in] data data fins on avançar
         *  \pre no is_passat(data)
         *  \post el rellotge del p.i marca \e data */
        void set_rellotge(Data data);

        /** \brief Afegeix una tasca
         *  \param[in] data la data de la tasca a afegir
         *  \param[in] tasca la tasca a afegir
         *  \pre  no is_passat(data)
         *  \post si retorna true el p.i conté la tasca t */
        bool add_tasca(const Data &data, const Tasca& t);

        /** \brief Canvia el títol d'una tasca del menú
         *  \param[in] id nº de la tasca al menú
         *  \param[in] titol nou títol de la tasca
         *  \pre true
         *  \post si retorna true, la tasca \e id del menú té com a títol \e titol */
        bool set_titol(const int id, string titol);

        /** \brief Canvia el dia d'una tasca del menú
         *  \param[in] id nº de la tasca al menú
         *  \param[in] d nou dia de la tasca
         *  \pre  true
         *  \post si retorna true, la tasca \e id del menú té com a dia \e d */
        bool set_dia(const int id, Dia d);

        /** \brief Canvia la hora d'una tasca del menú
         *  \param[in] id nº de la tasca al menú
         *  \param[in] h nova hora de la tasca
         *  \pre  true
         *  \post si retorna true, la tasca \e id del menú té com a hora \e h */
        bool set_hora(const int id, Hora h);

        /** \brief Canvia la data d'una tasca del menú
         *  \param[in] id nº de la tasca al menú
         *  \param[in] d nova data de la tasca
         *  \pre  true
         *  \post si retorna true, la tasca \e id del menú té com a data \e d */
        bool set_data(const int id, Data d);

        /** \brief Afegeix una etiqueda a una tasca del menú
         *  \param[in] id nº de la tasca al menú
         *  \param[in] etiqueta etiqueta a afegir
         *  \pre  true
         *  \post si retorna true, la tasca \e id del menú té l'etiqueta \e etiqueta */
        bool add_etiqueta(const int id, string etiqueta);

        /** \brief Esborra una etiqueda d'una tasca del menú
         *  \param[in] id nº de la tasca al menú
         *  \param[in] etiqueta etiqueta a esborrar
         *  \pre  true
         *  \post si retorna true, la tasca \e id no té l'etiqueta \e etiqueta */
        bool del_etiqueta(const int id, const string etiqueta);

        /** \brief Esborra totes les etiquedes d'una tasca del menú
         *  \param[in] id nº de la tasca al menú
         *  \pre true
         *  \post si retorna true, la tasca \e id del menú no té cap etiqueta */
        bool del_etiquetes(const int id);

        /** \brief Esborra una tasca del menú
         *  \param[in] id nº de la tasca al menú
         *  \pre true
         *  \post si retorna true, el p.i no conté la tasca \e id del menú */
        bool del_tasca(const int id);

        // Consultores
        /** \brief Consulta si una data és passada
         *  \param[in] data la data a avaluar
         *  \pre true
         *  \post retorna si data és anterior al rellotge del p.i */
        bool is_passat(const Data &data) const;

        /** \brief  Obté el dia del rellotge
         *  \pre true
         *  \post retorna el dia del rellotge del p.i */
        Dia get_dia() const;

        /** \brief  Obté la hora del rellotge
         *  \pre true
         *  \post retorna la hora del rellotge del p.i */
        Hora get_hora() const;

        /** \brief Genera el menu de les tasques d'un interval que compleixen una expressió
         *  \param[in] dia1 inici de l'interval temporal
         *  \param[in] dia2 final de l'interval temporal
         *  \param[in] expressio expressió booleana ben parentitzada (opcional)
         *  \pre true
         *  \post el menú conté les tasques amb data en [\e data1, \e data2] no passades
         *  amb un conjunt d'etiquetes que compleix \e expressio i es mostra el menú */
        void consulta(Dia dia1, Dia dia2, string expressio = "");

        /** \brief Genera el menu del tasques d'un dia que compleixen una expressió
         *  \param[in] dia dia on han d'estar les tasques
         *  \param[in] expressio expressió booleana ben parentitzada (opcional)
         *  \pre true
         *  \post el menú conté les tasques no passades amb dia \e dia i un un conjunt
         *  d'etiquetes que compleix \e expressio i es mostra el menú */
        void consulta(Dia dia, string expressio = "");

        /** \brief Genera el menu de les tasques que compleixen una expressió \n
         * En aquest cas no hi ha cap restricció temporal, sinó que es busca en totes
         *  \pre true
         *  \post el menú conté les tasques no passades amb un conjunt d'etiquetes que
         *  compleix expressio i es mostra el menú */
        void consulta(string expressio = "");

        // Escriptura
        /** \brief Escriu totes les tasques del passat
         * \pre true
         * \post s'han mostrat pel canal estàndar de sortida totes les tasques anteriors
         * al rellotge del p.i */
        void passat();

    private:
        /** \invariant
         *  - Conjunt etiquetes
         *      -# El cjt d'etiquetes està ordenat lexicogràficament
         *      -# Cada cjt de tasques és un subconjunt ordenat de tasques no passades
         *      -# Cada etiqueta té un únic cjt de tasques associat i viceversa
         *      -# El cjt de tasques de cada etiqueta conté almenys 1 element (no buits)
         */
        /// Un instant itera sobre el conjunt de les tasques
        typedef map<Data, Tasca>::iterator instant;
        /// Un cinstant és un instant sense dret a modificació
        typedef map<Data, Tasca>::const_iterator cinstant;

        /** \struct Ordre instant
         *  \brief Defineix l'ordre entre instants */
        struct ordre_instant {
            /** \brief Ordre entre instants
             *  \param[in] a lhs
             *  \param[in] b rhs
             *  \pre a i b són instants vàlids
             *  \post retorna si la tasca apuntada per a és anterior a la de b */
            bool operator()(const instant& a, const instant& b) const;
        };

        /// Un set_instant és un conjunt d'instants ordenats per ordre_instant
        typedef set<instant, ordre_instant> set_instant;
        /// Un tag_map és un map de tag al seu conjunt d'instants
        typedef map<string, set_instant> tag_map;

        /// Rellotge: data concreta a la qual està i instant a la primera tasca no passada
        pair<Data, instant> clock_;
        /// Conjunt de tasques: guarda les tasques ordenades i associades per la seva data
        map<Data, Tasca> tasks_;
        /// Catàleg d'etiquetes: associa a cada etiqueta el cjt de tasques que la tenen
        map<string, set_instant> tags_;
        /// Menú: guarda les tasques corresponents a la última consulta
        list<instant> menu_;


        /** \brief Indica si es pot modificar la tasca #id del menu
         * \param[in] id número de la tasca en el menu
         * \pre true
         * \post si es pot modificar retorna un iterador a l'element id-èssim del menú;
         *  si no, retorna false */
        pair<list<instant>::iterator, bool> menu_item(const int id);

        /** \brief Afegeix una tasca (private)
         *  \param[in] data la data de la tasca a afegir
         *  \param[in] tasca la tasca a afegir
         *  \return iterator a la tasca inserida i bool si s'ha pogut inserir
         *  \pre  no is_passat(data)
         *  \post si return.second, el p.i conté la tasca t i return.first és un
         *  instant que hi apunta */
        pair<instant, bool> p_add_tasca(const Data& data, const Tasca& t);

        /** \brief Modifica la data d'una tasca del menú
         *  \param[in]
         *  \pre true
         *  \post si no existeix una tasca amb data d, la tasca del menú apuntada per
         *  it té com a data d. Retorna si s'ha pogut fer la modificació */
        bool p_set_data(list<instant>::iterator& it, Data d);

        /** \brief Genera i escriu el menú d'un interval de tasques
         *  Genera i escriu el menú (alhora) de totes les tasques entre in1 i in2,
         *  [in1,in2) és un interval del cjt de tasques
         *  \param[in] in1 inici de l'interval
         *  \param[in] in2 final de l'interval
         *  \pre in1 apunta a una tasca no passada i in2 apunta a una tasca no anterior a
         *  la de in1 (informalment: rellotge del p.i <= *in1 <= *in2); i el menú està buit
         *  \post el menú conté les tasques de [*in1, *in2) i s'ha mostrat el menú */
        void menu_directe(instant& in1, instant& in2);

        /** \brief Genera i escriu el menú d'un interval de tasques
         *  Genera i escriu el menú (alhora) de totes les tasques entre in1 i in2,
         *  [in1, in2) és un interval del cjt de tasques associat a una etiqueta
         *  \param[in] in1 inici de l'interval
         *  \param[in] in2 final de l'interval
         *  \pre in1 apunta a una tasca no passada i in2 apunta a una tasca no anterior a
         *  la de in1 (informalment: rellotge del p.i <= in1 <= in2); i el menú està buit
         *  \post el menú conté les tasques de [in1, in2) i s'ha mostrat el menú */
        void menu_directe(set_instant::iterator& in1, set_instant::iterator& in2);

        /** \brief Fusiona 2 rangs de tasques fent la intersecció
         *  \param[in] in1 inici del 1r operand
         *  \param[in] in2 final del 1r operand
         *  \param[in][out] l 2n operand i contenidor de la intersecció
         *  \pre in1 i in2 són iteradors a contenidors d'instants
         *  \post l conté la intersecció de [in1, in2) amb l */
        template<typename Iterator>
        void merge_and(Iterator in1, Iterator in2, list<instant>& l);

        /** \brief Fusiona 2 rangs de tasques fent la unió
         *  \param[in] in1 inici del 1r operand
         *  \param[in] in2 final del 1r operand
         *  \param[in][out] l 2n operand i contenidor de la unió
         *  \pre in1 i in2 són iteradors a contenidors d'instants
         *  \post l conté la reunió de [in1, in2) amb l */
        template<typename Iterator>
        void merge_or(Iterator in1, Iterator in2, list<instant>& l);

        /** \brief Llegeix una etiqueta d'una expressió
         *  \param[in] exp expressió d'on s'ha d'extreure l'etiqueta
         *  \pre exp és una part d'una expressió booleana on el 1r caràcter és el 1r
         *  caràcter de l'etiqueta a extreure
         *  \post es retorna l'etiqueta extreta i s'ha consumit l'etiqueta de exp */
        string extract_tag(istringstream& exp);

        /** \brief Obté una cota equivalent en el cjt d'instant d'una etiqueta
         * Obté un iterador que apunta al primer instant del cjt de tags *tag que no és
         * anterior a in \n
         * Esquema : * representa una tasca, X és "in" i Y el "return" \n
         * Cjt general:  * * * * * * * * * X * * * * * * * * \n
         * Cjt etiqueta: *     *   *         Y           *
         *  \param[in] tag iterador que apunta al cjt d'instants que s'ha d'acotar
         *  \param[in] in instant amb el qual volem acotar el conjunt tag
         *  \pre tag és vàlid (no apunta a l'end)
         *  \post retorna un iterador del cjt d'instant d'una etiqueta tal que els
         *  elements que hi són anteriors i posteriors també ho són respecte in;
         *  si no n'hi ha cap retorna un iterador al final (end) */
        set_instant::iterator safe_bound(tag_map::iterator& tag, const instant& in);

        /** \brief Avalua una expressió parentitzada en un interval d'instants
         * Avalua una expressió booleana parentitzada que comença per un '(' fins al
         * parèntesi tancant ')' corresponent, deixant al flux la part no evaluada
         *  \param[in] in1 inici de l'interval on avaluar
         *  \param[in] in2 final de l'interval on avaluar
         *  \param[in] exp flux de l'expressió parentitzada
         *  \param[out][in] l contenidor on es guarda el resultat
         *  \pre in1 apunta a un element no passat i in2 és posterior a in1 \n
         *       exp conté, al seu principi, una expressió booleana de la forma: \n
         *       exp: (e.e) | (e,e)   e:  exp  | etiqueta \n
         *      ; l és una llista buida ; exp = EXP \n
         *  \post l conté les tasques en [in1,in2) que compleixen l'expressió delimitada
         *  pel primer '(' fins al ')' corresponent, s'ha consumit aquesta expressió
         *  de exp */
        void exp_parentitzada(const instant& in1, const instant& in2, istringstream& exp, list<instant>& l);

        /** \brief Escriure una línia del menú
         *  \param[in] i número de la línia
         *  \param[in] it cinstant apuntant a l'entrada a escriure
         *  \pre it és valid (!= end)
         *  \post s'ha escrit pel canal de sortida estàndar una línia en format:
         *  %i titol_tasca data_tasca etiquetes% */
        void print_menu_item(int i, const cinstant& it) const;

        /** \brief Escriure el menú
         *  \pre true
         *  \post s'ha escrit pel canal de sortida estàndar 1 línia per a cada element
         *  del menú seguint el format de print_menu_item */
        void print_menu() const;
};
#endif
