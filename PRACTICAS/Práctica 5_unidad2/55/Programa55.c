#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

int *p;
int ref;

void *Hilo1(void *argumentos)//Hilo que verifica que el numero ingresado es compuesto
{
  
   int factor = 2;
   p = &ref;
   
   int *parametros=(int*)argumentos;
   printf("\nEstamos en el hilo 1...\n");
   printf("Valor ingresado: %i",*parametros);
  
   if(*parametros%factor==0){
   	printf("\nEl numero se puede descomponer");
   	ref = 0;	 
   }
   else{
   	printf("\nEl numero no se puede descomponer");	
   	ref = 1;
   }

   return (p);
   pthread_exit(NULL);
}

void *Hilo2(void *arr){//Hilo que calcula los factores del numero 

     int *parametros=(int*)arr;
     int factor;
     
     printf("\n-------------------------------------------");
     printf("\nHola!! soy el hilo 2 y tengo el dato [%d] y sus factores son\n",*parametros);
     
     for(factor =2;factor <=*parametros;factor++){
     	while(*parametros%factor==0){
     		printf("%d\t|%d\n",*parametros,factor);
     		*parametros/=factor;
     	}
     }
     pthread_exit(NULL);
}

void *Hilo3(void *arr){//Hilo que muestra el mensaje de ser primo 

     int *parametros=(int*)arr;
     printf("\n-------------------------------------------");
     printf("\nHola!! soy el hilo 3, el numero [%d] es primo\n",*parametros);
     pthread_exit(NULL);
}

int main ()
{
   pthread_t hilo1;
   pthread_t hilo2;
   pthread_t hilo3;
   
   int argumentos[1],arr[1];
   
   printf("Ingrese el numero a descomponer: ");
   scanf("%i",&argumentos[0]);
   
   arr[0] = argumentos[0];
   
   pthread_create(&hilo1,NULL,Hilo1,(void*)argumentos);
   pthread_join(hilo1,NULL);
   printf("\nHilo 1 terminado...");
   
   printf("\nEl valor de referencia es: %d\n",*p);
   
   if(*p==0){
   pthread_create(&hilo2,NULL,Hilo2,(void*)arr);
   pthread_join(hilo2,NULL);
   }
   else {
   pthread_create(&hilo3,NULL,Hilo3,(void*)arr);
   pthread_join(hilo3,NULL);
   }
   
}

