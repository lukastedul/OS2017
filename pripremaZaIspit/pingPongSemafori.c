#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
//#include <stdlib.h> //nez za kaj je to
#include <unistd.h> //to je za sleep

sem_t red1;
sem_t red2;

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
      sem_wait(&red2);
      printf("Pong\n");
      sleep(1);
      sem_post(&red1);
   }
   pthread_exit(0);
}


int main(int argc, char *argv[])
{
   pthread_t ping;
   pthread_t pong;

   sem_init(&red1, 0, 1);
   sem_init(&red2, 0, 0);

   pthread_create (&ping, NULL, Ping, NULL);
   pthread_create (&pong, NULL, Pong, NULL);

   pthread_join(ping, NULL);
   pthread_join(pong, NULL);

   sem_destroy(&red1);
   sem_destroy(&red2);

   return 0;
}