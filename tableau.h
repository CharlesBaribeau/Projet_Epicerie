/* UQAM / Département d'informatique
   INF3105 - Structures de données et algorithmes
   Squelette pour classe générique Tableau<T> pour le TP1 et Lab3.

   AUTEUR(S):
    1) Charles-Olivier Baribeau BARC09039201
    2) Maxime Phaneuf           PHAM22088202
*/

#if !defined(_TABLEAU___H_)
#define _TABLEAU___H_

#include <assert.h>
template <class T>
class Tableau{

public:
    // Constructeurs
	Tableau<T>(int capacite_initiale=4);
    Tableau<T>(const Tableau&);
    // Destructeurs
    ~Tableau<T>();
    // Méthodes publiques

    /**
     *  Ajoute un élément à la fin du tableau.
     *
     *  @param element   l'objet (du template T) qui sera ajouté.
     */
    void ajouter(const T& element);
    /**
     *  Vide le tableau.
     */
    void vider();
    /**
     *  Retourne la taille du tableau.
     *
     *  @return          la taille du tableau.
     */
    int taille() const;
    /**
     *  Insère un élément à une position donnée.
     *
     *  @param element  l'objet (du tempplate T) qui sera ajouté.
     *  @param index    un int qui correspond à la position à laquelle l'on
     *                  veut ajouter.
     */
    void inserer(const T& element, int index=0);
    /**
     *  Enlève l'élément situé à la position donnée.
     *
     *  @param index    un int qui correspond à la position à laquelle l'on
     *                  veut enlever.
     */
    void enlever(int index=0);
    /**
     * Retourne la position d'un élément dans le tableau.
     *
     * @param element   l'objet (du template T) duquel on cherche sa position.
     * @return          La position de l'objet s'il est dans le tableau, -1 sinon.
     */
    int chercher(const T& element);
	/**
     * Redimentionne le tableau avec une nouvelle capacité.
     *
     * @param nouvelleCapacite  La nouvelle taille du tableau.
     */
  	void redimentionner(int nouvelleCapacite);
    
    
    // Opérateurs publiques
    const T& operator[] (int index) const;
    T& operator[] (int index);
    bool operator == (const Tableau<T>& autre) const;
    Tableau<T>& operator = (const Tableau<T>& autre);
private:
    T*             elements;
    int            nbElements;
    int            capacite;
};


// ---------- Définitions -------------


template <class T>
Tableau<T>::Tableau(int capacite_)
{
   	nbElements = 0;
	elements = new T[capacite_];
	capacite = capacite_; 
}

template <class T>
Tableau<T>::Tableau(const Tableau<T>& autre)
{
    nbElements = autre.nbElements;
	capacite = autre.capacite;
	elements = new T[capacite];
	for(int i = 0; i < nbElements;i++){
		elements[i] = autre.elements[i];
	}
}

template <class T>
Tableau<T>::~Tableau()
{
    delete[] elements;

}

template <class T>
int Tableau<T>::taille() const
{
    return nbElements;
}

template <class T>
void Tableau<T>::ajouter(const T& item){
		
	if(nbElements == capacite) redimentionner(capacite*2);
	elements[nbElements] = item;
	nbElements++;
}
template <class T>
void Tableau<T>::redimentionner(int nouvelleCapacite){
	capacite = nouvelleCapacite;
	T* temp = new T[capacite];
	for(int i = 0; i < nbElements; i++)	temp[i] = elements[i];
	delete[] elements;
	elements = temp;
}

template <class T>
void Tableau<T>::inserer(const T& element, int index)
{
    if(nbElements == capacite) redimentionner(capacite*2);
	for(int i = nbElements - 1; i >= index; i--) 
			elements[i+1] = elements[i];
	elements[index] = element;
	nbElements++;	

}

template <class T>
void Tableau<T>::enlever(int index)
{
    for(int i = index; i < nbElements; i++)
		if(i + 1 < nbElements) elements[i] = elements[i+1];

	nbElements--; 
}

template <class T>
int Tableau<T>::chercher(const T& element)
{
    for(int i = 0; i < nbElements; i++)
		if(elements[i] == element) return i;
	return -1;
}

template <class T>
void Tableau<T>::vider()
{
    delete[] elements;
   	nbElements = 0;
	elements = new T[4];
	capacite = 4;    
}

template <class T>
const T& Tableau<T>::operator[] (int index) const
{
    assert(index < nbElements);
	return elements[index];
}

template <class T>
T& Tableau<T>::operator[] (int index)
{
    assert(index < nbElements);
	return elements[index];
}

template <class T>
Tableau<T>& Tableau<T>::operator = (const Tableau<T>& autre)
{
    if(this == &autre) return *this;
	
	nbElements = autre.nbElements;
	if(capacite < autre.nbElements || autre.nbElements * 2 < capacite){
		capacite = autre.capacite;
		elements = new T[capacite];
	}
	for(int i = 0; i < nbElements; i++)	elements[i] = autre.elements[i];
	return *this;
}

template <class T>
bool Tableau<T>::operator == (const Tableau<T>& autre) const
{
    if(this == &autre) return true;
	if(nbElements != autre.nbElements) return false;
	for(int i = 0; i < nbElements; i++)
		if(!(elements[i] == autre.elements[i])) return false;
    return true;
}

#endif //define _TABLEAU___H_
