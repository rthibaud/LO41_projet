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
	sem_post(&zoneCaissePleine[0]); //le premier poste a toujours des materiaux disponibles

	for(num=nbPostes;num>0; num --)
	{	
		sem_getvalue(&zoneCaissePleine[num-1], &val);
		if (val>0)
		{	
			printf("Le poste %d a %d pieces pretes, le poste %d en prends une \n", num-1, val,num);
			sem_wait(&zoneCaissePleine[num-1]);
			travail();
			sem_post(&zoneCaisseVide[num+1]);
			switch (num)
			{
				case 4:
				{
					printf("voiture prete\n");
					num=0;
					break;
				}
				case 3:
				{
					num=0;
					break;
				}
				case 2:
				{
					num=0;
					break;
				}
				case 1:
				{
					num=0;
					break;
				}
		}
		}
		else
		{	
			creationThread((void*)num);
			//pthread_create(&tid[num],0,(void *(*)())creationThread,(void*)num);
			//pthread_join(tid[num],NULL);
		}
	}

   	//flux de production
	sem_post(&zoneCaisseVide[nbPostes]); //le poste 4 a pas besoin de caisse vide, car la voiture est prise directement

	for(num=1;num<nbPostes+1; num ++)
	{	
		sem_wait(&zoneCaisseVide[num]); //decrement semaphore
		printf("Le poste %d prepare une piece \n", num);
		travail();
		sem_post(&zoneCaissePleine[num]); //increment semaphore
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
