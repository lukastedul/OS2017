#include<iostream>
#include<cstdlib>
#include<pthread.h>
#include<unistd.h>
using namespace std;

int n;
int *trazim, *broj;

void ulazUKriticniOdsjecak(int i){
	trazim[i]=1;
	for(int j=0; j<n; j++){
		if(broj[j]>broj[i]){
			broj[i]=broj[j];
		}
	}
	broj[i]++;
	trazim[i]=0;
	
	for(int j=0;j<n;j++){
		while(trazim[j]!=0);
		while(broj[j]!=0 && (broj[j]<broj[i] || (broj[j]==broj[i] && j<i)));
	}
}

void izlazIzKriticnogOdsjecka(int i){
	broj[i]=0;
}

int novi() {
        static int i=0;
        return i++;
}

void *algoritam(void *p){
	int k, m, i;
	i=novi();
	
	for(k=1; k<=5;k++){
		ulazUKriticniOdsjecak(i);
		for(m=1;m<=5;m++){
			cout<<"Dretva "<<i+1<<", K.O. br: "<<k<<" ("<<m<< "/5)\n";
			sleep(1);
		}
		izlazIzKriticnogOdsjecka(i);
	}
}

int main(int argc, char *argv[]){

	int i;
	pthread_t *v;

	if(argc<2){
		cout<<"Krivi unos"<<endl;
		return 0;
	}

	n=atoi(argv[1]);
	if(!n){
		cout<<"Krivi unos"<<endl;
		return 0;
	}

	v=(pthread_t*)malloc(sizeof(pthread_t)*n); //alociranje memorije za dretvu
	trazim=(int *)malloc(sizeof(int)*n); //trazim
	broj=(int *)malloc(sizeof(int)*n); //broj
	
	for(i=0;i<n;i++){
		pthread_create(&v[i],NULL, algoritam, NULL); //kreiranje dretvi
	}
	for(i=0;i<n;i++){
		 pthread_join(v[i], NULL); //čekanje na završavanje dretvi
	}

	return 0;
}