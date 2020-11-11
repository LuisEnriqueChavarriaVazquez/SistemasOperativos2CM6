#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

static int contador=0;
sem_t sem1;
static void * hilo_1_funcion(void *arg);
static void * hilo_2_funcion(void *arg);

int esNumerico(char * c){
 
  if(*c=='0'){
     return 0;
  }

  int valorRegreso=0; 
  
 for(;*c!='\0';c++){
     if(isdigit(*c)==0) {
        valorRegreso=0;
        break;
     }else{
        valorRegreso=1;
    }
  }
   return valorRegreso;
}

int main(int argc, char *argv []){

   long numeroSeg;
   char *p;   
   pthread_t hilo_1;
   pthread_t hilo_2;

   if(argc!=2){

   printf("Numero de parametros incorrectos \n");

   }else{

     if(esNumerico(argv[1])==1){
         numeroSeg=strtol(argv[1],&p,10);          
         sem_init(&sem1,0,1);
         pthread_create(&hilo_1,NULL,*hilo_1_funcion,NULL);
         pthread_create(&hilo_2,NULL,*hilo_2_funcion,NULL); 
       //pthread_join(hilo_1,NULL);
       //pthread_join(hilo_2,NULL); 
           sleep(numeroSeg);
         printf("Contador :%d \n",contador);
      }else{
         printf("Escriba un valor numerico mayor a cero \n");
      }
   }
   return 0;
}


static void * hilo_1_funcion(void * arg){
    
   while(1){
      sem_wait(&sem1);   
      contador++;
      sem_post(&sem1);
   }

}


static void * hilo_2_funcion(void *arg){

   while(1){
    sem_wait(&sem1);
    contador--;
    sem_post(&sem1);
   }
}
