#include <iostream>
#include <csignal>
using namespace std;

static int n;

void Igra(int unos){

     int _unos = unos;
     static int i = 0;
     string igrac;
     string pobjednik;


     if(i % 2 != 0){
          igrac="A";
          pobjednik="B";
     }
     else{
          igrac="B";
          pobjednik="A";
     }

     if(unos>n){
          cout<<"Nije moguce uzeti vise zigica nego sto ih ima na stolu!"<<endl;
     }
     else{
          n=n-unos;
          i++;

          cout<<" Igrac "<<pobjednik<<" uzeo sa stola "<<_unos<<"."<<endl;

          if (n<=0) {
               cout<<"Zigica na stolu: "<<n<<". Pobjednik je igrac: "<<igrac<<endl;
          }
          else{
               cout<<"Zigica na stolu: "<<n<<". Na redu je igrac: "<<igrac<<endl;
          }
     }

}

void PrekidnaRutina(int sig){
     int unos = 0;
     switch (sig) {
          case SIGINT:
               unos = 1;
               break;
          case SIGQUIT:
               unos = 2;
               break;
          case SIGTSTP:
               unos = 3;
               break;
          default:
               break;
     }
     Igra(unos);
}

int main(int argc, char const *argv[]) {

     cout<<"M=3"<<endl;
     cout<<"N=";
	cin>>n;
	cout<<"Parametri su ispravni. Zapocinjem igru."<<endl;

     sigset(SIGINT, PrekidnaRutina);
     sigset(SIGQUIT,PrekidnaRutina);
     sigset(SIGTSTP,PrekidnaRutina);

     cout<<"Zigica na stolu: "<<n<<". Na redu je igrac: A"<<endl;

     while (n>0) {
          // CEKANJE
     }

     return 0;
}
