/* int shmget(key_t key, int size, int flags); stvaranje novog segmenta i njegovog kljuca  
 * char *shmat(int segid, char *addr, int flags); vezanje segmenta na određenu adresu
 * int shmdt(char *addr); otpuštanje segmenta
 * shmctlint shmctl(int segid, int cmd, struct shmid_ds *sbuf); uništavanje segmenta
 */


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

	int l, m, n, broj, zad, brojac, id;

	if(argc<4){
		cout<<"Krivi unos"<<endl;
		return 0;
	}

	l=atoi(argv[1]); //velicina vektora odnosno broj eksponenata
	m=atoi(argv[2]); //
	n=atoi(argv[3]); //broj procesa
	
	if(!(l && m && n)){
		cout<<"Krivi unos"<<endl;
		return 0;
	}
	if(l<n){
		cout<<"Krivi unos (l mora biti veci od n)"<<cout;
		return 0;
	}
	
	a=(long double*)malloc(sizeof(int)*l); //alociranje memorije
	id=shmget(IPC_PRIVATE,sizeof(int)*100,0600); //stvaranje novog segmenta
												 //dozvola pristupa 0600 znači da korisnik može čitati i pisati, a grupa i ostali ne mogu
 												 //vraća identifikacijski broj segmenta ili -1 u slučaju greške

	if(id==-1){
		exit(1); //greška
	}
	b=(long double*)shmat(id,NULL,0); //alociranje memorije i vezanje na adresni prostor

	sigset(SIGINT, brisanje);
	
	cout<<"Eksponenti="<<endl;
	srand(time(0)); //seed za random brojeve
	rand();			//generator
	for(int i=0; i<l; i++){
		a[i]=10*((double)rand()/(double)RAND_MAX); //RAND_MAX je najveći broj iz rand, 32767
		cout<<setprecision(12)<<fixed<<a[i]<<endl;
	}

	broj=l/n; //raspoređivanje posla ravnomjerno
	zad=0; //
	cout<<"Eksponencijale="<<endl;
	for(int p=1; p<=n; p++){
		brojac=zad;
		if(p!=n){
			zad += broj;
		}
		else{
			zad=l;
		}
		switch(fork()){
			case -1:{
				cout<<"Greska"<<endl;
				exit(-1);
				break;
			}
			case  0:{
				double brojnik, nazivnik;
				for(int j=brojac; j<zad; j++){
					b[j]=0;
					for(int i=0; i<m; i++){
						brojnik = pow(a[j],i);
						nazivnik=1;
						if(i>0){
							for(int k=1; k<=i;k++){
								nazivnik=k; //*
							}
						}
						b[j] += (double)brojnik/nazivnik;
					}
					usleep(10000);
				}
				exit(0);
				break;
			}
			default:break;
		}
	}

	while (n--){
		wait(NULL);  //cekanje da svi procesi zavrse
	}
	for(int i=0;i<l;i++){
		cout << b[i] << endl;
	}
	shmdt((long double*)b); //otpustanje segmenta iz adresnog prostora
	shmctl(id, IPC_RMID, NULL); //unistavanje segmenta
	exit(0);

	return 0;	
}