Tournoi4 : Logiciel d'organisation de tournoi de tennis de table loisir.

Le principe est un tournoi où à chaque tour les tables de 4 joueurs sont définies.
Ensuite 3 matchs en double sur chaque table sont effectués correspondant à toutes les combinaisons d'équipes possibles. Chaque joueur a un point par match gagné.

Installation
Sur un PC Windows on peut installer Cygwin.

On installe d'abord tout les packages par défaut.
Ensuite on installe les packages commencant par gcc et le package git en prenant la version la plus récente.

A partir d'une fenêtre cygwin pour récupérer les sources faire la commande :

git clone https://github.com/yvesmocq/Tournoi4.git

ensuite pour compiler il faut aller dans le repertoire source :

cd Tournoi4/src

On compile :

gcc *.cpp -o Tournoi4.exe

L'executable est le fichier Tournoi4.exe

Le mieux est de travailler dans un répertoire vierge :

cd ../..

mkdir tournoi

cd tournoi

cp ../Tournoi4/src/Tournoi4.exe .

Maintenant vous pouvez lancer le fichier Tournoi4 :

./Tournoi4

Toutes les données sont dans le fichier svt4.dt4, avant et après chaque tirage une sauvegarde est faite.
ce qui peut permettre de revenir en arrière.
A tout moment si on quitte le programme, quand on le relance on repart du même état.
Si on veut repartir à zéro il faut effacer ou renommer le fichier svt4.dt4.

Pour saisir les résultats il faut d'abord savoir qu'il y a deux possibilités soit un joueur gagne tout ses matchs soit un joueur perd tous ses matchs.
On saisie donc une lettre correspondant au joueur puis 3 ou 0.

Si le nombre de joueurs présents n'est pas divisible par 4, on a des joueurs qui ne font pas de match pour un tour.
On saisie à la main le nombre de points qu'on leur attibue, leur donner 2 points semble une bonne valeur pour compenser le fait de ne pas avoir jouer.
Mais c'est l'organisateur qui choisi.




