#ifndef _CHAINEDEPRODUCTION_
#define _CHAINEDEPRODUCTION_


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>

#define nbPostes 4

int nbPieces;
int val, num;

sem_t *panneauTicket;
sem_t *zoneCaissePleine;
sem_t *zoneCaisseVide;
pthread_t *tid;
pthread_mutex_t mutex;

void traitant(int num);
void travail(int ID);

#endif
