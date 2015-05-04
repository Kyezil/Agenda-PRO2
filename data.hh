/** \file data.hh
    \brief Especificació de Data (Dia i Hora)
*/
#ifndef DATA_HH
#define DATA_HH
#include <utility>
#include <string>
using namespace std;

/** \struct Dia
    \brief Representa una dia , dia.mes.any
*/
struct Dia {
    int any;
    int mes;
    int dia;
    /** /invariant 0 <= \b any <= 99
     *             1 <= \b mes <= 12
     *             0 <= \b dia <= 31  */

    /** \brief Construeix Dia a partir d'un string
     *  \param[in] s string que conté un dia  "dia.mes.any"
     *  \pre \e s té el format DD.MM.AA
     *  \post el p.i conté la data representada per \e s */
    Dia(string s);

    /** \brief Indica ordre entre dies (<).
     *  \param[in] d rhs dia
     *  \return (p.i < d)
     *  \pre true
     *  \post retorna cert i el p.i és anterior a \e d  */
   bool operator<(const Dia &d) const;
};

/** \struct Hora
    \brief Representa una hora , hora:minut
*/
struct Hora {
    int hora;
    int minut;
    /** /invariant 0 <= \b hora <= 23
     *             0 <= \b minut <= 59

    /** \brief Construeix Hora a partir d'un string
     *  \param[in] s string que conté un dia  "hora:minut"
     *  \pre \e s té el format HH:MM
     *  \post el p.i conté la hora representada per \e s*/
    Hora(string s);
    
    /** \brief Indica ordre entre hores (<).
     *  \param[in] d rhs hora
     *  \return (p.i < h)
     *  \pre true
     *  \post retorna cert i el p.i és anterior a \e h */
   bool operator<(const Hora&d) const;
};

typedef pair<Dia, Hora> Data;
#endif
