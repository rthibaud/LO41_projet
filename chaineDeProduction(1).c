#include "chaineDeProduction.h"


void premierPoste(int ID) //ID=0
{
	printf("Demande envoyée. Le premier poste rentre en action. \n");
	
	//sem_wait(&zoneCaissePleine[ID]);
	//printf("Le poste %d prend une caisse pleine\n",ID);	
	sem_wait(&zoneCaisseVide[ID]);
	printf("Le poste %d prend une caisse vide \n",ID);

	sem_post(&panneauTicket[ID+1]);

	//travail
	
	printf("Le poste %d a termine, il fournit le poste suivant. \n",ID);

	sem_post(&zoneCaissePleine[ID+1]);

	pthread_mutex_lock(&mutex);
	sem_getvalue(&zoneCaissePleine[ID-1],&val);	
	if (val<2)// si j ai max deux caisses  
	{
		pthread_mutex_unlock(&mutex);
		posteDeTravail(ID+1);
	}
}

void* creationThread(void* ID)
{
	int a= (int)ID;
	premierPoste((int)ID);
	/*switch (a)
	{
		case 0:
			printf("boucle %d, poste: coloration fibres\n", a+1);
			posteDeTravail(a);
			break;
		case 1:
			printf("boucle %d, poste: fabrication de fils\n", a+1);			
			posteDeTravail(a);
			break;
		case 2:
			printf("boucle %d, poste: fabrication des tissus\n", a+1);
			posteDeTravail(a);
			break;		
		case 3:
			printf("boucle %d, poste: fabrication des sieges\n", a+1);
			posteDeTravail(a);
			break;	
	}*/
}

void posteDeTravail(int ID)
{
	sem_wait(&panneauTicket[ID]); //If the semaphore's value is greater than zero, then  the  		decrement  proceeds, and  the function returns, immediately.  If the semaphore currently has   		value zero, then the call blocks until either it  becomes  possibleto  perform the decrement 		(i.e., the semaphore value rises above zero), or a signal handler interrupts the call.*\

	printf("Le poste %d enleve le ticket et rentre en action. \n",ID);

	sem_wait(&zoneCaissePleine[ID]); //a vider pour construir ses pieces
	sem_wait(&zoneCaisseVide[ID]);//a remplir avec les pieces produits

	printf("Le poste %d prend une caisse pleine et une vide \n",ID);

	if (ID<nbPostes) //si c est pas la derniere operation a faire
	{	
		sem_post(&panneauTicket[ID+1]); //envoi le tiket au poste aval
		//sem_post()  increments  (unlocks)  the semaphore pointed to by sem.  If the 			semaphore's value consequently  becomes  greater  than  zero,  thenanother  process  			or thread blocked in a sem_wait(3) call will be woken up and proceed to lock the 			semaphore.
	}

	/*travail(ID);*/
	printf("Le poste %d a termine, il fournit le poste suivant. \n",ID);

	if (ID<nbPostes) //si c est pas la derniere operation a faire
	{	
		sem_post(&zoneCaissePleine[ID+1]);//envoi la caisse pleine au poste amont
	}

	else if (ID==nbPostes)
		printf("La voiture est finie!\n");

	if (ID>0) //le premier poste a pas de poste aval
	{
		sem_post(&zoneCaissePleine[ID-1]); //envoi la caisse vide au poste aval
	}

	if (ID<nbPostes-1) 
	{
		sem_post(&zoneCaisseVide[ID+1]); //envoi la caisse pleine au poste amont
	}

	pthread_mutex_lock(&mutex);
	sem_getvalue(&zoneCaissePleine[ID-1],&val);	
	if (val<2)
	{
		pthread_mutex_unlock(&mutex);
		posteDeTravail(ID+1);
	}
}


