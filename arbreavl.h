/* UQAM / Département d'informatique
   INF3105 - Structures de données et algorithmes
   Squelette pour classe générique ArbreAVL<T> fourni par le département.
   
   Complétion du code par les étudiants
   AUTEUR(S):
    1) Charles-Olivier Baribeau BARC09039201
    2) Maxime Phaneuf           PHAM22088202
*/

#if !defined(_ARBREAVL___H_)
#define _ARBREAVL___H_
#include <cassert>
#include "pile.h"
#include <algorithm>

template <class T>
class ArbreAVL {
	friend class Noeud;
   public:
    // Constructeurs
    ArbreAVL();
    ArbreAVL(const ArbreAVL&);
    // Destructeurs
    ~ArbreAVL();
    // Méthodes publiques
 
    /**
     *  Insère un élément dans l'arbre AVL.
     *
     *  @param       L'objet du template T qui sera ajouté.
     */
    void inserer(const T&);
    /**
     *  Parcours l'arbre et retourne true si l'élément est présent.
     *
     *  @param       L'objet du template T que l'on cherche.
     *  @return      true si l'objet est présent, false sinon.
     */
    bool contient(const T&) const;
    /**
     *  Vérifie si l'arbre est vide.
     *
     *  @return      true si l'arbre est vide, false sinon.
     */
    bool vide() const;
    /**
     *  Parcours l'arbre récursivement pour supprimer chacun des noeuds.
     */
    void vider();
    /**
     *  Enlève un élément de l'arbre.
     *
     *  @param      L'objet du template T que l'on chercher à enlever.
     */
    void enlever(const T&); 
    /**
     *  Retourne la hauteur de l'arbre.
     *
     *  @return     Un int qui représente la hauteur de l'arbre.
     */
    int  hauteur() const;
    
    // Déclaration de la class Iterateur et de ses fonctions.
    class Iterateur;
    /**
     *  Retourne un Iterateur pointant vers le premier élément de l'arbre.
     *
     *  @return     L'objet Iterateur pointant vers le plus petit élément.
     */
    Iterateur debut() const;
    /**
     *  Retourne un Iterateur pointant vers le dernier élément de l'arbre.
     *
     *  @return     L'objet Iterateur pointant vers le plus grand élément.
     */
    Iterateur fin() const;
    /**
     *  Retourne un Iterateur pointant vers un élément donné.
     *
     *  @param      L'objet du template T que l'on cherche.
     *  @return     L'objet Iterateur pointant vers l'objet du template T
     *              que l'on chercait
     */
    Iterateur rechercher(const T&) const;
    /**
     *  Retourne l'élément suivant lorsque l'élément recherché n'est pas trouvé dans l'arbre.
     *
     *  @param      L'objet du template T que  l'on cherche.
     *  @return     L'objet Iterateur pointant sur l'élément ou sur le suivant.
     */
    Iterateur rechercherEgalOuSuivant(const T&) const;
    /**
     *  Retourne l'élément précédant lorsque l'élément recherché n'est pas trouvé dans l'arbre.
     *
     *  @param      L'objet du template T que l'on cherche.
     *  @return     L'objet Iterateur pointant sur l'élément ou sur le précédant.      
     */
    Iterateur rechercherEgalOuPrecedent(const T&) const;
    // Accès aux éléments de l'arbre via un intérateur.
    const T& operator[](const Iterateur&) const;
    T& operator[](const Iterateur&);
    // Copie d'un arbre AVL.
    ArbreAVL& operator = (const ArbreAVL&);

  private:
    class Noeud{
		friend class ArbreAVL;
		friend class Iterateur;
		Noeud(const T&);
        Noeud *gauche;
        Noeud *droite;
        int equilibre;
        T contenu;
    };
    Noeud* racine;

    // Fonctions internes.
    
    /**
     *  Retourne la hauteur d'un noeud.
     *
     *  @param *n      Pointeur vers l'objet Noeud duquel l'on veut la hauteur.
     *  @return        Un int correspondant à la hauteur du noeud.
     */
    int hauteur(Noeud *n) const;
    /**
     *  Insère un élément dans un noeud. Si le noeud est vide, on retourne un 
     *  nouveau noeud avec l'élément à l'intérieur.
     *
     *  @param *&      Noeud dans lequel on veut insérer l'élément.
     *  @param &       Élément du template T que l'on veut insérer.
     *  return         true si l'élément à été inséré, false sino.
     */
    bool inserer(Noeud*&, const T&);
    /**
     *  Rééquilibre l'arbre en faisant une rotation gauche/droite.
     *
     *  @param  *&     Noeud sur lequel on veut faire la rotation.
     */
    void rotationGaucheDroite(Noeud*&);
    /**
     *  Rééquilibre l'arbre en faisant une rotation droite/gauche.
     *
     *  @param *&      Noeud sur lequel on veut faire la rotation.
     */
    void rotationDroiteGauche(Noeud*&);
    /**
     *  Parcours l'arbre et supprime tous les noeuds.
     *
     *  @param *&      Noeud que l'on veut vider.
     */
    void vider(Noeud*&);
    /**
     *  Parcours le Noeud et vérifie si l'élément donné est présent.
     *
     *  @param *n       Pointeur vers le Noeud que l'on parcours.
     *  @param &        L'objet du template T que l'on veut trouver.
     */
    bool contient(Noeud *n, const T&) const;
    /**
     *  Copie un noeud dans un autre.
     *
     *  @param *        Pointeur vers un Noeud duquel on veut copier.
     *  @param *&       Noeud dans lequel on veut copié.
     */
    void copier(const Noeud*, Noeud*&) const;
    /**
     *  Retourne le plus grand élément d'un noeud.
     *
     *  @param *        Pointeur vers le Noeud duquel on veut trouvé le plus
     *                  grand élément.
     *  @return         un objet du template T correspondant au plus grand
     *                  élément du noeud donné.
     */
    const T& max(Noeud*) const;
    /**
     *  Enlève un élément d'un noeud.
     *
     *  @param *&n      Noeud duquel on veut enlever l'élément.
     *  @param &e       L'objet du template T que l'on veut enlever.
     *  @return         true si l'objet a été enlevé, false sinon.
     */
    bool enlever(Noeud*& n, const T& e);

  public:
    class Iterateur{
      friend class Noeud;
	  public:
        // Constructeurs
        Iterateur(const ArbreAVL& a);
        Iterateur(const Iterateur& a);
        Iterateur(const ArbreAVL& a, Noeud* c);
        // Op/rateurs
        operator bool() const;
        bool operator!() const;
        bool operator==(const Iterateur&) const;
        bool operator!=(const Iterateur&) const;
        const T& operator*() const;
        Iterateur& operator++();
        Iterateur operator++(int);
        Iterateur& operator = (const Iterateur&);
      private:
        const ArbreAVL& arbre_associe;
        Noeud* courant;
        Pile<Noeud*> chemin;
        
      friend class ArbreAVL;
    };
};


//-----------------------------------------------------------------------------

template <class T>
ArbreAVL<T>::Noeud::Noeud(const T& c):
gauche(NULL), droite(NULL), equilibre(0), contenu(c)
{
}

template <class T>
ArbreAVL<T>::ArbreAVL() : racine(NULL)
{
}

template <class T>
ArbreAVL<T>::ArbreAVL(const ArbreAVL<T>& autre) : racine(NULL)
{
    copier(autre.racine, racine);
}

template <class T>
ArbreAVL<T>::~ArbreAVL()
{
    vider();
}

template <class T>
bool ArbreAVL<T>::contient(const T& element) const
{
    return contient(racine,element);
}

template <class T>
bool ArbreAVL<T>::contient(Noeud *n, const T& element) const
{
   if(n == NULL) return false;
   else if (element < n->contenu) return contient(n->gauche,element);
   else if (element > n->contenu) return contient(n->droite,element);
   return true; 
}

template <class T>
void ArbreAVL<T>::inserer(const T& element)
{
    inserer(racine, element);
}

template <class T>
bool ArbreAVL<T>::inserer(Noeud*& noeud, const T& element)
{
    if(noeud==NULL)
    {
        noeud = new Noeud(element);
        return true;
    }
    if(element < noeud->contenu){
        if(inserer(noeud->gauche, element))
        {
            noeud->equilibre++;
            if(noeud->equilibre == 0) return false;
            if(noeud->equilibre == 1) return true;
            assert(noeud->equilibre==2);
            if(noeud->gauche->equilibre == -1)
            {
                rotationDroiteGauche(noeud->gauche);
            }
            rotationGaucheDroite(noeud);
            
        }
        return false;
    }
    else if(noeud->contenu < element){
        if(inserer(noeud->droite, element))
        {
            noeud->equilibre--;
            if(noeud->equilibre == 0) return false;
            if(noeud->equilibre == -1) return true;
            assert(noeud->equilibre == -2);
            if(noeud->droite->equilibre == 1)    
            {
                rotationGaucheDroite(noeud->droite);
            }
            rotationDroiteGauche(noeud);
            
        }
        return false;
    }

    // element == noeud->contenu
    noeud->contenu = element;  // Mise à jour
    return false;
}

template <class T>
void ArbreAVL<T>::rotationGaucheDroite(Noeud*& racinesousarbre)
{
    Noeud *temp = racinesousarbre->gauche;
    int  ea = temp->equilibre;
    int  eb = racinesousarbre->equilibre;
    int  neb = -(ea>0 ? ea : 0) - 1 + eb;
    int  nea = ea + (neb < 0 ? neb : 0) - 1;

    temp->equilibre = nea;
    racinesousarbre->equilibre = neb;
    racinesousarbre->gauche = temp->droite;
    temp->droite = racinesousarbre;
    racinesousarbre = temp;
}

template <class T>
void ArbreAVL<T>::rotationDroiteGauche(Noeud*& racinesousarbre)
{
    Noeud *temp = racinesousarbre->droite;
    int ea = temp->equilibre;
    int eb = racinesousarbre->equilibre;
    int neb= -(ea<0 ? ea : 0) +1 +eb;
    int nea= ea + (neb>0 ? neb : 0) +1 ;

    temp->equilibre = nea;
    racinesousarbre->equilibre = neb;
    racinesousarbre->droite = temp->gauche;
    temp->gauche = racinesousarbre;
    racinesousarbre = temp;    
}

template <class T>
bool ArbreAVL<T>::vide() const
{
    return racine == NULL;
}

template <class T>
void ArbreAVL<T>::vider(){
  vider(racine);
  racine = NULL;
}

template <class T>
void ArbreAVL<T>::vider(Noeud*& noeud)
{
    if(noeud != NULL)
    {
        vider(noeud->gauche);
        vider(noeud->droite);
        delete noeud;
    }
}

template <class T>
void ArbreAVL<T>::copier(const Noeud* source, Noeud*& noeud) const
{
    if (source != NULL)
    {
        noeud = new Noeud(source->contenu);
        copier(source->gauche, noeud->gauche);
        copier(source->droite, noeud->droite);
    }
}

template <class T>
int  ArbreAVL<T>::hauteur() const{
    
    return hauteur(racine);
}

template <class T>
int ArbreAVL<T>::hauteur(Noeud *n) const
{
    if (n == NULL )
    {
        return 0;
    }
    return std::max(hauteur(n->gauche),hauteur(n->droite)) + 1;
}

template <class T>
const T& ArbreAVL<T>::max(Noeud* n) const
{
   while (n->droite != NULL)
   {
        n = n->droite;
   }
   return n->contenu;
}

template <class T>
void ArbreAVL<T>::enlever(const T& element)
{
    enlever(racine, element);
}

template <class T>
bool ArbreAVL<T>::enlever( Noeud*& noeud, const T& element)
{
    if(element < noeud->contenu)
    {
        bool retour = false;
        if(enlever(noeud->gauche, element))
        {
            noeud->equilibre -= 1;
            if(noeud->equilibre == 0) return true;
            if(noeud->equilibre == 1) return false;
            retour = noeud->droite->equilibre != 0;
            if(noeud->droite->equilibre == 1)
            {
                rotationGaucheDroite(noeud->droite);
            }
            rotationDroiteGauche(noeud);     
        }
        return retour;
    }
    else if(element > noeud->contenu)
    {
        bool retour = false;
        if(enlever(noeud->droite, element))
        {
            noeud->equilibre += 1;
            if(noeud->equilibre == 0) return true;
            if(noeud->equilibre == -1) return false;
            retour = noeud->gauche->equilibre != 0;
            if(noeud->gauche->equilibre == -1)
            {
                rotationDroiteGauche(noeud->gauche);
            }
            rotationGaucheDroite(noeud);    
        }
        return retour;
    }
    Noeud *temp = noeud;
    if (noeud->gauche==NULL)
    {
        noeud = noeud->droite;
        delete temp;
        return true;
     }
    if (noeud->droite==NULL)
    {
        noeud = noeud->gauche;
        delete temp;
        return true;
    }
    noeud->contenu = max(noeud->gauche);
    noeud = temp;
    return enlever(noeud->gauche, noeud->contenu);
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::debut() const
{
    Iterateur it(*this);
    it.courant = racine;
    if (it.courant->gauche != NULL)
    {
        while(it.courant->gauche != NULL)
            {
                it.chemin.empiler(it.courant);
                it.courant = it.courant->gauche;
            }
    }
    return it;
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::fin() const
{
    return Iterateur(*this);
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercher(const T& e) const
{
    Iterateur it(*this);
    Noeud *noeud = racine;
    while (noeud)
    {
        if (noeud->contenu > e)
        {
            it.chemin.empiler(noeud);
            noeud = noeud->gauche;
        }
        else if (noeud->contenu < e)
        {
            noeud = noeud->droite;
        } else 
        {
            it.courant = noeud;
            return it;
        }
    }
    it.chemin.vider();
    return it;
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercherEgalOuSuivant(const T& e) const
{
    Iterateur it(*this);
    Noeud *noeud = racine;
    while (noeud)
    {
        if (noeud->contenu > e)
        {
            it.chemin.empiler(noeud);
            noeud = noeud->gauche;
        }
        else if (noeud->contenu < e)
        {
            noeud = noeud->droite;
        } else 
        {
            it.courant = noeud;
            return it;
        }
    }
    if (!it.chemin.vide())
    {
        it.courant = it.chemin.depiler();
        while (it && e >= it.courant->contenu)
        {
            it++;
        }
    }
    return it;
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercherEgalOuPrecedent(const T& e) const
{
    Noeud *fin = NULL;
    Noeud *noeud = racine;
    while (noeud)
    {
        if (noeud->contenu > e)
        {
            noeud = noeud->gauche;
        }
        else if (noeud->contenu < e)
        {
            fin = noeud;
            noeud = noeud->droite;
        } else 
        {
            return rechercher(e);
        }
    }
    if (fin != NULL)
    {
        return rechercher(fin->contenu);
    }

    return Iterateur(*this);
}

template <class T>
const T& ArbreAVL<T>::operator[](const Iterateur& iterateur) const
{
    assert(&iterateur.arbre_associe == this);
    assert(iterateur.courant);
    return iterateur.courant->contenu;
}

template <class T>
T& ArbreAVL<T>::operator[](const Iterateur& iterateur)
{
    assert(&iterateur.arbre_associe == this);
    assert(iterateur.courant);
    return iterateur.courant->contenu;
}

template <class T>
ArbreAVL<T>& ArbreAVL<T>::operator=(const ArbreAVL& autre) {
    if(this==&autre) return *this;
    vider();
    copier(autre.racine, racine);
    return *this;
}

//-----------------------
template <class T>
ArbreAVL<T>::Iterateur::Iterateur(const ArbreAVL& a)
 : arbre_associe(a), courant(NULL)
{
}

template <class T>
ArbreAVL<T>::Iterateur::Iterateur(const ArbreAVL<T>::Iterateur& a)
: arbre_associe(a.arbre_associe)
{
    courant = a.courant;
    chemin = a.chemin;
}

// Pré-incrément
template <class T>
typename ArbreAVL<T>::Iterateur& ArbreAVL<T>::Iterateur::operator++()
{
    if(courant)
    {
        Noeud *temp = courant->droite;
        while(temp != NULL)
        {
            chemin.empiler(temp);
            temp = temp->gauche;
        }
        if(!chemin.vide())
        {
            courant = chemin.depiler();
        } 
        else
        {
            courant = NULL;
        }
    }
    return *this;
}

// Post-incrément
template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::Iterateur::operator++(int)
{
    Iterateur copie(*this);
    operator++();
    return copie;
}

template <class T>
ArbreAVL<T>::Iterateur::operator bool() const
{
    return courant!=NULL;
}

template <class T>
bool ArbreAVL<T>::Iterateur::operator!() const{
    return courant==NULL;
}

template <class T>
bool ArbreAVL<T>::Iterateur::operator==(const Iterateur& o) const{
    assert(&arbre_associe==&o.arbre_associe);
    return courant==o.courant;
}

template <class T>
bool ArbreAVL<T>::Iterateur::operator!=(const Iterateur& o) const{
    assert(&arbre_associe==&o.arbre_associe);
    return courant!=o.courant;
}

template <class T>
const T& ArbreAVL<T>::Iterateur::operator *() const
{
    assert(courant!=NULL);
    return courant->contenu;
}

template <class T>
typename ArbreAVL<T>::Iterateur& ArbreAVL<T>::Iterateur::operator = (const Iterateur& autre){
    assert(&arbre_associe==&autre.arbre_associe);
    courant = autre.courant;
    chemin = autre.chemin;
    return *this;
}

#endif
