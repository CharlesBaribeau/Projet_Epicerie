/*  INF3105 | Structures de données et algorithmes
 *  UQAM | Département d'informatique | Automne 2016
 *  Pile pour les intérateur d'Arbre AVL pour le Lab6 et TP2
 *  http://ericbeaudry.ca/INF3105/
 */

#if !defined(__PILE__H__)
#define __PILE__H__
#include <cstddef>
template <class T>
class Pile
{
  public:
    // Constructeurs
    Pile();
    Pile(const Pile&);
    // Destructeur
    ~Pile();
    // Fonction publiques
    void empiler(const T&);
    void depiler(T& out);
    T depiler();
    bool vide() const { return sommet==NULL;}
    void vider();
    const Pile<T>&    operator = (const Pile<T>&);

  private:    
    class Cellule
    {
      public:
        Cellule(const T& e, Cellule* c);
        T contenu;
        Cellule* suivante;
    };

    Cellule* sommet;
};

#include "assert.h"
#include "pile.h"

template <class T>
Pile<T>::Pile()
{
    sommet = NULL;
}

template <class T>
Pile<T>::~Pile()
{
    vider();
}

template <class T>
Pile<T>::Pile(const Pile<T>& autre)
{
    sommet = NULL;
    *this = autre;
}


template <class T>
void Pile<T>::vider()
{
    while(!vide())
        depiler();  
}

template <class T>
Pile<T>::Cellule::Cellule(const T& e, Cellule* c)
 : suivante(c)
{
    contenu=e;
}

template <class T>
void Pile<T>::empiler(const T& e)
{
    sommet = new Cellule(e, sommet);
    assert(sommet);
}

template <class T>
T Pile<T>::depiler()
{
    assert(sommet);
    Cellule c(*sommet);
    delete sommet;
    sommet = c.suivante;
    return c.contenu;
}

template <class T>
void Pile<T>::depiler(T& e)
{
    assert(sommet!=NULL);
    e = sommet->contenu;
    Cellule* c = sommet;
    sommet = sommet->suivante;
    delete c;
}


template <class T>
const Pile<T>& Pile<T>::operator = (const Pile<T>& autre)
{
    if(&autre == this) return *this;
 
    Cellule** t=&sommet;
    Cellule* a=autre.sommet;
    while(a){
        if((*t) == NULL)
             *t = new Cellule(a->contenu, NULL);
        else
             (*t)->contenu = a->contenu;
        t = &((*t)->suivante);
        a = a->suivante;
    }
    a = *t;
    *t = NULL;
    while(a!=NULL){
        Cellule* temp = a->suivante;
        delete a;
        a = temp;
    }

    return *this;
}

#endif
