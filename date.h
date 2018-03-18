/*  AUTEUR(S):
    1) Charles-Olivier Baribeau BARC09039201
    2) Maxime Phaneuf           PHAM22088202
*/

#if !defined(__DATE_H__)
#define __DATE_H__

#include <iostream>

class Date{
  public:
    // Constructeurs
    Date();
    Date(int annee,int mois,int jour);
    // Opérateurs publics pour les comparaisons
    bool operator <(const Date& date) const;
	bool operator >(const Date& date) const;
	bool operator ==(const Date& date) const;
  private:
    int annee;
    int mois;
    int jour;
    // Operateur privés pour le input/output
    friend std::ostream& operator << (std::ostream&, const Date& date);
    friend std::istream& operator >> (std::istream&, Date& date);
};

#endif
