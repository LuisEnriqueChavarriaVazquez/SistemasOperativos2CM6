#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>

int main(){
   printf("Soy el proceso padre con un solo hijo, mi pid es:%d y mi ppid:%d \n",getpid(),getppid());
   pid_t pid=fork();
   if(pid==-1){
     perror("Error al crear el proceso con 3 hijos \n");
     exit(-1);
   }
   if(pid==0){
    printf("Soy el proceso padre con tres hijos, mi pid es:%d y mi ppdid:%d \n",getpid(),getppid());
      for(int i=0;i<3;i++){
            pid_t pidNivel2=fork();
           if(pidNivel2==-1){
               perror("Error al crear un proceso \n");
               exit(-1); 
            }
            if(pidNivel2==0){
              printf("Soy el proceso %d  padre con dos hijos, mi pid %d y mi ppdid es:%d \n",(i+1),getpid(),getppid());
              for(int j=0;j<2;j++){
                  pid_t pidNivel3=fork();
                  if(pidNivel3==-1){
                    perror("Error al crear un proceso \n");
                    exit(-1);
                    }
                   if(pidNivel3==0){
                    printf("Soy el proceso %d con 0 hijos, mi pid %d y mi ppid es:%d \n",(j+1),getpid(),getppid());
                     sleep(1);
                     exit(0);
                     }
                  wait(NULL);
               }
              // printf("Soy el proceso %d  padre con dos hijos, mi pid %d y mi ppid:%d \n",(i+1),getpid(),getppid());
               sleep(1);
               exit(0);
             }
            wait(NULL);  
         } 
    //  printf("Soy el proceso padre con tres hijos, mi pid es:%d y mi ppdid:%d \n",getpid(),getppid());       
       sleep(1);
       exit(0);
   }
    wait(NULL);
 //   printf("Soy el proceso padre con un solo hijo, mi pid es:%d y mi ppid:%d \n ",getpid(),getppid());

   return 0;
}

