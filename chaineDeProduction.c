#include "chaineDeProduction.h"

void traitant(int num)
 {
	printf("\nLiberation des ressources..\n");
	for(num=0;num<nbPostes+1;num++)
	{
		sem_destroy(&panneauTicket[num]);
		sem_destroy(&zoneCaissePleine[num]);
		sem_destroy(&zoneCaisseVide[num]);
	}
	free(tid);
	free(panneauTicket);
	free(zoneCaissePleine);
	free(zoneCaisseVide);

	raise(SIGSTOP);
  }

void travail(int ID)
{
	sem_wait(&zoneCaisseVide[ID]); 
	printf("Le poste %d prepare une piece \n", ID);
	sleep(1); //BOUCLE
	printf("piece construite par le poste %d\n", ID);
	sem_post(&zoneCaissePleine[ID]);
}