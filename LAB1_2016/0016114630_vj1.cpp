#include <iostream>
#include <ctime>
#include <unistd.h>
#include <csignal>

using namespace std;
int tekprek=0;

void obradaprekida(int razina){
        cout<<"Obraduje se prekid razine "<<razina<<endl;
        for(int i=1;i<=5;i++){
              
                cout<<"Obrada prekida razine "<<razina<<" = "<<i<<"/5"<<endl;
                sleep(1);
        }
        cout<<"Obraden prekid razine "<<razina<<endl<<endl;
        
}

void prekidnarutina(int signal){
        int prioritet[4];
        int i;
        time_t v;
        time(&v);
        cout<<" prekidna rutina pokrenuta u  "<<ctime(&v)<<endl;

        switch(signal){
                case SIGINT:
                        i=1;
                        break;
                case SIGQUIT:
                        i=2;
                        break;
                case SIGTSTP:
                        i=3;
                        break;
                default:
                        return;
        }

        if(i>tekprek){
                prioritet[i]=tekprek;
                tekprek=i;
                sigrelse(signal);
                obradaprekida(i);
                sighold(signal);
                tekprek=prioritet[i];
                return;
        }
        
        cout<<"Prekid je manje razine "<<endl;
}

int main(){
	
	
        sigset(SIGINT,prekidnarutina);
        sigset(SIGQUIT,prekidnarutina);
        sigset(SIGTSTP,prekidnarutina);

        cout<<"Glavni program se izvodi"<<endl;
        
        for(int i=1;i<=20;i++){
                cout<<"Glavni program "<<i<<"/20"<<endl;
                sleep(1);
        }
        
        cout<<"Glavni program je gotov"<<endl;       
}

