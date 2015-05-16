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
        Dia() = default;

        /** \brief Construeix Dia directament
         *  \pre els paramètres compleixen l'invariant de la classe
         *  \post el p.i conté la dia representada pels paramètres */
        Dia(int dia, int mes, int any);
        
        /** \brief Construeix Dia a partir d'un string
         *  \param[in] s string que conté un dia  "dia.mes.any"
         *  \pre \e s té el format DD.MM.AA
         *  \post el p.i conté la dia representada per \e s */
        Dia(string s);

        /** \brief Indica ordre entre dies (<).
         *  \param[in] d rhs dia
         *  \return (p.i < d)
         *  \pre true
         *  \post retorna cert i el p.i és anterior a \e d  */
        bool operator<(const Dia &d) const;

        /** \brief Escriu Dia en un flux de sortida
         *  \param[in] d el dia a escriure
         *  \param[out] os el flux de sortida on escriure
         *  \pre true
         *  \post s'ha escriu dia "DD.MM.AA" a os
         */
        static void print(const Dia& d, ostream& os);
};

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

        /** \brief Indica ordre entre hores (<).
         *  \param[in] h rhs hora
         *  \return (p.i < h)
         *  \pre true
         *  \post retorna cert i el p.i és anterior a \e h */
        bool operator<(const Hora &h) const;

        /** \brief Escriu Hora en un flux de sortida
         *  \param[in] h la hora a escriure
         *  \param[out] os el flux de sortida on escriure
         *  \pre true
         *  \post s'ha escriu dia "HH:MM" a os
         */
        static void print(const Hora& d, ostream& os);
};

typedef pair<Dia, Hora> Data;
ostream& operator<<(ostream& os, const Data& d);
#endif
