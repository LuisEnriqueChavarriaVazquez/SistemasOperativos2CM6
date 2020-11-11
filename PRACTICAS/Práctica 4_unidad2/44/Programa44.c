#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<sys/types.h>

#define PERMISOS 0644

//Código para crear un semaforo
int Crea_semaforo(key_t llave,int valor_inicial)
{
   int semid=semget(llave,1,IPC_CREAT|PERMISOS);
   if(semid==-1)
   {
      return -1;
   }
   semctl(semid,0,SETVAL,valor_inicial);
   return semid;
}
//Como se trata de un semaforo binario, se crean los metodos para
//incrementarlo o disminuir su valor
void down(int semid)
{
   struct sembuf op_p[]={0,-1,0};
   semop(semid,op_p,1);
}

void up(int semid)
{
   struct sembuf op_v[]={0,+1,0};
   semop(semid,op_v,1);
}

//Se crea la región critica de los procesos
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
//Se crea la región no critica del primer proceso
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
//Se crea la región no critica del segundo proceso
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
   
   int PID,PID2;
   int proceso1, proceso2;
   int shmid3;
   int *Proceso_favorecido;
   key_t llave1,llave2,llave3;
   //Se crea la memoria compartida para los procesos
   llave1=ftok("Prueba1",'k');
   llave2=ftok("Prueba2",'l');
   llave3=ftok("Prueba3",'m');
   //se crean dos semaforos 1 por proceso
   proceso1=Crea_semaforo(llave1,0);
   proceso2=Crea_semaforo(llave2,0);
   //Se declara el proceso favorecido como apuntador
   shmid3=shmget(llave3,sizeof(int),IPC_CREAT|0600);
   Proceso_favorecido=shmat(shmid3,0,0);
   //Se inicializa el proceso 1 en 1
   up(proceso1);
   *Proceso_favorecido=1;
   //implementación del algoritmo de dekker
   if(proceso1==0)
   {
      while (1)
      {
         up(proceso1);
         while(proceso2)
         {
            if(*Proceso_favorecido==2)
            {
               down(proceso1);
               while(*Proceso_favorecido==2);
               up(proceso1);
            }
         }
         PID=getpid();
         regionCritica(PID);
         *Proceso_favorecido=2;
         down(proceso1);
         regionNoCritica(PID);
      }
   }
   else
   {
      while(1)
      {
         up(proceso2);
         while(proceso1)
         {
            if(*Proceso_favorecido==1)
            {
               down(proceso2);
               while(*Proceso_favorecido==1);
               up(proceso2);
            }
         }
         PID2=getpid();
         regionCritica(PID2);
         *Proceso_favorecido=1;
         down(proceso2);
         regionNoCritica2(PID);
      }
   }
   return 0;
}
