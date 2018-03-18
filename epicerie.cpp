/**  AUTEUR(S):
 *  Charles-Olivier Baribeau BARC09039201
 *  Maxime Phaneuf           PHAM22088202
 */
#include <iostream>
#include "epicerie.h"
#include <sstream>
#include <math.h>

//Constructeurs
Chemin::Chemin(){
	distance = 0;
}

Reseau::Reseau(){

}

Epicerie::Epicerie(){
    
}

Epicerie::Epicerie(string nom, PointST& emplacement){
   this->nom = nom;
   this->emplacement = emplacement;
}

Commande::Commande(){
	nbrProduits = 0;
}

//Operateurs
std::ostream& operator<< (std::ostream& os, Epicerie& epicerie){
	ArbreMap<string, Tableau<Date> >::Iterateur iterProduit = epicerie.inventaire.debut();
	string produit;
	int quantite;
	for(;iterProduit != epicerie.inventaire.fin(); ++iterProduit){
		produit = iterProduit.cle();
		quantite = epicerie.inventaire[produit].taille();
		if(quantite>0){
			std::ostringstream ss; 
			ss << quantite;
			produit += " " + ss.str() + " ";
			os << produit;
		}
	}
	return os;
}

std::istream& operator>> (std::istream& is, Epicerie& epicerie){
	is >> epicerie.nom; 
	is >> epicerie.emplacement;
	return is;
}



bool Epicerie::operator== (Epicerie& autre){
	return autre.nom == nom;
}

istream& operator>>(istream& is, Commande& c){
    string nomproduit;
	is >> nomproduit;
    while(is && nomproduit!=";"){
	int quantite;
        is >> quantite;
		c.ajouterProduit(nomproduit, quantite);
		is >> nomproduit;
	}

    return is;
}
ostream& operator<<(ostream& os, Commande& c){
	ArbreMap<string, int>::Iterateur iterProduit = c.produits.debut();
	for(;iterProduit!= c.produits.fin();++iterProduit){
		if(iterProduit.valeur() > 0){
			os<< iterProduit.cle()<< " "<<iterProduit.valeur()<< " ";
		}
	}
	os<< " ;";
	return os;
}


std::ostream& operator<< (std::ostream& os, Chemin& chemin){
	return chemin.afficherChemin(os); 
}

std::ostream& Chemin::afficherChemin(std::ostream& os){
	os << round(distance) << "m ";
	for(int k= liste.taille()-1 ;k>=0 ;--k){
		os <<liste[k] <<" ";
	}
	return os;
}

void Epicerie::verifierInventaire(Date date){
	if(!inventaire.vide()){
		ArbreMap<string, Tableau<Date> >::Iterateur iterProduit = inventaire.debut();
		Tableau<Date> listeTmp;
		for(;iterProduit != inventaire.fin();++iterProduit){
			listeTmp = iterProduit.valeur();
			for(int i = 0;i < listeTmp.taille(); ++i){
				if(date > listeTmp[i] || date == listeTmp[i]) iterProduit.valeur().enlever(i); 
			}
		}
	}
}

void Epicerie::retirerProduit(string nom, int quantite){
	Tableau<Date> invTmp = inventaire[nom];
	int i = 0;
	while(i < invTmp.taille() && i < quantite){
		inventaire[nom].enlever(0);
		i++;
	}	
}

int Epicerie::approvisionner(string nom, Date date, int quantite){
	for(int i = 0; i < quantite; ++i) ajouterDate(nom, date);
	return 0;
}

void Epicerie::ajouterDate(string nom, Date date){
	bool inserer = false;
	int i = 0;
	Tableau<Date> tmp = inventaire[nom];
	while(i < tmp.taille() && !inserer){
		inserer = date > tmp[i];
		if(inserer){
			tmp.inserer(date, i);
		}else{
			i++;
		}
	}
	if(!inserer) tmp.ajouter(date);
	inventaire[nom] = tmp;
}

Epicerie Reseau::afficherEpicerie(string nom){
	return epiceries[nom];
}

void Commande::ajouterProduit(string nom, int quantite){

	produits[nom] = quantite;
	nbrProduits = nbrProduits + quantite;

}

bool Commande::comparerProduit(Epicerie& epicerie){
	ArbreMap<string, int>::Iterateur iterInventaire = produits.debut();
	string nomProduit;
	int quantite, taille = 0, i = 0;
	for(;iterInventaire != produits.fin();++iterInventaire){
		nomProduit = iterInventaire.cle();
		quantite = iterInventaire.valeur();
		taille = epicerie.inventaire[nomProduit].taille();
		i = 0;
		while(i < quantite && i < taille){
			nbrProduits--;
			iterInventaire.valeur()--;
			i++;
		}
	}
	return nbrProduits == 0;
}
bool Commande::estComplet(int nbr){
	return nbrProduits == nbr;
}


void Chemin::ajouterEpicerie(Epicerie& epi, double dist){
	liste.ajouter(epi.nom);
	distance = distance + dist;
}
void Chemin::ajouterDistance(double d){
	distance = distance + d;
}

int Reseau::placer(Epicerie& epicerie){
	epiceries[epicerie.nom] = epicerie;
	return 0;
}

int Reseau::changerDate(Date date){
	if(!epiceries.vide()){
		ArbreMap<string, Epicerie>::Iterateur iterEpicerie = epiceries.debut();
		for(;iterEpicerie != epiceries.fin();++iterEpicerie){
			iterEpicerie.valeur().verifierInventaire(date);	
		}
	}
	this->date = date;
	return 0;
}

bool Reseau::estPresente(string nom){
	return epiceries[nom].nom != "";
}

void Reseau::approvisionner(string epicerie, string produit, Date date, int quantite){
	epiceries[epicerie].approvisionner(produit, date, quantite);
}

void Reseau::evaluer(PointST p, int nbMax, double distMax, Commande c){
	ArbreMap<string, Epicerie>::Iterateur iterEpicerie = epiceries.debut();
	bool complet = false;
	int i = 0;
	Chemin chemin;
	this->nbMax = nbMax;
	this->distanceMax = distMax;
	parcourir(chemin, c, i, p, p); 
	if(chemins.vide() && !complet){
		std::cout<< "IMPOSSIBLE ";
	}else{
		Chemin tmp = chemins.debut().valeur(); 
		std::cout <<tmp;	
	}
	chemins.vider();
}

bool Reseau::parcourir(Chemin chemin, Commande c, int i, PointST p, PointST depart){
	bool complet = false;
	int j = i;
	Chemin tmpChemin = chemin;
	Commande c2 = c;
   	PointST tmpP = p;
	ArbreMap<string, Epicerie>::Iterateur iter = epiceries.debut();
	for(;iter != epiceries.fin();++iter){	
		
		if(tmpChemin.liste.chercher(iter.cle()) == -1){
			complet = c2.comparerProduit(iter.valeur());
			tmpChemin.ajouterEpicerie(iter.valeur(), tmpP.distance(iter.valeur().emplacement));
			j++;
		}
		if(complet) {
			tmpChemin.ajouterDistance(iter.valeur().emplacement.distance(depart));	
			chemins[tmpChemin.distance] = tmpChemin;
		}
		if(!complet && iter != epiceries.fin() && j < nbMax && tmpChemin.distance < distanceMax && i !=j) {
			parcourir(tmpChemin, c2, j, iter.valeur().emplacement, depart);	
		}
		j = i;
		tmpChemin = chemin;	
		complet = false;
		c2 = c;
	}
	return c.nbrProduits == 0;
}

Commande& Reseau::ramasser(string nom, Commande& c){
	Epicerie* e = &epiceries[nom];
	string nomProduit;
	int *nbrCommande, nbrInv, nbrRamasse = 0;
	ArbreMap<string, int>::Iterateur iterProduit = c.produits.debut();
	for(;iterProduit != c.produits.fin();++iterProduit){
		nomProduit = iterProduit.cle();
		nbrCommande = &iterProduit.valeur();
		nbrInv = e->inventaire[nomProduit].taille();		
		if(nbrInv > 0 && *nbrCommande > 0){
			if(nbrInv >= *nbrCommande) nbrRamasse = *nbrCommande;
	    	else nbrRamasse = nbrInv;	
			e->retirerProduit(nomProduit, nbrRamasse);
			c.nbrProduits -= nbrRamasse;
			*nbrCommande -= nbrRamasse;
		}
	}
	return c;
}
