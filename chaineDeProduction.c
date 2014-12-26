#include "chaineDeProduction.h"


int	P (int SemId, int Nsem) {		/*   P(s)      */
	struct sembuf SemBuf = {0,-1,0} ;
	SemBuf.sem_num = Nsem ;
	return semop(SemId, &SemBuf,1) ;
}

int	V (int SemId, int Nsem) {		/*   V(s)      */
	struct sembuf SemBuf = {0,1,0} ;
	SemBuf.sem_num = Nsem ;
	return semop(SemId, &SemBuf, 1) ;
}

int initsem(key_t semkey) 
{
    
	int status = 0;		
	int semid_init;
   	union semun {
		int val;
		struct semid_ds *stat;
		ushort * array;
	} ctl_arg;
    if ((semid_init = semget(semkey, 2, IFLAGS)) > 0) {
		
	    	ushort array[nbPoste+1] = {0, 0};
	    	ctl_arg.array = array;
	    	status = semctl(semid_init, 0, SETALL, ctl_arg);
    }
   if (semid_init == -1 || status == -1) { 
	perror("Erreur initsem");
	return (-1);
    } else return (semid_init);
}

void* creationThread(void* ID)
{
	printf("je suis dans le thread %d \n ",(int)ID);
	exit(0);
}