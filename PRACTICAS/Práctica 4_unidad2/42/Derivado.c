#include <string.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <sys/types.h> 
#include <unistd.h> 

#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 

#define LLENADO 0 
#define listo 1 
#define Nolisto -1 

struct memoria { 
	char buff[300]; 
	int estado, primer_pid1, segundo_pid2; 
}; 
struct memoria* shared_memory_seguidor; 
void manejador(int signum) { 
	// Recibimos mensaje
	if (signum == seguidor_dos) { 
		printf("Recibo = "); 
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
	shared_memory_seguidor->segundo_pid2 = pid; 
	shared_memory_seguidor->estado = Nolisto; 

	// usamos la seña para el llamado y la
	// interacción con memoria compartida.
	signal(seguidor_dos, manejador); 

	while (1) { 
		sleep(1); 
		printf("-----Escritura == "); 
		fgets(shared_memory_seguidor->buff, 300, stdin); 

		/*Enviamos la info al otro lado con 
		nuestra función de KILL*/
		shared_memory_seguidor->estado = listo; 
		kill(shared_memory_seguidor->primer_pid1, seguidor_uno); 
		while (shared_memory_seguidor->estado == listo) 
			continue; 
	}shmdt((void*)shared_memory_seguidor); 
	return 0; 
} 
