#include "chaineDeProduction.h"
#include <malloc.h>


int main (int argc, char* argv[])
{
	int num, i;

	pthread_mutex_init(&mutex,NULL);

	//nbPostes=4;

	
	tid=(pthread_t *)malloc((nbPostes+1)*sizeof(pthread_t));

	panneauTicket=(sem_t*)malloc((nbPostes+1)*sizeof(sem_t));
	zoneCaissePleine=(sem_t*)malloc((nbPostes+1)*sizeof(sem_t));
	zoneCaisseVide=(sem_t*)malloc((nbPostes+1)*sizeof(sem_t));

	for(num=0;num<nbPostes+1;num ++)
	{	
		sem_init(&panneauTicket[num],0,2);
		sem_init(&zoneCaissePleine[num],0,2);
		sem_init(&zoneCaisseVide[num],0,2);
		pthread_create(&tid[num],0,(void *(*)())creationThread,(void*)num);
	}
	
//printf("%10s%10s%10s%10s%10s\n\n", "ciao","io","tre","bla","bla");

	for(num=0;num<nbPostes+1;num++)
	{
		pthread_join(tid[num],NULL);
	}


	free(tid);
	free(panneauTicket);
	free(zoneCaissePleine);
	free(zoneCaisseVide);

	return 0;
}
