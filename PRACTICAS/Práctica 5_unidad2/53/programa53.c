#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

//numero de hilos del proceso hijo
#define MAX_THREADS 3

//nos servira para imprimir los identificadores de los hilos
void Hilo1(void)
{
   printf("\nHilo: %ld\n",pthread_self());
   pthread_exit(0);
}
//dos hilos mas creados por cada uno de los 3 primeros
void Hilo2(void){
   pthread_attr_t atributos;
   pthread_t identificadores[2];
   pthread_attr_init(&atributos);
   pthread_attr_setdetachstate(&atributos,PTHREAD_CREATE_DETACHED);
   for(int k=0;k<2;k++){
     pthread_create(&identificadores[k],&atributos,(void*)Hilo1,NULL);
   		
   }
   sleep(2);
}

int main()
{
  
   pid_t pid;
   pthread_attr_t atributos;
   pthread_t identificadores[MAX_THREADS];
   pthread_attr_init(&atributos);
   pthread_attr_setdetachstate(&atributos,PTHREAD_CREATE_DETACHED);
   
   //se crea el proceso hijo
   pid= fork();
    if(pid==-1)
   {
      perror("\nError al crear el proceso\n");
      exit(-1);
   }
   //si esta creado entonces entra al ciclo
   if(pid==0)
   {
   	   
	   for(int j=0;j<MAX_THREADS;j++)
	   {
	      //se crean 3 hilos a partir de el proceso hijo
	      pthread_create(&identificadores[j],&atributos,(void*)Hilo2,NULL);
	      sleep(2);
	   }
   }

  
   return 0;
}
