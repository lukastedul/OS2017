#include <iostream>
using namespace std;

int main(){

	cout<<"NIM"<<endl<<endl;

	int m,n;

	cout<<"M=";
	cin>>m;
	while(m<3){
		cout<<"Broj mora biti veci od 2!"<<endl;
		cout<<"M=";
		cin>>m;
	}

	cout<<"N=";
	cin>>n;
	while(n<m){
		cout<<"Broj sibica na stolu mora biti veci od M!"<<endl;
		cout<<"N=";
		cin>>n;
	}

	cout<<"Parametri su ispravni. Zapocinjem igru."<<endl<<endl;

	string igrac;
	string pobjednik;
	int i=1;
	int unos;
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
		cin>>unos;
		while(unos>n){
			cout<<"Nije moguce uzeti vise sibica nego sto ih ima na stolu!"<<endl;
			cout<<igrac<<":";
			cin>>unos;
		}
		while(unos>m){
			cout<<"Nije moguce uzeti vise od "<<m<<" sibica!"<<endl;
			cout<<igrac<<":";
			cin>>unos;
		}

		n=n-unos;
		i++;
		cout<<endl;
	}

	cout<<"Zigica na stolu: "<<n<<". Pobjedio je igrac: "<<pobjednik<<endl;


	system("pause");
	return 0;

}
