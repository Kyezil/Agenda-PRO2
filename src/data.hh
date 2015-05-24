/** \file data.hh
  \brief Definició de Data (Dia i Hora)
  */
#ifndef DATA_HH
#define DATA_HH
/// \cond HIDE
#include <utility>
#include <string>
#include <ostream>
/// \endcond HIDE
using namespace std;

/** \class Dia
  \brief Representa un dia, dia.mes.any
  */
class Dia {
    private:
        int dia; ///< 1 <= dia <= 31
        int mes; ///< 1 <= mes <= 12
        int any; ///< 0 <= any <= 99

    public:
        /** \brief Constructor per defecte
         *  \pre true
         *  \post el p.i no té valors per defecte */
        Dia() = default;

        /** \brief Constructor explícit amb dia, mes i any
         *  \pre els paràmetres compleixen les condicions dels membres
         *  \post el p.i representat el dia definit pels paramètres*/
        Dia(int dia, int mes, int any);

        /** \brief Constructor a partir string
         *  \param[in] s dia a representar
         *  \pre \e s té el format "DD.MM.AA" on D,M,A són digits [0-9]
         *  \post el p.i conté la dia representada per \e s */
        Dia(string s);

        /** \brief Escriure formatejat
         *  \param[in] d el dia a escriure
         *  \param[out] os el flux de sortida on escriure
         *  \pre true
         *  \post s'ha escrit d a os amb el format "DD.MM.AA" */
        static void print(const Dia& d, ostream& os);

        /// Operadors de comparació \{
        friend bool operator<(const Dia& lhs, const Dia& rhs);
        friend bool operator==(const Dia& lhs, const Dia& rhs);
        friend bool operator!=(const Dia& lhs, const Dia& rhs);
        friend bool operator>(const Dia& lhs, const Dia& rhs);
        friend bool operator<=(const Dia& lhs, const Dia& rhs);
        friend bool operator>=(const Dia& lhs, const Dia& rhs);
        /// \}
};
/** Comparació de Dia
 *  '@' representa l'operador : <, >, ==, !=, <=, >=
 *  \brief Indica ordre entre dies (@).
 *  \pre true
 *  \post retorna si (\e lhs @ \e rhs)
 *  \{ */
bool operator<(const Dia& lhs, const Dia& rhs);
bool operator==(const Dia& lhs, const Dia& rhs);
bool operator!=(const Dia& lhs, const Dia& rhs);
bool operator>(const Dia& lhs, const Dia& rhs);
bool operator<=(const Dia& lhs, const Dia& rhs);
bool operator>=(const Dia& lhs, const Dia& rhs);
/// \}

/** \class Hora
  \brief Representa una hora, hora:minut
  */
class Hora {
    private:
        int hora; ///< 0 <= hora <= 23
        int minut; ///< 0 <= minut <= 59

    public:
        Hora() = default;

        /** \brief Construeix hora directament
         *  \pre els paramètres compleixen l'invariant de la classe
         *  \post el p.i conté la hora representada pels paramètres */
        Hora(int hora, int minut);

        /** \brief Construeix Hora a partir d'un string
         *  \param[in] s string que conté un dia  "hora:minut"
         *  \pre \e s té el format HH:MM
         *  \post el p.i conté la hora representada per \e s */
        Hora(string s);

        /** \brief Escriu Hora en un flux de sortida
         *  \param[in] h la hora a escriure
         *  \param[out] os el flux de sortida on escriure
         *  \pre true
         *  \post s'ha escriu dia "HH:MM" a os
         */
        static void print(const Hora& d, ostream& os);

        /// Operadors de comparació \{
        friend bool operator<(const Hora& lhs, const Hora& rhs);
        friend bool operator==(const Hora& lhs, const Hora& rhs);
        friend bool operator!=(const Hora& lhs, const Hora& rhs);
        friend bool operator>(const Hora& lhs, const Hora& rhs);
        friend bool operator<=(const Hora& lhs, const Hora& rhs);
        friend bool operator>=(const Hora& lhs, const Hora& rhs);
        /// \}
};

/** Comparació de Hora 
 *  '@' representa l'operador : <, >, ==, !=, <=, >=
 *  \brief Indica ordre entre hores (@).
 *  \pre true
 *  \post retorna si (\e lhs @ \e rhs)
 *  \{ */
bool operator<(const Hora& lhs, const Hora& rhs);
bool operator==(const Hora& lhs, const Hora& rhs);
bool operator!=(const Hora& lhs, const Hora& rhs);
bool operator>(const Hora& lhs, const Hora& rhs);
bool operator<=(const Hora& lhs, const Hora& rhs);
bool operator>=(const Hora& lhs, const Hora& rhs);
///\}

/** \brief Definició de Data */
typedef pair<Dia, Hora> Data;

/** \brief Operador << de Data
 *  \pre true
 *  \post s'ha escrit Data en format: \%DD.MM.AA HH:MM\% a os */
ostream& operator<<(ostream& os, const Data& d);
#endif
