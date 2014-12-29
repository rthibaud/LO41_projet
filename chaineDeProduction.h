#ifndef _CHAINEDEPRODUCTION_
#define _CHAINEDEPRODUCTION_


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define nbPostes 4


//int nbPostes;
int nbPieces;

sem_t *panneauTicket;
sem_t *zoneCaissePleine;
sem_t *zoneCaisseVide;
pthread_t *tid;
pthread_mutex_t mutex;






void* creationThread(void* ID);
void posteDeTravail(int ID);





#endif
