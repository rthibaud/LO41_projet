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
		case(2):nbPostes=8;break;
		case(3):nbPostes=15;break;
		case(4):nbPostes=35;break;
		case(5):nbPostes=100;break;
		case(6):nbPostes=300;break;
		case(7):nbPostes=800;break;
		case(8):printf("Combien de postes nécessite votre produit ? \n");
				scanf("%d",&nbPostes);break;
		case(0):printf("ben aurevoir alors \n");exit(0);break;
	}

	printf("Combien voulez-vous de pièces ? \n");
	scanf("%d",&nbPieces);

	nbPiecesProduites=0;
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
	free(tid_attr);
	free(panneauTicket);
	free(zoneCaissePleine);
	free(zoneCaisseVide);

	raise(SIGSTOP);
}

void* creationThread(void* ID)
{
	int i,val,timeOfProduction;
	i=(int)ID;

	srand(time(NULL));
	timeOfProduction=rand()%5;
	if (i==0)
	{
		pthread_mutex_lock(&mutex);
	
			sem_getvalue(&zoneCaissePleine[i+1],&val);
			while((nbPiecesProduites<nbPieces) || (val<=2))
			{
				pthread_mutex_unlock(&mutex);
				premierPoste(i,timeOfProduction);
				sem_getvalue(&panneauTicket[i],&val);
			}

	}
	else if (i==nbPostes-1)
	{
	
		sem_getvalue(&panneauTicket[i],&val);
		while(val>0)
		{
			dernierPoste(i,timeOfProduction);
			sem_getvalue(&panneauTicket[i],&val);
		}
		
	}
	else
	{
		pthread_mutex_lock(&mutex);
		sem_getvalue(&zoneCaissePleine[i+1],&val);
		while((nbPiecesProduites<nbPieces) || (val<=2))
		{
			pthread_mutex_unlock(&mutex);
			posteDeTravail(i,timeOfProduction);
			sem_getvalue(&panneauTicket[i],&val);
		}
	}
}

void posteDeTravail(int ID,int timeOfProduction)
{
	("poste %d: j'attends le ticket\n", ID);
	sem_wait(&panneauTicket[ID]);


	printf("oui\nLe poste %d prend une caisse pleine et une vide \n",ID);
	sem_wait(&zoneCaissePleine[ID-1]);
	sem_wait(&zoneCaisseVide[ID]);

	sem_post(&panneauTicket[ID-1]);

	printf("le poste %d prepare une piece...\n", ID);

	sleep(timeOfProduction);
	printf("Le poste %d a termine \n",ID);
	sem_post(&zoneCaissePleine[ID]);
	sem_post(&zoneCaisseVide[ID-1]);
	
	
}

void premierPoste(int ID, int timeOfProduction)
{
	sem_wait(&panneauTicket[ID]);
	

	printf("Le premier poste (%d) prend une caisse vide à remplir avec la matiere premiere\n",ID);
	sem_wait(&zoneCaisseVide[ID]);
	
	printf("le premier poste (%d) prepare une piece...\n", ID);
	sleep(timeOfProduction);
	sem_post(&zoneCaissePleine[ID]);
	printf("Le poste %d a termine\n",ID);	


  }

void dernierPoste(int ID, int timeOfProduction)
{

	sem_wait(&panneauTicket[ID]);

	printf("le poste %d a des pieces deja pretes, il envoie au poste aval\n", ID);
	sem_wait(&zoneCaissePleine[ID-1]);
	sem_post(&panneauTicket[ID-1]);

	printf("Le poste %d a termine, le %d eme produit est fini. \n",ID, nbPiecesProduites+1);
	pthread_mutex_lock(&mutex);
	nbPiecesProduites++;
	pthread_mutex_unlock(&mutex);

	sem_post(&zoneCaisseVide[ID-1]);
	if(nbPieces-nbPiecesProduites==0)
	{
		sem_post(&fin); /*on arrete le travail*/
	}

}

