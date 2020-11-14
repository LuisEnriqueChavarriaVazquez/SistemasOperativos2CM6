#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<sys/types.h>

//Creamos una región critica para ambos procesos
void regionCritica()
{
   int i;
   printf("\nProceso en la region critica proceso con pid=%d\n",getpid());
   for(i=0;i<3;i++)
   {
      printf("\nRegión critica: %d\n",i);
      sleep(1);	
   }
}
//creamos la region no critica para el proceso 1
void regionNoCritica()
{
   int i;
   printf("\nEn la region NO critica proceso con pid=%d\n",getpid());
   for(i=0;i<5;i++)
   {
      printf("\nContando(%d): %d\n",getpid(),i);
      sleep(1);
   }
}
//creamos la region no critica para el proceso 2
void regionNoCritica2()
{
   int i;
   printf("\nEn la region NO critica proceso con pid=%d\n",getpid());
   for(i=0;i<7;i++)
   {
      printf("\nContando(%d): %d\n",getpid(),i);
      sleep(1);
   }
}

int main()
{
   //identificadores de los dos procesos 
   int PID,PID2;
   
   int shmid1,shmid2,shmid3;
   int *proceso1;
   int *proceso2;
   int *Proceso_favorecido;
   //se crea la memoria compartida para los procesos 
   key_t llave1;
   key_t llave2;
   key_t llave3;
   llave1=ftok("Prueba1",'k');
   llave2=ftok("Prueba2",'l');
   llave3=ftok("Prueba3",'m');
   shmid1=shmget(llave1,sizeof(int),IPC_CREAT|0600);
   shmid2=shmget(llave2,sizeof(int),IPC_CREAT|0600);
   shmid3=shmget(llave3,sizeof(int),IPC_CREAT|0600);
   proceso1=shmat(shmid1,0,0);
   proceso2=shmat(shmid2,0,0);
   Proceso_favorecido=shmat(shmid3,0,0);
   //se inicializan en diferente estado los procesos 
   *proceso1=1;
   *proceso2=0;
   *Proceso_favorecido=1;
   //se codifica el algortimo de dekker
   if(*proceso1==0)
   {
      while (1)
      {
         *proceso1=1;
         while(*proceso2)
         {
            if(*Proceso_favorecido==2)
            {
               *proceso1=0;
               while(*Proceso_favorecido==2);
               *proceso1=1;
            }
         }
         PID=getpid();
         regionCritica(PID);
         *Proceso_favorecido=2;
         *proceso1=0;
         regionNoCritica(PID);
      }
   }
   else
   {
      while(1)
      {
         *proceso2=1;
         while(*proceso1)
         {
            if(*Proceso_favorecido==1)
            {
               *proceso2=0;
               while(*Proceso_favorecido==1);
               *proceso2=1;
            }
         }
         PID2=getpid();
         regionCritica(PID2);
         *Proceso_favorecido=1;
         *proceso2=0;
         regionNoCritica2(PID);
      }
   }
   return 0;
}
