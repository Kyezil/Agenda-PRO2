/** \file Data.hh
    \brief Especificació de Data
*/
#ifndef _DATA_HH_
#define _DATA_HH_
/** \struct Data
    \brief Representa una data dia:mes:any hora:minut
*/
struct Data {
    unsigned int any;   /// \invariant \f$ \textbf{any} \le 99 \f$
    unsigned int mes;   /// \invariant \f$ 1 \le \textbf{mes} \le 12 \f$
    unsigned int dia;   /// \invariant \f$ 1 \le \textbf{dia} \le 31 \f$
    unsigned int hora;  /// \invariant \f$ \textbf{hora} < 24 \f$
    unsigned int minut; /// \invariant \f$ \textbf{minut} < 60 \f$
    
    /** \brief Indica ordre entre dates (<).
     *  \param[in] d rhs data
     *  \return (p.i < b)
     *  \pre true
     *  \post retorna cert i el p.i és anterior a \e d
   */
   bool operator<(const Data &d) const;
};
#endif
