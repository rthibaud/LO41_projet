#include "chaineDeProduction.h"

void accueil()
{
	int choix;

	printf("Tripote et Mascagne, bonjour : \n \n");

	printf("Que pouvons nous faire pour vous : \n");
	printf(" 1: Des vis \n");
	printf(" 2: Des étagères \n");
	printf(" 3: Des chaises \n");
	printf(" 4: Des armoires \n");
	printf(" 5: Des pergolas \n");
	printf(" 6: Des jolis petits chalets à Courchevel \n");
	printf(" 7: Des modules lunaires \n");
	printf(" 8: Des produits encore jamais vu \n");
	printf(" 0: Vous laissez partir ... \n");

	scanf("%d",&choix);

	printf("%d \n",choix);

	while ((choix<0)||(choix>8))
	{
		printf("Malgrè l'étendu de nos domaines d'applications nous ne pouvons satisfaire votre demande, veuillez resaisir une réponse : \n");
		printf("Que pouvons nous faire pour vous : \n");
		printf(" 1: Des vis \n");
		printf(" 2: Des étagères \n");
		printf(" 3: Des chaises \n");
		printf(" 4: Des armoires \n");
		printf(" 5: Des pergolas \n");
		printf(" 6: Des jolis petits chalets à Courchevel \n");
		printf(" 7: Des modules lunaires \n");
		printf(" 8: Des produits encore jamais vu \n");
		printf(" 0: Vous laissez partir ... \n");
		choix=0;
		scanf("%d",&choix);
	}

	switch(choix)
	{
		case(1):nbPostes=2;break;
	}
}

void* creationThread(void* ID)
{
	printf("je suis dans le thread %d \n ",(int)ID);
	exit(0);
}

void posteDeTravail(int ID)
{
	int nbCaisse;
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
	sem_getvalue(&zoneCaissePleine[ID-1],&nbCaisse);
	if (nbCaisse<2 )  
	{
		pthread_mutex_unlock(&mutex);
		posteDeTravail(ID);
	}
}

void premierPoste(int ID)
{
	printf("Le poste %d rentre en action. \n",ID);
	

	printf("Le poste %d prend une caisse pleine \n",ID);
	sem_wait(&zoneCaissePleine[ID]);
	if (ID<nbPostes-1)
	{
		sem_post(&panneauTicket[ID+1]);
	}

	/*travail(ID);*/
	printf("Le poste %d a termine, il fournit le poste suivant. \n",ID);

	if (ID<nbPostes-1)
	{
		sem_post(&zoneCaisseVide[ID-1]);
	}

	pthread_mutex_lock(&mutex);
	if (nbPiecesProduites<nbPieces) 
	{
		pthread_mutex_unlock(&mutex);
		premierPoste(ID);
	}
}