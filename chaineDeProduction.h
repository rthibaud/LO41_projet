#ifndef _CHAINEDEPRODUCTION_
#define _CHAINEDEPRODUCTION_


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <time.h>

sem_t *panneauTicket;
sem_t *zoneCaissePleine;
sem_t *zoneCaisseVide;
sem_t fin;
pthread_t *tid;
pthread_attr_t *tid_attr;
pthread_mutex_t mutex;
int nbPostes;
int nbPieces;
int nbPiecesProduites;


void traitant(int num);
void accueil();
void* creationThread(void* ID);
void posteDeTravail(int ID,int timeOfProduction);
void premierPoste(int ID,int timeOfProduction);
void dernierPoste(int ID,int timeOfProduction);

#endif

