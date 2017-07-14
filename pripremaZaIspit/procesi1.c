#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h> //nez za kaj je to
#include <unistd.h> //to je za sleep
#include <signal.h>
#include <sys/wait.h>

int Id; /* identifikacijski broj segmenta */
int *ZajednickaVarijabla;
 
void Pisac(int i)
{
   *ZajednickaVarijabla = i;
}

void Citac(void)
{
   int i;

   do {
      i = *ZajednickaVarijabla;
      printf("Procitano %d\n", i);
      sleep(1);
   } while (i == 0);

   printf("Procitano je: %d\n", i);
}
void brisi(int sig)
{
   /* oslobađanje zajedničke memorije */
   shmdt(ZajednickaVarijabla);
   shmctl(Id, IPC_RMID, NULL);
   exit(0);

}
int main(void)
{
   /* zauzimanje zajedničke memorije */
   Id = shmget(IPC_PRIVATE, sizeof(int)*100, 0600);
   /* sizeof(int) je dovoljno memorije, ali u nekim slucajevima (pinus) 
      treba zatraziti vise memorije, pa je u primjeru broj pomnozen sa 100 */
 
   if (Id == -1)
      exit(1);  /* greška - nema zajedničke memorije */
 
   ZajednickaVarijabla = (int *) shmat(Id, NULL, 0);
   *ZajednickaVarijabla = 0;
   //sigset(SIGINT, brisi);//u slučaju prekida briši memoriju
 
   /* pokretanje paralelnih procesa */
   if (fork() == 0) {
      Citac();
      exit(0);
   }
   if (fork() == 0) {
      sleep(5);
      Pisac(123);
      exit(0);
   }
   wait(NULL);
   wait(NULL);
   brisi(0);

 
   return 0;
}