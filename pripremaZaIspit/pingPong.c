#include <stdio.h>
#include <pthread.h>
//#include <stdlib.h>

void *Ping(void *x)
{
   while(1)
   {
      printf("Ping\n");
   }
}

void *Pong(void *x)
{
   while(1)
   {
      printf("Pong\n");
   }
}


int main(int argc, char *argv[])
{
   pthread_t ping;
   pthread_t pong;

   pthread_create (&thread1, NULL, Ping, NULL);
   //sleep(2);
   pthread_create (&thread1, NULL, Pong, NULL);

   pthread_join(ping, NULL);
   pthread_join(pong, NULL);

   return 0;
}