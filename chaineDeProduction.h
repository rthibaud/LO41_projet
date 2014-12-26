#ifndef _CHAINEDEPRODUCTION_
#define _CHAINEDEPRODUCTION_


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define IFLAGS (SEMPERM | IPC_CREAT)
#define SKEY   (key_t) IPC_PRIVATE	
#define SEMPERM 0600				  /* Permission */

pthread_t tid[];
pthread_mutex_t mutex[];
int nbPostes;


/*pour les sémaphores initialisation, libération, protection*/
int initsem(key_t semkey);
int	V (int SemId, int Nsem);
int	P (int SemId, int Nsem);


void* creationThread(void* ID);





#endif