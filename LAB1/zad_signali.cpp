#include <iostream>
#include <unistd.h>
#include <csignal>
using namespace std;

int unos = 0;

void prekidnaRutina(int sig){
	switch (sig) {
		case SIGINT:
			unos=1;
			break;
		case SIGQUIT:
			unos=2;
			break;
		case SIGTSTP:
			unos=2;
			break;
		}
}

int main(){

	cout<<"NIM"<<endl<<endl;

	// postavljanje signala
	sigset(SIGINT, prekidnaRutinaJedan);
	sigset(SIGQUIT, prekidnaRutinaDva);
	sigset(SIGTSTP, prekidnaRutinaTri);



	// postavke igre
	int m=3;
	cout<<"M="<<m<<endl;
	/*cin>>m;
	while(m<3){
		cout<<"Broj mora biti veci od 2!"<<endl;
		cout<<"M=";
		cin>>m;
	} NI TO MI NETREBA, BUDE 3 FIKSNO */

	int n=0;
	cout<<"N=";
	cin>>n;
	while(n<m){
		cout<<"Broj sibica na stolu mora biti veci od "<< m <<" !"<<endl;
		cout<<"N=";
		cin>>n;
	}

	cout<<"Parametri su ispravni. Zapocinjem igru."<<endl<<endl;



	// igra
	string igrac;
	string pobjednik;
	int i=1;
	// UNOOOOOOOOOOOOOOOOOS int unos;
	while(n>0){
		if(i % 2 != 0){
			igrac="A";
			pobjednik="B";
		}
		else{
			igrac="B";
			pobjednik="A";
		}

		cout<<"Zigica na stolu: "<<n<<". Na redu je igrac: "<<igrac<<endl;
		cout<<igrac<<":";
		cin>>unos; //CEKANJE
		while(unos>n){
			cout<<"Nije moguce uzeti vise sibica nego sto ih ima na stolu!"<<endl;
			cout<<igrac<<":";
			cin>>unos;
		}
		/*while(unos>m){
			cout<<"Nije moguce uzeti vise od "<<m<<" sibica!"<<endl;
			cout<<igrac<<":";
			cin>>unos;
		} MISLIM DA JE OVO NEPOTREBNO VISE */

		n=n-unos;
		i++;
		cout<<endl;
	}

	cout<<"Zigica na stolu: "<<n<<". Pobjedio je igrac: "<<pobjednik<<endl;

	//system("pause");  NE RADI NA BARKI
	return 0;

}
