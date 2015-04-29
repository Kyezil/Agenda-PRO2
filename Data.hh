/** \file Data.hh
    \brief Especificació de la classe Data
*/

#ifndef _DATA_HH_
#define _DATA_HH_

/** \class Data
    \brief Representa una data amb els atributs any, mes, dia, hora i minut
*/
class Data
{
protected:
  
  unsigned int any;   /// \invariant \f$ any \le 99 \f$
  unsigned int mes;   /// \invariant \f$ 1 \le mes \le 12 \f$
  unsigned int dia;   /// \invariant \f$ 1 \le dia \le 31 \f$
  unsigned int hora;  /// \invariant \f$ hora < 24 \f$
  unsigned int minut; /// \invariant \f$ minut < 60 \f$
  
public:
  
  //Constructores
  
  /** \brief Creadora per defecte.
      \pre Cert
      \post El resultat és una data per defecte.
   */
  Data();
  
  /** \brief Creadora amb valors inicials.
      \pre \f$ \textit{any} \le 99, 1 \le \textit{mes} \le 12, 
      1 \le \textit{dia} \le 31, \textit{hora} < 24,
      \textit{minut} < 60 \f$
      \post El p.i. representa la data dels paràmetres.
   */
  Data(int any, int mes, int dia, int hora, int minut);  
  
  // Consultores
  
  /** \brief Indica ordre entre dates (<).
      \pre Cert
      \post El resultat indica si la primera data és anterior a la segona.
   */
  bool operator< (Data &a, Data &b);
};

#endif
