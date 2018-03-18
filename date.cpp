/*  AUTEUR(S):
    1) Charles-Olivier Baribeau BARC09039201
    2) Maxime Phaneuf           PHAM22088202
*/

#include "date.h"
#include <cstdio>
#include <iomanip>
#include <assert.h>

Date::Date(){

}

Date::Date(int annee, int mois, int jour){
    this->annee = annee;
    this->mois = mois;
    this->jour = jour;
}

bool Date::operator <(const Date& d) const{
    if (this->annee == d.annee){
        if (this->mois == d.mois){
            return this->jour < d.jour;
        }
        return this->mois < d.mois;
    }
    return this->annee < d.annee;

}

bool Date::operator >(const Date& d) const{
	if (this->annee == d.annee){
		if (this->mois == d.mois){
			return this->jour > d.jour;
		}
		return this->mois > d.mois;
	}
	return this->annee > d.annee;
}

bool Date::operator ==(const Date& d) const{
	return annee == d.annee && mois == d.mois && jour == d.jour;
}


std::ostream& operator << (std::ostream& os, const Date& d){
    int a=d.annee, m=d.mois, j=d.jour;
    char chaine[40];
    sprintf(chaine, "%04d-%02d-%02d", a, m, j);
    os << chaine;
    return os;
}

std::istream& operator >> (std::istream& is, Date& d){
    int a=0, m=0, j=0;
    char t1=0,t2=0;
    is >> a >> t1 >> m >> t2 >> j;
    assert(t1=='-');
    assert(t2=='-');
    d.annee = a;
    d.mois = m;
    d.jour = j;    
    return is;
}

