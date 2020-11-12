#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>

int main(){

   const char *oracion[5]={"Hola ","esta ","es ","mi ","practica "};
   for(int i=0; i< 5;i++){
      pid_t pid=fork();
      if(pid==-1){
        perror("error creando proceso");
      }
      if(pid==0){
         FILE *fp;
          fp=fopen("Practica33.txt","a+");
          fputs(oracion[i],fp);
          fclose(fp);
//         sleep(1);
         exit(0);
      }
     wait(NULL);
   }

    FILE *fp=fopen("Practica33.txt","a+");
    fputs("uno",fp);
   fclose(fp);
  return 0;
}
