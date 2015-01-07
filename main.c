#include "chaineDeProduction.h"

int main (int argc, char* argv[])
{
	int num,i,valeur1,valeur2;
	pthread_mutex_init(&mutex,NULL);

	struct sigaction action;
	action.sa_handler=traitant;

	accueil();



	tid=(pthread_t *)malloc((nbPostes+1)*sizeof(pthread_t)); 
	tid_attr=(pthread_attr_t*)malloc((nbPostes+1)*sizeof(pthread_attr_t)); 

	panneauTicket=(sem_t*)malloc((nbPostes+1)*sizeof(sem_t));
	zoneCaissePleine=(sem_t*)malloc((nbPostes+1)*sizeof(sem_t));
	zoneCaisseVide=(sem_t*)malloc((nbPostes+1)*sizeof(sem_t));

	sigaction(SIGINT,&action,NULL);
	sem_init(&fin,0,0);
	

	for(num=0;num<nbPostes;num ++)
	{			
		sem_init(&zoneCaissePleine[num],0,2);
		sem_init(&zoneCaisseVide[num],0,2);
		if (num<nbPostes-1)
		{
			sem_init(&panneauTicket[num],0,0); 
		}
		else //le dernier poste recoit la demande de pieces, et donc les tickets
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
	printf("votre ordre est pret. \n");

	for(i=0;i<nbPostes;i++)
	{
		sem_getvalue(&zoneCaissePleine[i],&valeur1);
		sem_getvalue(&zoneCaisseVide[i],&valeur2);
		printf("\ncaisses pleine poste %d: %d \n caisses vides poste %d: %d\n\n", i, valeur1,i,valeur2);
	}

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
