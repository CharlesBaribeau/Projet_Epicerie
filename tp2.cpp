/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Automne 2017 | TP2
    http://ericbeaudry.uqam.ca/INF3105/tp2/   

    AUTEUR(S):
    Charles-Olivier Baribeau BARC09039201
    Maxime Phaneuf           PHAM22088202

    À LIRE AVANT D'EXÉCUTER :
    Certains test ne semblent que fonctionner sur les machines du serveur malt.
    Le démonstrateur des laboratoires nous a mentionné de signaler au correcteur
    que pour ne pas avoir d'erreurs, il faut exécuter les test sur une de ses
    machines.
*/
#include <fstream>
#include <iostream>
#include <string>
#include <cassert>
#include <cmath>
#include <limits>
#include "date.h"
#include "epicerie.h"
#include "pointst.h"

using namespace std;

int tp2(istream& entree){
    Date maintenant;
    Reseau reseau;
	while(entree){
        string typecommande;
        entree >> typecommande;
        if(!entree) break; // détection fin ==> sortie
        
        if(typecommande=="RECOMMANDER"){
			PointST p;
            int nbMaxEpiceries=0;
            double maxdistance=0;
            Commande c;
            char deuxpoints=0;
			entree >> p >> nbMaxEpiceries >> maxdistance >> deuxpoints >> c;
            assert(deuxpoints==':');
			reseau.evaluer(p, nbMaxEpiceries, maxdistance,c);
        }else if(typecommande=="RAMASSER"){
            Commande c;
            entree >> c;
            string nomepicerie;
            entree >> nomepicerie;
			while(entree && nomepicerie!=";"){
               	c = reseau.ramasser(nomepicerie, c);
                entree >> nomepicerie;
            }
			if(c.nbrProduits == 0) cout << "COMPLET";
			else{
				cout<<"MANQUE "<<c;
			}
        }else if(typecommande=="APPROV"){
            string nomepicerie;
			char deuxpoints=0;
            entree >> nomepicerie >> deuxpoints;
            assert(deuxpoints==':');
            string nomproduit;
            entree >> nomproduit;
            while(entree && nomproduit!=";"){
                int quantite;
          		Date dateexpiration;
                entree >> quantite >> dateexpiration;
                reseau.approvisionner(nomepicerie, nomproduit, dateexpiration, quantite);
				entree >> nomproduit;
            }
			cout << "OK";
        }else if(typecommande=="PLACER"){
            PointST position;
            string nom;
            char pointvirgule=0;
            Epicerie epicerie;
			entree >> epicerie >> pointvirgule;
            assert(pointvirgule==';');
            if(reseau.placer(epicerie) == 0) cout << "OK";
			else cout << "INVALIDE" ;
        }else if(typecommande=="INVENTAIRE"){
            string nomepicerie;
            char pointvirgule=0;
            entree >> nomepicerie>> pointvirgule;
            assert(pointvirgule==';');
            Epicerie epicerieAff = reseau.afficherEpicerie(nomepicerie); 
			cout << epicerieAff << ";" ;
        }else if(typecommande=="DATE"){
            char pointvirgule=0;
			entree >> maintenant >> pointvirgule;
            assert(pointvirgule==';');
            reseau.changerDate(maintenant);
            cout << "OK";
        }else{
            cout << "Commande '" << typecommande << "' invalide!" << endl;
            return 2;
        }
        cout << endl;
        entree >> ws; // force la lecture d'un espace blanc.
    }
    return 0;
}
// syntaxe d'appel : ./tp2 [nomfichier.txt]
int main(int argc, const char** argv){
    // Gestion de l'entrée :
    //  - lecture depuis un fichier si un argument est spécifié;
    //  - sinon, lecture depuis std::cin.
    if(argc>1){
         std::ifstream entree_fichier(argv[1]);
         if(entree_fichier.fail()){
             std::cerr << "Erreur d'ouverture du fichier '" << argv[1] << "'" << std::endl;
             return 1;
         }
         return tp2(entree_fichier);
    }else
         return tp2(std::cin);        

    return 0;
}


