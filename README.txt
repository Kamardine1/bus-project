Nom & prénom des étudians : MIRGHANE MOHAMED Kamardine / BECKER Pierre-Antoine

Un petit readme explicatif de notre projet de bus en C.

Tri.c et Tri.h contient notre bibliotheque de tri.

source.c et source.h contiennent les fonctions qui nous on permis de coder le projet.

============================================================================================================================================================================================
Note pour la partie 1 :

Pas de chose importantes à signaler.
============================================================================================================================================================================================



============================================================================================================================================================================================
Note pour la partie 2 :

Pour avoir la fonctionnalité de la partie 2 : il faut appuyer sur la touche 'T' pour declencher la fonctionnalité pour le tri comme demandé. On a choisit la touche T comme "T"ri.
Le tri marche bien , le seul soucis c'est que pour générer aléatoirement les nombres, nous utilisons la bibliotheque <time.h> ce qui fait que les valeurs sont généres en fonction du temps.
Vu que le temps qui sépare la génération est minime, les valeurs ont la meme valeurs ce qui fait que nous voyons pas le tri mais il marche bel et bien.
Il faut suivre les consignes de la console.
ATTENTION : Si vous tapez une autre lettre/chiffre que ceux attendu par la console, cela fera planter le programme.
============================================================================================================================================================================================



============================================================================================================================================================================================Note pour la partie 3 :

Pas de chose importantes à signaler.
============================================================================================================================================================================================



============================================================================================================================================================================================
Note pour la partie 4 :

Pour sauvegarder la position du bus, on a imaginé de mettre les coordonnées de x et y du bus en dernière ligne du fichier, s'il y a plusieurs bus chaque ligne correspondra aux coordonnées de chaque bus. On peut mettre aussi en première ligne de fichier mais il y a plus de choses à gérer.
============================================================================================================================================================================================



============================================================================================================================================================================================
Note pour la partie 5 :

Les fonctions 5.1 et 5.2 marchent niquel, pour voir à quel point elles marchent, decommentez les codes de demonstration (mise en commentaire) dans le main.
Des gros blocs de commentaires sont la pour indiquer de quels fonctionnalités s'agit-il.

Pour la fonctionnalité 5.3 (rendre une ligne circulaire), elle marche mais la bibliotheque de listes doublements chainés la fait planter du fait que lorsque la ligne devient circulaire, elle n'est plus une liste doublement chainée mais une file circulaire, ce qui fait que les fonctions de la bibliotheque de listes doublements chainés font des opérations à l'infini car il n'a plus la condition d'arret (ce qui prouve que la ligne est devenue circulaire).
Il est possible de voir cela dans la console (si vous etes rapide pour visualiser les affichages qui s'affichent à l'infini).
============================================================================================================================================================================================



============================================================================================================================================================================================
Note pour la partie 6 :

Pour que plusieurs bus circulent en même temps. Nous avons fait une boucle pour pouvoir créer des bus avec la fonction "creeBus" qui sont stockés dans un tableau qui s'appelle depot, qui fait reference à un depot de bus.
Chaque bus est accessible avec depot[indice du tableau].
Nous avons choisi que le nombre de bus soit egal au nombre de ligne, mais il est tout à fait possible de les faire changer de ligne. Nous aurions pu faire à ce qu'on lise un entier au début du fichier et qui correspondra au nombre de bus (comme le nombre total de station ou de ligne).
Certains blocs de code sont commentés , il faut les decommenter comme indiquer dans le code pour avoir les fonctionnalités qui gerent parfaitement plusieurs lignes de bus.
ATTENTION : La partie graphique du projet est en chaos car il n'ya qu'un seul sprite pour plusieurs bus, mais l'on peut voir dans la console que tout va bien.
============================================================================================================================================================================================



============================================================================================================================================================================================
Note pour la partie 7 :

Pour qu'une même station appartienne à plusieurs ligne de bus. Il faudrait créer un nouveau tronçon avec la fonction creeTroncon qui relie les lignes de bus entre elles. Il faudra aussi modifier la ligne de bus avec le nouveau tronçon pour que le bus ne fasse pas le même chemin que d'habitude pour qu'il passe par la station appartenant à plusieurs ligne de bus. Il faudra créer une deuxième version du fichier data pour ajouter le nouveau tronçon entre deux stations crée et que l'on voit s'afficher sur l'interface graphique.
============================================================================================================================================================================================