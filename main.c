#include "chaineDeProduction.h"

int main (int argc, char* argv[])
{
	int num,k;
	pthread_mutex_init(&mutex,NULL);

	struct sigaction action;
	action.sa_handler=traitant;
	sigaction(SIGINT,&action,NULL);
	accueil();

	tid=(pthread_t *)malloc((nbPostes+1)*sizeof(pthread_t)); 
	tid_attr=(pthread_attr_t*)malloc((nbPostes+1)*sizeof(pthread_attr_t)); 

	panneauTicket=(sem_t*)malloc((nbPostes+1)*sizeof(sem_t));
	zoneCaissePleine=(sem_t*)malloc((nbPostes+1)*sizeof(sem_t));
	zoneCaisseVide=(sem_t*)malloc((nbPostes+1)*sizeof(sem_t));

		sem_init(&fin,0,0);

	for(num=0;num<nbPostes;num ++)
	{			
		sem_init(&zoneCaissePleine[num],0,2);
		sem_init(&zoneCaisseVide[num],0,2);
		if (num<nbPostes-1)
		{
			sem_init(&panneauTicket[num],0,1); 
		}
		else
		{
			sem_init(&panneauTicket[num],0,nbPieces);
		}
	}


	for(num=0;num<nbPostes;num++)
	{
		pthread_attr_init (tid_attr+num);
 		pthread_attr_setdetachstate(tid_attr+num, PTHREAD_CREATE_DETACHED) ;
  		pthread_create (tid+num, tid_attr+num,creationThread,(void*)num);
	}

	/*for(num=0;num<nbPostes;num++)
	{
		pthread_join((tid+num),NULL);
	}*/


	sem_wait(&fin);

	/*liberation des ressources*/
	for(num=0;num<nbPostes+1;num++)
	{
		sem_destroy(&panneauTicket[num]);
		sem_destroy(&zoneCaissePleine[num]);
		sem_destroy(&zoneCaisseVide[num]);
	}
	free(tid);
	free(tid_attr);
	free(panneauTicket);
	free(zoneCaissePleine);
	free(zoneCaisseVide);
	
	//return 0;
}
