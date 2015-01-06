#include "chaineDeProduction.h"

int main (int argc, char* argv[])
{
	int num, i, h;
	pthread_mutex_init(&mutex,NULL);

	accueil();

	struct sigaction action;
	action.sa_handler=traitant;
	sigaction(SIGINT,&action,NULL);

	tid=(pthread_t *)malloc((nbPostes+1)*sizeof(pthread_t)); 

	panneauTicket=(sem_t*)malloc((nbPostes+1)*sizeof(sem_t));
	zoneCaissePleine=(sem_t*)malloc((nbPostes+1)*sizeof(sem_t));
	zoneCaisseVide=(sem_t*)malloc((nbPostes+1)*sizeof(sem_t));

	for(num=0;num<=nbPostes;num ++)
	{	
		sem_init(&panneauTicket[num],0,2); 
		sem_init(&zoneCaissePleine[num],0,0);
		sem_init(&zoneCaisseVide[num],0,2);	
	}


	

	/*flux de demande*/
	sem_post(&zoneCaissePleine[0]); /*le premier poste a toujours des materiaux disponibles*/


	for(num=nbPostes;num>0; num --)
	{	
		printf("poste %d reveillé \n", num);
		sem_getvalue(&zoneCaissePleine[num-1], &val);
		if (val>0)
		{	
			sem_wait(&zoneCaissePleine[num-1]);
			printf("Le poste %d a %d pieces pretes, le poste %d en prends une \n", num-1, val,num);
			travail(num);
			sem_post(&zoneCaisseVide[num-1]);
			switch (num)
			{
				case nbPostes:
				{
					printf("voiture prete\n");
					num=0;
					break;
				}
				default:
				{
					num=num+2;
					break;
				}
			}
		}
		else
		{	
			printf("Demande pieces au poste %d\n", num-1);
		}
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
