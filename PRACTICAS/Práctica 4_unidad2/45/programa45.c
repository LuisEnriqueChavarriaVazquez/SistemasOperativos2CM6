#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define N 5               //num. de filosofos
#define IZQ (i-1)%N      //vecino izquierdo de i
#define DER (i+1)%N      //vecino derecho de i
#define PENSANDO 0
#define CON_HAMBRE 1
#define COME 2


pthread_t filos[N];       //hilos que representan a los filósofos
sem_t mutex ;             //semáforo para la sección crítica
sem_t s[N];               //semáforos para los filósofos
int estado [N] ;          //estado actual de cada filósosfo


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
  printf("Filósofo %d esta comiendo un caballo \n", i);
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
    printf("Filósofo %d comiendo\n", i) ;
    sem_post(&s[i]);
  }
}


/* 
	El filosofo i intenta tomar los  tenedores
 */
void toma_tndrs(int i)
{
  
  sem_wait(&mutex);             //entra a la sección crítica, hace uso del semaforo
  estado[i] = CON_HAMBRE;      //dice: tengo mucha hambre
  verifica(i);                 // verifica que pueda tomar los tenedores
  sem_post(&mutex);            //sale de la sección crítica y el sem. puede permitir la entrada a alguien más
  sem_wait(&s[i]);            //se bloquea si no consiguió los tenedores
}


/* 
	el filosofo i dejará los tenedores
 */
void deja_tndrs(int i)
{
  
  sem_wait(&mutex);       // de nuevo entra a la sección critica
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

  //cada hilo espera a que terminen los demás y libera los recursos
  for (i=0; i<N; i++){
    pthread_join(filos[i],NULL);
  }
  
}
