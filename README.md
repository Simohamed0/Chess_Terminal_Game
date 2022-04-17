#                                                           QADADRI Haytam

# Compilation et Exécution :

### -> Compilez le programme avec la commande "make" et exécuter le programme avec "./bin/echecs"

# Niveau d'éxigence :

### -> Le problème répond à tous les niveaux attendus dans le sujet.

# Contenu du Programme :

### -> Fichier : Piece.cc + Piece.h qui gère le déplacement des pièce. Il contient la classe abstraite Piece.
### -> Fichier : Jeu.cc   + Jeu.h   qui gère le déroulement de la partie.Il contient la classe Jeu.
### -> Fichier : Main-Echecs.cc     qui s'occupe de lancer une partie tout en traitant les entrées.
### -> Les Sous-Classes de Piece:
### &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;{&nbsp;Roi  , &nbsp;&nbsp;Dame ,&nbsp;&nbsp;Cavalier ,&nbsp;&nbsp;Fou ,&nbsp;&nbsp;Tour ,&nbsp;&nbsp;Pion&nbsp;}

# Test Automatique:

### -> J'ai reuissi à passer tous les niveaux de test automatique 4,5 et 6

# Conception du programme et les difficultés rencontrées :

### -> Pour concevoir ce programme, j'ai commencé tout d'abord par créer la classe Pièce et les sous-classes correspondantes. C'était laborieux à faire vu qu'il fallait à chaque fois testé la pièce en question. Cette phase de développement était relativement longue et remplie de problème de compilation.
### -> Après avoir créer cette dernière, j'ai décidé de me pencher sur la classe Echiquier qui était relativement simple à coder vu que vous avez partagé des bouts de code sur le sujet. Cependant, lors de la conception de la classe Jeu je me suis rendu compte que je peux intégrer la classe Echiquier dans la classe Jeu pour optimiser mon programme ainsi au lieu d'avoir 3 classes j'ai fait justement que 2.
### -> Pour cette dernière phase de développement, je me suis intéressé aux fonctionnalités : Prise en passant,Grand-Roque,Petit-Roque,Promotion,Echec,Echec et Mat et Pat. Elles avaient tous leurs part de diffucltée mais celles qui m'ont donné du fil à retordre sont les fonctionnalités : Grand/Petit-Roque,Echec et Mat et Pat.

# Nouvelles Fonctionnalités:

### -> Ajout d'une nouvelle fonctionnalité en ligne maintenant il est possible de jouer aux echecs en ligne.
### -> Ajout d'une interface graphique html.