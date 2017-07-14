#include <stdio.h>
#include <pthread.h>
//#include <stdlib.h> //nez za kaj je to
#include <unistd.h> //to je za sleep

pthread_mutex_t monitor;
int zadnji = NULL;

void *Ping()
{
   while(1)
   {
      sem_wait(&red1);
      printf("Ping\n");
      sleep(1);
      sem_post(&red2);
   }
   pthread_exit(0);
}

void *Pong()
{
   while(1)
   {
      pthread_mutex_lock(&monitor);
         while(zadnji==2){
            pthread_cond_wait(&uvjet,&monitor)
         }
         zadnja="PONG";
         printf("Pong\n");
         pthread_cond_signal(&monitor);
      pthread_mutex_unlock(&monitor);
   }
   pthread_exit(0);
}


int main(int argc, char *argv[])
{
   pthread_t ping;
   pthread_t pong;

   pthread_create (&ping, NULL, Ping, NULL);
   pthread_create (&pong, NULL, Pong, NULL);

   pthread_join(ping, NULL);
   pthread_join(pong, NULL);

   sem_destroy(&red1);
   sem_destroy(&red2);

   return 0;
}