#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>

int main(){
 
  for(int i=0;i<10;i++){   
    pid_t pid =fork();
    if(pid==-1){
      perror("Error al crear el proceso");
      exit(-1);
    }
    if(pid==0){
      printf("Proceso %d -Hola soy el proceso con pid %d y mi padre es %d \n",(i+1),getpid(),getppid());
      sleep(5);     
	 exit(0);
      }
      wait(NULL);
  }

 printf("Soy el proceso padre y tengo el pid %d \n",getpid());
 
  return 0;
}
