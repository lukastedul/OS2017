#include <iostream>
#include <unistd.h>
#include <csignal>
using namespace std;

static int n;

void Igra(int unos){

     int _unos = unos; //koliko sibica igrac uzima sa stola
     static int i = 0; //brojac koji sluzi za odredivanje igraca A ili B
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
               cout<<"Nije moguce uzeti vise sibica nego sto ih ima na stolu!"<<endl;
          }
          else{
               n=n-unos;
               i++;
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
          case 1:
               unos = 1;
               break;
          case 2:
               unos = 2;
               break;
          case 3:
               unos = 3;
               break;
          default:
               cout<<"Nije moguce uzeti vise od 3 sibice AL NI U BARKA PROGRAMU!"<<endl;
               break;
     }
     Igra(unos);
}

int main(int argc, char const *argv[]) {

     // postavljanje parametaraa
     cout<<"N=";
	cin>>n;
	cout<<"Parametri su ispravni. Zapocinjem igru."<<endl;

     /* postavljanje signala
     sigset(SIGINT,PrekidnaRutina);
     sigset(SIGQUIT,PrekidnaRutina);
     sigset(SIGTSTP,PrekidnaRutina);
     */

     cout<<"Zigica na stolu: "<<n<<". Na redu je igrac: A"<<endl; //ovo se samo jednom izvrsi

     // cekanje na prekid
     int sig;
     while (n>0) {
          cin>>sig;
          PrekidnaRutina(sig);
     }

     system("pause");
     return 0;
}
