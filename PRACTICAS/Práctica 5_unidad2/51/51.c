#define _GNU_SOURCE

/*USAMOS GNU SOURCE PARA acceder a diversas funciones
que son omitidas en POSIX, del mismo modo si queremos
acceder a funciones de bajo nivel que no son portables
a otro sistema, si buscaramos portabilidad
usariamos _POSIX_C_SOURCE=200809L, pero en este caso no
es necesario.*/

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <string.h>

typedef struct{
    int contador;
    /*Debemos acceder a la parte de la pid
    el identificador de nuestro hilo y a
    los pthreads*/
    pid_t identificador_pid;   
    pid_t identificador_tid;  
    pthread_t ptid;    
} data;

void *foo(void *args){
    data *referencia = (data *) args;

    referencia->ptid = pthread_self();
    referencia->identificador_pid  = getpid();
    referencia->identificador_tid  = syscall(SYS_gettid);
   
    return(referencia);
}

void spawnThreads(unsigned int numeroHilosDefinidos)
{
    int referente;
    pthread_t *identificadores_tids = malloc(sizeof(pthread_t) * numeroHilosDefinidos);

    int contador;

    for (contador = 0; contador < numeroHilosDefinidos; contador++)
    {
        data *referenciaExterna = malloc(sizeof(data) * numeroHilosDefinidos);
        memset(referenciaExterna, '\0', sizeof(*referenciaExterna));

        referenciaExterna->contador = contador;

        referente = pthread_create(&identificadores_tids[contador], NULL, foo, (void *) referenciaExterna);

        if ( referente != 0)
            perror("Error!!!");
    }

    for (int contador = 0; contador < numeroHilosDefinidos; ++contador)
    {
        data *estadoActual;

        referente = pthread_join(identificadores_tids[contador], (void *) &estadoActual);

        if ( referente != 0)
            perror("Error!!");
        else
        {
            printf("______________________________________________________\n"
                    "-------HILO NÚMERO [[%d]]-------\n"
                    "pthreadId del proceso referido a [%lu]\n"
                    "identifcardor [pid] == [%d]\n"
                    "identificador [tid] == [%d]\n",
                   estadoActual->contador, estadoActual->ptid, estadoActual->identificador_pid, estadoActual->identificador_tid);

            free(estadoActual);
        }
    }

    free(identificadores_tids);
}

int main(int argc, char *argv[])
{
    printf("___HILO PRINCIPAL___\n --pthreadId == %lu \n --pid == %d \n --tid == %ld\n"
            "______________________________________________________\n"
            "_________________SIGUIENTES_DOS_HILOS_________________\n\n",
           pthread_self(), getpid(), syscall(SYS_gettid));

    spawnThreads(2);

    return(0);
}
