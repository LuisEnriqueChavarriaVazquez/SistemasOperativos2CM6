#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <string.h>
#define SEND_KEY 2
#define RCV_KEY 3

typedef struct msgbuf {
    long tipo_mensaje_evitar_vacios;  
    char mensajito[100];  //Aqui va la info del mensaje.
} MSG_BUF;

    int main(){
        int identificadorMensaje;
        MSG_BUF escritor,lector;
        /*
            Iniciamos las validaciones.
        */
        if((identificadorMensaje=msgget(5,IPC_CREAT |0644))<0)
            perror("error");

        if(fork()==0){
            // el proceso derivado que recibe.
            while(1) {
                if((msgrcv(identificadorMensaje,&lector,sizeof(lector.mensajito),RCV_KEY,0))<0)
                    perror("error");
                printf("Mensaje que te enviaron proceso_2 =  %s\n",lector.mensajito);
            }
        }else{
        // Escribimos en el proceso // PADRE
        /*En esta parte podemos hacer la validación
         e caso de que el mensaje no cumpla
        con las caracteristicas.*/
        while(1){
            escritor.tipo_mensaje_evitar_vacios=SEND_KEY;
            printf("--[P2]Escribe algo\n");

            scanf(" %[^\n]",escritor.mensajito);

            if((msgsnd(identificadorMensaje,&escritor,strlen(escritor.mensajito)+1,0))<0){
                perror("error");
            }
        }
    }return 0;
}


