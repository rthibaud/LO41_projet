#include "chaineDeProduction.h"


int main (int argc, char* argv[])
{
	int num, i;
	pthread_mutex_init(&mutex,NULL);

	tid=(pthread_t *)malloc((nbPostes+1)*sizeof(pthread_t)); 

	panneauTicket=(sem_t*)malloc((nbPostes+1)*sizeof(sem_t));
	zoneCaissePleine=(sem_t*)malloc((nbPostes+1)*sizeof(sem_t));
	zoneCaisseVide=(sem_t*)malloc((nbPostes+1)*sizeof(sem_t));




	for(num=0;num<nbPostes;num ++)
	{	
		sem_init(&panneauTicket[num],0,2); 
		sem_init(&zoneCaissePleine[num],0,0);
		sem_init(&zoneCaisseVide[num],0,1);	
	}


	//flux de demande
	sem_post(&zoneCaissePleine[nbPostes]); //le premier poste a toujours des materiaux disponibles
	for(num=0;num<nbPostes+1; num ++)
	{	
		sem_getvalue(&zoneCaissePleine[num], &val);
		if (val>0)
		{	
			printf("Le poste %d a %d pieces pretes, j'en prends une \n", num+1, val);
			sem_wait(&zoneCaissePleine[num+1]);
		}
		else
		{	
			pthread_create(&tid[num],0,(void *(*)())creationThread,(void*)num);
			pthread_join(tid[num],NULL);
		}
	}

   	//flux de production
	sem_post(&zoneCaisseVide[0]); //le dernier poste a pas besoin de caisse vide, car la voiture est prise directement
	for(num=nbPostes;num>=0; num --)
	{	
		sem_getvalue(&zoneCaissePleine[num], &val);
		if (val>0)
		{	
			printf("Le poste %d a %d pieces pretes, j'en prends une \n", num+1, val);
			sem_wait(&zoneCaissePleine[num+1]);
		}
		else
		{	
			pthread_create(&tid[num],0,(void *(*)())creationThread,(void*)num);
			pthread_join(tid[num],NULL);
		}
	}
	

	//liberation des ressources
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
