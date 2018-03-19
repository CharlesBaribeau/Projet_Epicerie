# Projet d'épicerie
Système de recommandation du plus court trajet pour compléter son épicerie.

* Pour voir l'énoncé du travail et son utilisation:
http://htmlpreview.github.io/?https://github.com/CharlesBaribeau/Projet_Epicerie/blob/master/tp2.html

## Utilisation
    Une erreur de validation se produit dans vérification des réponses des tests automatiques fournis par
    le professeur. Ainsi, pour tester notre programme, il fallait exécuter ces commandes sur un serveur linux
    à partir du répertoire contenant le Makefile (tp2/) :
    * make tp2
    * ./tests/evaluer.sh
    Le symbole _==_ dans la colonne validation signifie que le résultat est bon.

## Structures de données
    * _tableau.h_ contient une structure de données personnalisée semblable à _vector_ de la std.
    * _pile.h_ contient une structure de données personnalisée semblable à _stack_ de la std.
    * _arbreavl.h_ contient une strcture de données personnalisée semblable à _set_ de la std.
    * _arbremap.h_ contient une structure de données personnalisée semblable à _map_ de la std.
    * _date.h_ contient une structure de données représentant une date.
    * _epicerie.h_ contient une structure de données personnalisée représentant une épicerie.
    * _pointst.h_ contient une structure de données personnalisée représentant la position d'un objet sur la carte.
