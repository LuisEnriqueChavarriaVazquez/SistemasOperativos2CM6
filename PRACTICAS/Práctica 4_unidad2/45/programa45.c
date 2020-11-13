#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define N 5               //num. de filosofos
#define IZQ (i-1)%N      //vecino izquierdo de i
#define DER (i+1)%N      //vecino derecho de i
#define PENSANDO 0
#define CON_HAMBRE 1
#define COME 2


pthread_t filos[N];       //hilos que representan a los fil�sofos
sem_t mutex ;             //sem�foro para la secci�n cr�tica
sem_t s[N];               //sem�foros para los fil�sofos
int estado [N] ;          //estado actual de cada fil�sosfo


/* 
	el filosofo i va a perder el tiempo... (va a pensar)
 */
void pensar (int i) 
{
  int t ;
  t = rand() % 11;
  printf("Filosofo %d pensando \n", i) ;
  estado[i] = PENSANDO;
  sleep (t) ;
}


/* 
	El filosofo i, va a comer !!!!!!!!
 */
void comer (int i) 
{
  printf("Fil�sofo %d esta comiendo un caballo \n", i);
  estado[i] = COME;
  sleep (5);
}


/* 
	Verifica que pueda tomar ambos tenedores
*/
void verifica(int i) 
{
  if( estado[i]==CON_HAMBRE && estado[IZQ]!=COME && estado[DER]!=COME ){
    estado[i] = COME;
    printf("Fil�sofo %d comiendo\n", i) ;
    sem_post(&s[i]);
  }
}


/* 
	El filosofo i intenta tomar los  tenedores
 */
void toma_tndrs(int i)
{
  
  sem_wait(&mutex);             //entra a la secci�n cr�tica, hace uso del semaforo
  estado[i] = CON_HAMBRE;      //dice: tengo mucha hambre
  verifica(i);                 // verifica que pueda tomar los tenedores
  sem_post(&mutex);            //sale de la secci�n cr�tica y el sem. puede permitir la entrada a alguien m�s
  sem_wait(&s[i]);            //se bloquea si no consigui� los tenedores
}


/* 
	el filosofo i dejar� los tenedores
 */
void deja_tndrs(int i)
{
  
  sem_wait(&mutex);       // de nuevo entra a la secci�n critica
  estado[i] = PENSANDO;  //deja de comer y se pone a pensar
  verifica(IZQ);        
  verifica(DER);
  sem_post(&mutex);
}


/* 


 */
void * filosofos (int i)
{
  int j ;


  for (; ; )
    {
      pensar(i) ;
      toma_tndrs(i) ;
      comer(i) ;
      deja_tndrs(i) ;
    }
}


main()
{
  int i ;


  for(i = 0; i < 5; i++){
    sem_init (&s[i], 0, 1);


    estado[i] = PENSANDO ;
  }


  sem_init (&mutex, 0, 1);

  //creamos un hilo de ejecucion para cada filosofo, que ejecuta filosofos()
  for (i=0; i<N; i++)
    pthread_create(&filos[i], NULL, (void *)filosofos,(void *) i);

  //cada hilo espera a que terminen los dem�s y libera los recursos
  for (i=0; i<N; i++){
    pthread_join(filos[i],NULL);
  }
  
}
