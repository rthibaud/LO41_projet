#ifndef _CHAINEDEPRODUCTION_
#define _CHAINEDEPRODUCTION_


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>

#define nbPostes 4

//int nbPostes;
int nbPieces;
int val;

sem_t *panneauTicket;
sem_t *zoneCaissePleine;
sem_t *zoneCaisseVide;
pthread_t *tid;
pthread_mutex_t mutex;

void fluxInfo(int ID);
void* creationThread(void* ID);
void* posteDeTravail(void* ID);
void travail(int ID);

#endif
