#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h> //nez za kaj je to
#include <unistd.h> //to je za sleep
#include <signal.h>
#include <sys/wait.h>
 
void Proces2(void)
{
   printf("proces2\n");
}

void Proces1(void)
{
   printf("proces1\n");
}

int main(void)
{ 
   /* pokretanje paralelnih procesa */
   if (fork() == 0) {
      Proces1();
      exit(0);
   }
   if (fork() == 0) {
      Proces2();
      exit(0);
   }
   wait(NULL);
   wait(NULL);
 
   return 0;
}