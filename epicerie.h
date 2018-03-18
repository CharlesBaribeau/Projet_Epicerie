/*  AUTEUR(S):
 *  Charles-Olivier Baribeau BARC09039201
 *  Maxime Phaneuf           PHAM22088202
*/
#if !defined(_EPICERIE__H_)
#define _EPICERIE__H_

#include <string>
#include "arbremap.h"
#include "date.h"
#include "pointst.h"
#include "tableau.h"
using namespace std;

class Epicerie{
	friend class Reseau;
    friend class Commande;
	friend class Chemin;
	public:
        // Constructeurs
		Epicerie();
        Epicerie(string, PointST&);

        // Fonctions publiques
        /**
         *  Approvisionne l'épicerie en y insérant un produit.
         *
         *  @param       un string représentant le nom du produit.
         *  @param       une Date représentant la date d'expiration.
         *  @param       un int représentant la quantité.
         *  @return      0
         */
        int approvisionner(string, Date, int);
        /**
         *  Vérifie l'inventaire d'une épicerie pour vérifier si un des produits
         *  est expiré. S'il un des produits est expiré, on l'enlève de l'inventaire. 
         *
         *  @param      une Date représentant l'expiration des produits.
         */ 
		void verifierInventaire(Date);
        /**
         *  Parcours l'inventaire de l'épicerie pour y retirer le produit
         *  commander.
         *  
         *  @param      un string représentant le nom du produit
         *  @param      un int représentant la quantité commander.
         */
		void retirerProduit(string, int);
		string getNom(){ return nom;}
		bool operator==(Epicerie&);
	private :
        string nom;
        PointST emplacement;
		ArbreMap<string, Tableau<Date> > inventaire;
		void ajouterDate(string, Date);
		friend ostream& operator<< (ostream&, Epicerie&);
		friend istream& operator>> (istream&, Epicerie&);
};
class Commande{
  	friend class Reseau;
  	friend class Epicerie;
  	friend class Chemin;
  public:
  	Commande();
    /**
     *  Ajoute un produit dans la commande.
     *
     *  @param      un string représentant le nom du produit.
     *  @param      un int représentant la quantité voulue.
     */
  	void ajouterProduit(string, int);
    /**
     *  Parcours l'épicerie donnée pour y trouver le plus de produits de la 
     *  commande possible.
     *
     *  @param      une Epicerie dans laquelle l'on veut trouver les produits.
     */
	bool comparerProduit(Epicerie&);
    /**
     *  Vérifie si la commande est complète en comparant le nombre de produits
     *  un nombre donné.
     *  
     *  @param      un int représentant le nombre auquel on veut comparer le
     *              nombre de produits.
     */
	bool estComplet(int);
	int nbrProduits;
  private:
	ArbreMap<string, int> produits;
	friend istream& operator>>(istream& is, Commande& c);
	friend ostream& operator<<(ostream& os, Commande& c);
};
class Chemin{
	friend class Commande;
	friend class Reseau;
	friend class Epicerie;
  public:
	Chemin();
    /**
     *  Ajoute une épicerie au chemin parcouru et y ajoute la distance.
     *
     *  @param &    une Epicerie qui sera ajoutée au chemin.
     *  @param      un double représentant la distance entre la position 
     *              acutelle et cette épicerie.
     */    
	void ajouterEpicerie(Epicerie&, double);
    /**
     *  Ajoute une distance au chemin parcouru
     *
     *  @param      un double représentant la distance.
     */
	void ajouterDistance(double);
	ostream& afficherChemin(ostream&);
  private:
	double distance;
	Tableau<string> liste;
	friend ostream& operator<< (ostream&, Chemin&);
};

class Reseau{
	
	friend class Epicerie;
	friend class Commande;
	friend class Chemin;
	
  public :
	// Constructeur
	Reseau();
    // Fonctions publiques
    /**
     *  Insère une épicerie donnée dans l'arbreMap contenant toutes
     *  les épiceries.
     *
     *  @param &    Une référence vers une Epicerie qui sera ajoutée.
     */
	int placer(Epicerie&);
    /**
     *  Change la date courante et lance la fonction permettant de 
     *  supprimer les produits expirés.
     *
     *  @param      La Date qui sera la date actuelle. 
     */
	int changerDate(Date);
    /**
     *  Approvisionne l'épicerie donnée avec le produit donné.
     *
     *  @param      Un string qui représente le nom de l'épicerie.
     *  @param      Un string qui représente le nom du produit.
     *  @param      Une Date qui représente la date d'expiration du produit.
     *  @param      Un int qui représente la quantité de produits qui seront
     *              approvisionnés.
     */
	void approvisionner(string, string, Date, int);
	/**
     *  Vérifie si l'épicerie donnée est déjà existante.
     *
     *  @param      Un string représentant le nom de l'épicerie que l'on
     *              chercher à confirmer sa présence.
     */
    bool estPresente(string);
    /**
     *  Retourne l'épicerie correspondant au nom donné.
     *
     *  @param      Un string représentant le nom de l'épicerie que l'on 
     *              veut retourner.
     */
	Epicerie afficherEpicerie(string);
    /**
     *  Lance la fonction de parcours du réseau. Elle utilise le point
     *  de départ donné ainsi que le nombre d'épiceries maximal que l'on
     *  peut parcourir. Elle utilise aussi la distance maximale que l'on peut 
     *  parcourir et la commande de produits. Par la suite, elle affiche le
     *  chemin parcouru.
     *
     *  @param      PointST de départ.
     *  @param      Un int correspondant au nombre maximal d'épiceries.
     *  @param      Un double correspondant à la distance maximale que l'on
     *              peut parcourir.
     *  @param      Une Commande correspondant aux produits souhaités.
     */
	void evaluer(PointST, int, double, Commande);
	/**
     *  Parcours l'arbre contenant les épiceries et ajoute le nom de l'épicerie
     *  dans le chemin parcouru lorsque le produit commandé s'y trouve. Repète 
     *  le processus jusqu'à ce que tous les chemins possibles soient trouvés.
     *
     *  @param      Le Chemin parcouru jusq'à maintenant.
     *  @param      La Commande de produits.
     *  @param      Un int représentant le nombre d'épiceries parcourues.
     *  @param      Un PointST représentant la dernière localisation.
     *  @param      Un PoinrST représentant le point de départ.
     */
    bool parcourir(Chemin, Commande, int, PointST, PointST);
    /**
     *  Enlève les produits d'une épicerie.
     *
     *  @param      Un string représentant le nom de l'épicerie.
     *  @param      La Commande contenant les produits.
     */
	Commande& ramasser(string, Commande&);
	private :
	ArbreMap<string, Epicerie> epiceries;
	ArbreMap<double, Chemin> chemins;
	Date date;
	int nbMax, distanceMax;	
		
};
#endif
