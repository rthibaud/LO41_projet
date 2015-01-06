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

	/*switch(choix)
	{
		case(1):nbPostes=2;break;
		case(2):nbPostes=8;break;
		case(3):nbPostes=15;break;
		case(4):nbPostes=35;break;
		case(5):nbPostes=100;break;
		case(6):nbPostes=300;break;
		case(7):nbPostes=800;break;
		case(8):printf("Combien de postes nécessite votre produit ? \n");
				scanf("%d",&nbPostes);break;
		case(0):printf("ben aurevoir alors \n");exit(0);break;
	}*/

	printf("Combien voulez-vous de pièces ? \n");
	scanf("%d",&nbPieces);
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

void traitant(int num)
 {
	printf("\nLiberation des ressources..\n");
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

	raise(SIGSTOP);
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
	raise(SIGSTOP);
  }

void travail(int ID)
{
	sem_wait(&zoneCaisseVide[ID]); 
	printf("Le poste %d prepare une piece \n", ID);
	sleep(1); /*BOUCLE*/
	printf("piece construite par le poste %d\n", ID);
	sem_post(&zoneCaissePleine[ID]);
}