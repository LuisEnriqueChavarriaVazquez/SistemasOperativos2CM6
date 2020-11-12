#include <signal.h>
#include <string.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 

#include <sys/types.h> 
#include <unistd.h>  
#include <stdio.h> 
#include <stdlib.h> 


#define LLENADO 0 
#define Listo 1 
#define Nolisto -1 

struct memoria { 
	char buff[300]; 
	int status, primer_pid1, segundo_pid2; 
}; 
struct memoria* shared_memory_seguidor;
void manejador(int signum) { }
	//Recibimos mensajes.
	if (signum == seguidor_uno) { 
		printf("Recibo derivado =="); 
		puts(shared_memory_seguidor->buff); 
	} 
} 

int main() { 
	/*
		Acceso al identificador del derivado
	*/
	int pid = getpid(); 

	int shared_memory_identificador; 
	/*
		Generamos una llave para nuestro 
		sistema de memoria compartida.

		*Procedemos a  crear la memoria
		compartida.

		*Pegamos la memoria compatida.

	*/
	int llave = 123; 
	shared_memory_identificador = shmget(llave, sizeof(struct memoria), IPC_CREAT | 0666);
	shared_memory_seguidor = (struct memoria*)shmat(shared_memory_identificador, NULL, 0); 

	// Guardamos la ID en la memoria compartida
	// Guardamos el estado en la memoria compartida.
	shared_memory_seguidor->primer_pid1 = pid; 
	shared_memory_seguidor->status = Nolisto; 

	// usamos la seña para el llamado y la
	// interacción con memoria compartida.
	signal(seguidor_uno, manejador); 

	while (1) { 
		while (shared_memory_seguidor->status != Listo) 
			continue; 
		sleep(1); 
		printf("-----Principal== "); 
		fgets(shared_memory_seguidor->buff, 100, stdin); 
		/*Enviamos la info al otro lado con 
		nuestra función de KILL*/
		shared_memory_seguidor->status = LLENADO; 
		kill(shared_memory_seguidor->segundo_pid2, seguidor_dos); 
	} 
	shmdt((void*)shared_memory_seguidor); 
	shmctl(shared_memory_identificador, IPC_RMID, NULL); 
	return 0; 
} 
