#include "chaineDeProduction.h"

void* creationThread(void* ID)
{
	printf("je suis dans le thread %d \n ",(int)ID);
	exit(0);
}

void posteDeTravail(int ID)
{
	printf("Le poste %d rentre en action. \n",ID);
	sem_wait(&panneauTicket[ID]);

	printf("Le poste %d prend une caisse pleine et une vide \n",ID);
	sem_wait(&zoneCaissePleine[ID]);
	sem_wait(&zoneCaisseVide[ID]);

	if (ID<nbPostes-1)
	{
		sem_post(&panneauTicket[ID+1]);
	}

	/*travail(ID);*/
	printf("Le poste %d a termine, il fournit le poste suivant. \n",ID);

	if (ID>0)
	{
		sem_post(&zoneCaissePleine[ID-1]);
	}

	if (ID<nbPostes-1)
	{
		sem_post(&zoneCaisseVide[ID-1]);
	}

	pthread_mutex_lock(&mutex);
	if (sem_getvalue(&zoneCaissePleine[ID-1])<2 )  
	{
		pthread_mutex_unlock(&mutex);
		posteDeTravail(ID);
	}
}

/*void premierPoste(int ID)
{
	printf("Le poste %d rentre en action. \n",ID);
	

	printf("Le poste %d prend une caisse pleine et une vide \n",ID);
	sem_wait(&zoneCaissePleine[ID]);
	sem_wait(&zoneCaisseVide[ID]);

	if (ID<nbPostes-1)
	{
		sem_post(&panneauTicket[ID+1]);
	}

	/*travail(ID);
	printf("Le poste %d a termine, il fournit le poste suivant. \n",ID);

	if (ID>0)
	{
		sem_post(&zoneCaissePleine[ID-1]);
	}

	if (ID<nbPostes-1)
	{
		sem_post(&zoneCaisseVide[ID-1]);
	}

	pthread_mutex_lock(&mutex);
	if (sem_getvalue(&zoneCaissePleine[ID-1])<2 ) 
	{
		pthread_mutex_unlock(&mutex);
		posteDeTravail(ID);
	}
}*/