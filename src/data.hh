/** \file data.hh
    \brief Definició de Data (Dia i Hora)
*/
#ifndef DATA_HH
#define DATA_HH
/// \cond HIDE
#include <utility>
#include <string>
/// \endcond HIDE
using namespace std;

/** \struct Dia
    \brief Representa un dia, dia.mes.any
*/
struct Dia {
    int any; ///< 0 <= any <= 99
    int mes; ///< 1 <= mes <= 12
    int dia; ///< 1 <= dia <= 31

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
    \brief Representa una hora, hora:minut
*/
struct Hora {
    int hora; ///< 0 <= hora <= 23
    int minut; ///< 0 <= minut <= 59
    
    /** \brief Construeix Hora a partir d'un string
     *  \param[in] s string que conté un dia  "hora:minut"
     *  \pre \e s té el format HH:MM
     *  \post el p.i conté la hora representada per \e s */
    Hora(string s);

    /** \brief Indica ordre entre hores (<).
     *  \param[in] h rhs hora
     *  \return (p.i < h)
     *  \pre true
     *  \post retorna cert i el p.i és anterior a \e h */
   bool operator<(const Hora &h) const;
};

typedef pair<Dia, Hora> Data;
#endif
