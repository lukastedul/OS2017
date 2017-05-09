#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<time.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>

struct sembuf SemBuf;

void brisi();
int n;
int m;
int semPisi;
int semPun;
int semPrazan;
int segId;
int *ULAZ, *IZLAZ;
struct podaci {
	int ulaz;
	int izlaz;
	int M[5];
};

int main(int argc, char *argv[]){
	if(argc<3){
		printf("Krivi unos!\n");
		return 0;
	}

	srand(time(NULL));
	int n = atoi(argv[2]);
	int m = atoi(argv[1]);
	sigset(SIGINT, brisi);
    semPisi = semget(IPC_PRIVATE, 1, 0666);
	semPun = semget(IPC_PRIVATE, 1, 0666);
	semPrazan = semget(IPC_PRIVATE, 1, 0666);
	semctl(semPisi, 0, SETVAL, 1);
	semctl(semPun, 0, SETVAL, 5);
	semctl(semPrazan, 0, SETVAL, 0);
	segId = shmget(IPC_PRIVATE, 100*sizeof(int), 0666);
	if(segId == -1){
		exit(1);
	}
	struct podaci *data  = shmat(segId, (void *) 0, 0);
	data->ulaz=0;
	data->izlaz=0;

	int d;
	for(d = 1; d <= m; d++ ){
		if(fork() == 0 ){ //proizvodac
			int i = 0;
			int ulaz;
			srand(time(NULL) ^ (getpid()<<16));
			do{
				SemBuf.sem_op = -1;
				semop(semPun, &SemBuf, 1);
				
				SemBuf.sem_op = -1;
				semop(semPisi, &SemBuf, 1);
				ulaz = data->ulaz;
				data->M[ulaz] = rand()%1000;
				printf("Proizvodac %d salje '%d'\n",d,data->M[ulaz]);
				data->ulaz = (ulaz+1)%5;
				i = i + 1;
				
				SemBuf.sem_op = 1;
				semop(semPisi, &SemBuf, 1);

				SemBuf.sem_op = 1;
				semop(semPrazan, &SemBuf, 1);

			}while(i < n);

			printf("Proizvodac %d zavrsio sa slanjem\n",d);
			exit(0);
		}
	}
	
	if(fork() == 0 ){ //potrosac
		int i = 0;
		int suma = 0;
		int uk = m*n;
		int izlaz;
		do{
			SemBuf.sem_op  = -1;
		    semop(semPrazan, & SemBuf, 1);
			izlaz = data->izlaz;
			printf("Potrosac prima %d\n",data->M[izlaz]);
			data->izlaz = (izlaz+1)%5;
			suma += data->M[izlaz];
			SemBuf.sem_op  = 1;
		    semop(semPun, & SemBuf, 1);
			i = i + 1;
		}while(i<uk);

		printf("Potrosac - suma primljenih brojeva= %d\n", suma);

		exit(0);
	}
	while(m--){
		wait(NULL);
	}
	wait(NULL);

	brisi();
}

 void brisi(int sig){
	 (shmctl(segId, IPC_RMID, NULL) != -1);
	 (semctl(semPisi, 0, IPC_RMID, 0) != -1);
	 (semctl(semPun, 0, IPC_RMID, 0) != -1);
	 (semctl(semPrazan, 0, IPC_RMID, 0) != -1);
	 exit(0);
}
