LO41_projet
===========

projet de LO41 Automne 2014

Mes idees

-On peut faire que chaque thread c'est la demande d'une voiture, donc definir un nombre maximum de demande
 qui peuvent etre faites

-Les caisses vides et pleines sont des semaphores, a chaque fois decrementé ou incrementé (donc y en a nbPostes=4)

-toute la parte de liberation de memoire, la mettre dans une fonction qui est evoquée soit à la fin du main, 
soit dans un sigaction pour changer le fonctionnement de ctrl+C

-j'ai pas du tout mis les mutex encore, car comme j ai fait les threads se creent et finissent en sequence (à changer 
parce que comme c est fait la il y a un thread pour chaque poste, et en effet ca sert a rien, je crois)

-pour les tickets je crois il faut faire une struct, j'ai pas encore pensé à ça

j'avais changé beaucoup des choses donc j ai chargé tout avec "_new" à la fin. Il faut les renommer pourque le makefile
puisse marcher. Je suis sur 32 bit, donc si t as de problemes de compilation, essaye d'effaser les files .o et recompiler!
Le poste qui fournit la voiture est le 4ieme, comme c est ecrit dans le sujet

Chiara

6/01/15

-j'ai ajouté le sighandler pour liberer la memoire
-j'ai mis l initialisation des semaphores pas dans la boucle pour voire si ça marche en donnant des valeurs differents
pour chaque poste
-j'ai mis deux caisses pour chaque poste (1 pleine et une vide, ou 2 vides etc..)

Chiara :)

7/01/14

-j'ai fait les threads en modalité detached et ca marche bien (a ce qu il parait)! après je crois 
il y avait un soucis avec l initialisation du semaphores des ticket, j'ai changé et ça marche 
un peu mieux....au moins pas d erreur de segmentation!
j'ai ajouté un semaphore qui dit quand le produit est fini, comme ça il a quelque chose à 
attendre avant de sortir du programme, mais il y a encore quelque probleme parce que 
il fait pas bien ce qu il doit faire! essaie à le lancer et regarde ce qu il fait

bonne nuit! 
chiara
