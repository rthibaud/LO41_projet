#include "chaineDeProduction.h"

int main (int argc, char* argv[])
{
	int num;
	pthread_mutex_init(&mutex,NULL);

	accueil();

	struct sigaction action;
	action.sa_handler=traitant;
	sigaction(SIGINT,&action,NULL);

	tid=(pthread_t *)malloc((nbPostes+1)*sizeof(pthread_t)); 

	panneauTicket=(sem_t*)malloc((nbPostes+1)*sizeof(sem_t));
	zoneCaissePleine=(sem_t*)malloc((nbPostes+1)*sizeof(sem_t));
	zoneCaisseVide=(sem_t*)malloc((nbPostes+1)*sizeof(sem_t));

	for(num=0;num<nbPostes;num ++)
	{			
		sem_init(&zoneCaissePleine[num],0,2);
		sem_init(&zoneCaisseVide[num],0,2);
		if (num<nbPostes-1)
		{
			sem_init(&panneauTicket[num],0,0); 
		}
		else
		{
			sem_init(&panneauTicket[num],0,nbPieces);
		}	
	}

	for(num=0;num<nbPostes;num++)
	{
		pthread_create(tid+num,0,creationThread,(void *)num);
	}

	for(num=0;num<nbPostes;num++)
	{
		pthread_join(&tid[num],NULL);
	}

	/*liberation des ressources*/
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

	return 0;
}
