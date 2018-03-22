# Projet d'épicerie
Système de recommandation du plus court trajet pour compléter son épicerie.

* Pour voir l'énoncé du travail et son utilisation:
http://htmlpreview.github.io/?https://github.com/CharlesBaribeau/Projet_Epicerie/blob/master/tp2.html
* Langage utilisé : C++
* Note obtenue : 21/20

## Utilisation
    Une erreur de validation se produit dans vérification des réponses des tests automatiques fournis par
    le professeur. Ainsi, pour tester notre programme, il fallait exécuter ces commandes sur un serveur linux
    à partir du répertoire contenant le Makefile (tp2/) :
    * make tp2
    * ./tests/evaluer.sh
    Le symbole == dans la colonne validation signifie que le résultat est bon.

## Structures de données
    * tableau.h contient une structure de données personnalisée semblable à vector de la std.
    * pile.h contient une structure de données personnalisée semblable à stack de la std.
    * arbreavl.h contient une strcture de données personnalisée semblable à set de la std.
    * arbremap.h contient une structure de données personnalisée semblable à map de la std.
    * date.h contient une structure de données représentant une date.
    * epicerie.h contient une structure de données personnalisée représentant une épicerie.
    * pointst.h contient une structure de données personnalisée représentant la position d'un objet sur la carte.
