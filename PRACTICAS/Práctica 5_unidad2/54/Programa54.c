#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int *p;
int *q;
int konta=0;
int cont=0;

void *Codigo_Hilo1(void *arg)//Hilo 1 que busca una cadena en un archivo dado
{

FILE *Fd;

      char palabra[30],texto[80];
      char fitxizen[]="//home//victor//Documentos//Pràcticas//Prueba.txt";

      int i,tmp1,tmp2;
       p = &konta;
	
      printf("\t----------------Hola!!!, soy el hilo 1----------------\n");	
      printf("Ingrese la palabra a buscar en el fichero: \n");
      fgets(palabra,30,stdin);
	//home/victor/Documentos/Pràcticas/Prueba.txt

      Fd=fopen(fitxizen, "r");

      if (Fd==NULL)
         printf("Error abriendo el fichero");

      while (feof(Fd)==0)
      {
            fgets(texto,80,Fd);

            for(i=0;i<strlen(texto);i++)
            {
               if (palabra[0]==texto[i])
               {
                  tmp1=0;

                  tmp2=i;

                  while ((palabra[tmp1]==texto[tmp2])&&(tmp2<strlen(texto))&&(tmp1!=strlen(palabra)))
                  {
                        tmp1++;
                        tmp2++;

                        if (tmp1==strlen(palabra))
                           konta++;
                  }
               }
            }
      }

      printf("La palabra se repite en el texto %d veces\n",konta);
      printf("Pulse Enter para continuar...\n");
      getchar();

     fclose(Fd);
     
     return(p);
   
   pthread_exit(NULL);
}

void *Codigo_Hilo2(void *arg)//Hilo 2 que copia archivos de un directorio a otro 
{
   int i;
   q = &cont;
   
   printf("\n\t----------------Hola!!!, soy el hilo 2----------------\n");
   printf("Copiando archivos del directorio...");
   
   system("cp //home//victor//Documentos//Pràcticas//filosofos.c //home//victor//Documentos");cont++;
      system("cp //home//victor//Documentos//Pràcticas//filosofos //home//victor//Documentos");cont++;
         system("cp //home//victor//Documentos//Pràcticas//Programa54.c //home//victor//Documentos");cont++;
            system("cp //home//victor//Documentos//Pràcticas//Programa54 //home//victor//Documentos");cont++;
               system("cp //home//victor//Documentos//Pràcticas//Programa55.c //home//victor//Documentos");cont++;
                  system("cp //home//victor//Documentos//Pràcticas//Programa55 //home//victor//Documentos");cont++;	
   
   
   printf("\nArchivos copiados\n\n");
   
   return(q);
   
   pthread_exit(NULL);
}

void *Codigo_Hilo3(void *argumentos)//Hilo 3 Crea el reporte con los resultados del hilo 1 y 2 
{
   int *datos = (int*)argumentos;
   FILE *Fd;
   
   printf("\n\n\t----------------Hola!!!, soy el hilo 3----------------\n");

	Fd=fopen("//home//victor//Documentos//Pràcticas//ResultadosPrograma54.txt", "w");
 
 	if(Fd==NULL){
 	      printf("\nError en la creacion del archivo");
 	}
 	else{
 	      printf("\nReporte creado exitosamente, revise el directorio\n\n");
 	}	
 
	fprintf(Fd,"\t***************Resultados del programa 54***************\n");
	fprintf(Fd,"\nEl numero de concurrencias del hilo 1 es: %d\n",*datos);
	fprintf(Fd,"\nEl numero de elementos copiados del hilo 2 es: %d\n",*(datos+1));
 

	fclose(Fd);
   
   pthread_exit(NULL);
}



int main()
{
   pthread_t hilo1;
   pthread_t hilo2;
   pthread_t hilo3;
   int argumentos[2];
   
   pthread_create(&hilo1,NULL,Codigo_Hilo1,NULL);
   pthread_join(hilo1,NULL);
   printf("\t****************Hilo numero 1 terminado-****************\n");
   printf("El valor retornado por el hilo 1 fue: %d\n\n",*p);
   
   pthread_create(&hilo2,NULL,Codigo_Hilo2,NULL);
   pthread_join(hilo2,NULL);
   printf("\t****************Hilo numero 2 terminado****************\n");
   
   argumentos[0] = *p;
   argumentos[1] = *q;
   pthread_create(&hilo3,NULL,Codigo_Hilo3,(void*)argumentos);
   pthread_join(hilo3,NULL);
   printf("\t****************Hilo numero 3 terminado****************\n");
   
   printf("\nFinalizando el hilo principal\n");
   pthread_exit(NULL);
}
