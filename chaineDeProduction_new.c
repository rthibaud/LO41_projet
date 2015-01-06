#include "chaineDeProduction.h"


void fluxInfo(int ID) 
{
	//pthread_create(&tid[1],0,(void *(*)())creationThread,(void*)1);
}

void* creationThread(void* ID)
{
	int a= (int)ID;
	switch (a)
	{
		case 1:
			printf("demande voiture reçue, demande des materiaux\n");
			break;
		case 2:
			printf("poste 2 reveillé. Demande pieces au poste 1\n");
			break;
		case 3:
			printf("poste 3 reveillé. Demande pieces au poste 2\n");
			break;		
		case 4:
			printf("poste 4 reveillé. Demande pieces au poste 3\n");
			break;	
	}
}

void* posteDeTravail(void* ID)
{
	
}

void travail()
{
	sleep(4);
	printf("piece construite\n");
}



