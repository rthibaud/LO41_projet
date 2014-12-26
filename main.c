#include "chaineDeProduction.h"


int main (int argc, char* argv[])
{
	int num;

	nbPostes=4;

	*tid=(pthread_t)malloc((nbPostes+1)*sizeof(pthread_t));

	for(num=0;num<nbPostes;num ++)
	{
		pthread_create(tid+num,0,(void *(*)())creationThread,(void*)num);
	}
return 0;
}