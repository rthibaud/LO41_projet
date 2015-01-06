#include "chaineDeProduction.h"


void fluxInfo(int ID) 
{

}

void* creationThread(void* ID)
{

}

void* posteDeTravail(void* ID)
{
	
}

void travail(int ID)
{
	sem_wait(&zoneCaisseVide[ID]); 
	printf("Le poste %d prepare une piece \n", ID);
	sleep(3);
	printf("piece construite par le poste %d\n", ID);
	sem_post(&zoneCaissePleine[ID]);
}



