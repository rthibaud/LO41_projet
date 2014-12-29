#include "chaineDeProduction.h"

void* creationThread(void* ID)
{
	printf("je suis dans le thread %d \n ",(int)ID);
	//exit(0);
	posteDeTravail((int)ID);
}

void posteDeTravail(int ID)
{
	printf("Le poste %d rentre en action. \n",ID);
	sem_wait(&panneauTicket[ID]); //If the semaphore's value (ID) is greater than zero, then  the  		decrement  proceeds, and  the function returns, immediately.  If the semaphore currently has   		value zero, then the call blocks until either it  becomes  possibleto  perform the decrement 		(i.e., the semaphore value rises above zero), or a signal handler interrupts the call.*\


	printf("Le poste %d prend une caisse pleine et une vide \n",ID);
	sem_wait(&zoneCaissePleine[ID]); //a vider pour construir ses pieces
	sem_wait(&zoneCaisseVide[ID]);//a remplir avec les pieces produits

	if (ID<nbPostes-1) //si c est pas la derniere operation a faire
	{	
		printf("je suis dans la boucle %d\n",ID);
		sem_post(&panneauTicket[ID+1]); //envoi le tiket au poste aval
		//sem_post()  increments  (unlocks)  the semaphore pointed to by sem.  If the 			semaphore's value consequently  becomes  greater  than  zero,  thenanother  process  			or thread blocked in a sem_wait(3) call will be woken up and proceed to lock the 			semaphore.

		printf("fin boucle %d\n",ID);

	}

	/*travail(ID);*/
	sleep(5);
	printf("Le poste %d a termine, il fournit le poste suivant. \n",ID);

	if (ID>0) //le premier poste a pas de poste aval
	{
		sem_post(&zoneCaissePleine[ID-1]); //envoi la caisse vide au poste aval
	}

	if (ID<nbPostes-1) //
	{
		sem_post(&zoneCaisseVide[ID+1]); //envoi la caisse pleine au poste amont
	}

	/*pthread_mutex_lock(&mutex);
	if (sem_getvalue(&zoneCaissePleine[ID-1])<2 )// si j ai max deux caisses  
	{
		pthread_mutex_unlock(&mutex);
		posteDeTravail(ID);
	}*/
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
