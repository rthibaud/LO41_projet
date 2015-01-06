#ifndef _CHAINEDEPRODUCTION_
#define _CHAINEDEPRODUCTION_


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>

sem_t *panneauTicket;
sem_t *zoneCaissePleine;
sem_t *zoneCaisseVide;
pthread_t *tid;
pthread_mutex_t mutex;
int nbPostes;
int nbPieces;
int nbPiecesProduites;


void traitant(int num);
void accueil();
void* creationThread(void* ID);
void posteDeTravail(int ID);
void premierPoste(int ID);
void dernierPoste(int ID);

#endif

