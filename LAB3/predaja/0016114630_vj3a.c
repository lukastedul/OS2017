#include <stdio.h>
#include <stdlib.h>
#include "unistd.h"
#include <time.h>
#include <signal.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>
#include <values.h>

void brisi();
int segId;

struct shm{
	sem_t sem[6];
};
struct shm *shared;

void proces(int brojProcesa)
{
	switch(brojProcesa)
	{
		case 2: //third
		sem_wait(&shared->sem[1]);
		break;
		case 3: //fourth
		sem_wait(&shared->sem[1]);
		break;
		case 4: //fifth
		sem_wait(&shared->sem[0]);
		break;
		case 5: //sixth
		sem_wait(&shared->sem[2]);
		break;
		case 6: //seventh
		sem_wait(&shared->sem[4]);
		sem_wait(&shared->sem[5]);
		sem_wait(&shared->sem[3]);
		break;
	}
	
	srand(time(NULL) ^ (getpid()<<16));
    int trajanje = rand() % 10 + 1;
    int t = trajanje;
    do{
        printf("Izvodim zadatak %d %d/%d\n",brojProcesa+1, trajanje, t);
		sleep(1);
    }while(trajanje--);
	
    sem_post(&shared->sem[brojProcesa]);
	if(brojProcesa == 1){
		sem_post(&shared->sem[brojProcesa]);
	}
	exit(0);
}

 int main(int argc, char *argv[] ){ 
     srand(time(NULL));
	 sigset(SIGINT, brisi);
    
	segId = shmget(IPC_PRIVATE, 10*sizeof(int), 0600);
    if(segId == -1){
		exit(1);
	}
	shared=shmat(segId,NULL,0);
    sigset(SIGINT, brisi);
    int i;
    for(i=0; i<7;i++){
		sem_init(&shared->sem[i], 1, 0);
	}
	for(i=0; i<7;i++){
		if(fork() == 0){
			proces(i);
		};
	}
	int n = 7;
	while(n--){
		wait(NULL);
	}
	for(i=0; i<7;i++){
		sem_destroy(&shared->sem[i]);
	}
	brisi();
	return 0;
 }
 
 void brisi(int sig){
	 int i;
	 (shmctl(segId, IPC_RMID, NULL) != -1);

	 for(i=0; i<7; i++){
		 (semctl(&shared->sem[i], 0, IPC_RMID, 0) != -1);
	}

	exit(0);
}