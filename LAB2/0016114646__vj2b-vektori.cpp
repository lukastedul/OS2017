#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<signal.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/ipc.h>
using namespace std;

long double *a, *b;
int id;

void brisanje(int sig){
	shmdt((long double*)b);
	shmctl(id,IPC_RMID,NULL);
	exit(0);
}

int main(int argc, char *argv[]){
	int l, m, n, broj, zad, counter, id;
	
	if(argc<4){
		cout << "Pogresan unos" << endl;
		return 0;
	}

	l=atoi(argv[1]);
	m=atoi(argv[2]);
	n=atoi(argv[3]);
	
	if(!(l && m && n)){
		cout << "Pogresan unos" << endl;
		return 0;
	}

	if(l<n){
		cout << "Pogresan unos - l mora biti veci od n" << cout;
		return 0;
	}
	
	a=(long double*)malloc(sizeof(int)*l);
	id=shmget(IPC_PRIVATE,sizeof(int)*100,0600);
	if(id==-1) exit(1);
	b=(long double*)shmat(id,NULL,0);
	sigset(SIGINT, brisanje);
	
	cout<<"Eksponenti="<<endl;
	srand(time(0));
	rand();
	for(int i=0; i<l; i++){
		a[i]=10*((double)rand()/(double)RAND_MAX);
		cout << setprecision(12) << fixed << a[i] << endl;
	}
	
	broj=l/n;
	zad=0;
	cout << "Eksponencijale = " << endl;
	for(int p=1; p<=n; p++){
		counter=zad;
		if(p!=n) zad += broj;
		else zad=l;
		switch(fork()){
			case -1:{
				cerr << "Pogreska" << endl;
				exit(-1);
				break;
			}
			case 0:{
				double brojnik, nazivnik;
				for(int j=counter; j<zad; j++){
					b[j]=0;
					for(int i=0; i<m; i++){
						brojnik = pow(a[j],i);
						nazivnik=1;
						if(i>0) for(int k=1; k<=i;k++) nazivnik *=k;
						b[j] += (double)brojnik/nazivnik;
					}
					usleep(10000);
				}
				exit(0);
				break;
			}
			default: break;
		}
	}
	while (n--) wait(NULL);
	for(int i=0;i<l;i++) cout << b[i] << endl;
	shmdt((long double*)b);
	shmctl(id, IPC_RMID, NULL);
	exit(0);
	return 0;	
}
