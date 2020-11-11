#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

//se define la variable global en 0
int N=0;

//el primer hilo hace un incremento a la variable global
void *Hilo1(void *argumentos)
{
   N=N+5;
   pthread_exit(NULL);
}
//el segundo hilo hace un decremento a la variable global
void *Hilo2(void *argumentos)
{
   N=N-2;
   pthread_exit(NULL);
}
int main ()
{
   pthread_t id_hilo1, id_hilo2;
   printf("\nCreacion del hilo 1\n");
   //se hace primero el incremento de 5
   pthread_create(&id_hilo1,NULL,Hilo1,NULL);
   sleep(2);
   printf("\nCreacion del hilo 2\n");
   //se hace el decremento de 2
   pthread_create(&id_hilo2,NULL,Hilo2,NULL);
   sleep(2);
  
   printf("\nHilos esperando su finalizacion...\n");
   pthread_join(id_hilo1,NULL);
   pthread_join(id_hilo2,NULL);
   printf("\nHilos finalizados\n");
   //se imprime el resultado de la operacion de los hilos
   //si todo es correcto se deberia mostrar 3
   printf("Valor de la variable global: %d \n",N);
   
   return 0;
}
