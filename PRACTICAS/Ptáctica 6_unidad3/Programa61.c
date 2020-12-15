#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Direcciones en la MaquinaVirtual-Disco Duro
 char dirDisDur [16][5]={
   {'0','0','0','0', '\0'},
   {'0','0','0','1', '\0'},
   {'0','0','1','0', '\0'},
   {'0','0','1','1', '\0'},
   {'0','1','0','0', '\0'},
   {'0','1','0','1', '\0'},
   {'0','1','1','0', '\0'},
   {'0','1','1','1', '\0'},
   {'1','0','0','0', '\0'},
   {'1','0','0','1', '\0'},
   {'1','0','1','0', '\0'},
   {'1','0','1','1', '\0'},
   {'1','1','0','0', '\0'},
   {'1','1','0','1', '\0'},
   {'1','1','1','0', '\0'},
   {'1','1','1','1', '\0'}
};

//Direcciones en la RAM
char dirMemoriaRAM [8][4]={
    {'0','0','0','\0'},
    {'0','0','1','\0'},
    {'0','1','0','\0'},
    {'0','1','1','\0'},
    {'1','0','0','\0'},
    {'1','0','1','\0'},
    {'1','1','0','\0'},
    {'1','1','1','\0'}   
};

int estadoMemRAM[8]={0,0,0,0,0,0,0,0};
int marcosIniciales[8]={5,4,1,6,7,2,3,0};

//Estructura de un elemento de la Tabla de paginacion
struct nodoTablaPag{
   int numPag;
   int marcoPag;
   int  bitPres;
   struct nodoTablaPag *ptrSig;
};

//Creacion Nodo de la tabla de paginacion
struct nodoTablaPag *crearNodoTabla(int numPagEntrada){
  struct nodoTablaPag *ptrNuevo=(struct nodoTablaPag *) malloc (sizeof(struct nodoTablaPag));
  ptrNuevo->numPag=numPagEntrada;
  ptrNuevo->marcoPag=-1;  
  ptrNuevo->bitPres=0;
  ptrNuevo->ptrSig=NULL;
  return (ptrNuevo);
}

//Ingreso de Nodo de la tabla de paginacion
void pushNodoTabla(struct nodoTablaPag *ptrCab,int numeroEntrada){
  struct nodoTablaPag *ptrNuevo=crearNodoTabla(numeroEntrada);
	struct nodoTablaPag *ptrAnt=ptrCab;
	struct nodoTablaPag *ptrDes=ptrCab->ptrSig;
	int band=0;
	if(ptrCab->ptrSig==NULL){
	   ptrCab->ptrSig=ptrNuevo;
	}else{
		for(;(ptrDes!=NULL) && (ptrNuevo->numPag < ptrDes->numPag);ptrAnt=ptrAnt->ptrSig,ptrDes=ptrDes->ptrSig);
	//	printf("Paso \n");
		 if(ptrDes==NULL){
		 	ptrAnt->ptrSig=ptrNuevo;
		 }else{
		 	ptrAnt->ptrSig=ptrNuevo;
		 	ptrNuevo->ptrSig=ptrDes;
		 }
	    
	}
}

//Sacar elemento de la lista de la tabla de paginacion
int sacarDatoTabla(struct nodoTablaPag *ptrCab, int datoKey){
	struct nodoTablaPag *ptrRec=ptrCab->ptrSig;
	int datoSacar;
	struct nodoTablaPag **ptrRecAnt=&ptrCab;
	for(;ptrRec!=NULL && (ptrRec->numPag!=datoKey);ptrRec=ptrRec->ptrSig,*ptrRecAnt=(*ptrRecAnt)->ptrSig);
	if(ptrRec==NULL){
     	return -1;
	}else{
		(*ptrRecAnt)->ptrSig=ptrRec->ptrSig;
	datoSacar=ptrRec->numPag;
	free(ptrRec);
	return datoSacar;
	}
}

//Consultar datos de la lista de la Tabla de paginacion
int consultarDatoTabla(struct nodoTablaPag *ptrCab, int datoKey){
	struct nodoTablaPag *ptrRec=ptrCab->ptrSig;
	int datoDevolver;
	struct nodoTablaPag **ptrRecAnt=&ptrCab;
	for(;ptrRec!=NULL && (ptrRec->numPag!=datoKey);ptrRec=ptrRec->ptrSig,*ptrRecAnt=(*ptrRecAnt)->ptrSig);
	if(ptrRec==NULL){
		return -1;
	}else{
	datoDevolver=ptrRec->numPag;
	return datoDevolver;
	}
}

//Ver toda la lista de la Tabla de paginacion
void recorrerListaTabla(struct nodoTablaPag *ptrCab){
	struct nodoTablaPag *ptrRec=ptrCab->ptrSig;
	while(ptrRec!=NULL){
		printf("El id num pag:%d, marco Pag:%d ,bitOcu:%d \n",ptrRec->numPag,ptrRec->marcoPag,ptrRec->bitPres);
		ptrRec=ptrRec->ptrSig;
	}
}

//Ver si la lista de Tabla de paginacion esta vacia
int ListaVaciaTabla(struct nodoTablaPag *ptrCab){
	if(ptrCab->ptrSig==NULL)
	  return 1;
	else
	  return 0;
}

//Estructura de un elemento de la Tabla de marcos
struct nodoTablaMar{
   int numMarco;
   int pagMarco;
   struct nodoTablaMar *ptrSig;
};

//Creacion Nodo de la tabla de Marcos
struct nodoTablaMar *crearNodoMarcos(int numMarEntrada){
  struct nodoTablaMar *ptrNuevo=(struct nodoTablaMar *) malloc (sizeof(struct nodoTablaMar)); 
  ptrNuevo->numMarco=numMarEntrada;
  ptrNuevo->pagMarco=-1;  
  ptrNuevo->ptrSig=NULL;
  return (ptrNuevo);
}

//Ingreso de Nodo de la tabla de marcos
void pushNodoMarco(struct nodoTablaMar *ptrCab,int numeroEntrada){
  struct nodoTablaMar *ptrNuevo=crearNodoMarcos(numeroEntrada);
	struct nodoTablaMar *ptrAnt=ptrCab;
	struct nodoTablaMar *ptrDes=ptrCab->ptrSig;
	int band=0;
	if(ptrCab->ptrSig==NULL){
	   ptrCab->ptrSig=ptrNuevo;
	}else{
		for(;(ptrDes!=NULL) && (ptrNuevo->numMarco < ptrDes->numMarco);ptrAnt=ptrAnt->ptrSig,ptrDes=ptrDes->ptrSig);
	//	printf("Paso \n");
		 if(ptrDes==NULL){
		 	ptrAnt->ptrSig=ptrNuevo;
		 }else{
		 	ptrAnt->ptrSig=ptrNuevo;
		 	ptrNuevo->ptrSig=ptrDes;
		 }
	    
	}
}

//Sacar elemento de la lista de la tabla de marcos
int sacarDatoMarcos(struct nodoTablaMar *ptrCab, int datoKey){
	struct nodoTablaMar *ptrRec=ptrCab->ptrSig;
	int datoSacar;
	struct nodoTablaMar **ptrRecAnt=&ptrCab;
	for(;ptrRec!=NULL && (ptrRec->numMarco!=datoKey);ptrRec=ptrRec->ptrSig,*ptrRecAnt=(*ptrRecAnt)->ptrSig);
	if(ptrRec==NULL){
     	return -1;
	}else{
		(*ptrRecAnt)->ptrSig=ptrRec->ptrSig;
	datoSacar=ptrRec->numMarco;
	free(ptrRec);
	return datoSacar;
	}
}

//Consultar datos de la lista de la Tabla de marcos
int consultarDatoMarco(struct nodoTablaMar *ptrCab, int datoKey){
	struct nodoTablaMar *ptrRec=ptrCab->ptrSig;
	int datoDevolver;
	struct nodoTablaMar **ptrRecAnt=&ptrCab;
	for(;ptrRec!=NULL && (ptrRec->numMarco!=datoKey);ptrRec=ptrRec->ptrSig,*ptrRecAnt=(*ptrRecAnt)->ptrSig);
	if(ptrRec==NULL){
		return -1;
	}else{
	datoDevolver=ptrRec->numMarco;
	return datoDevolver;
	}
}


//Ver toda la lista de la Tabla de marcos
void recorrerListaMarcos(struct nodoTablaMar *ptrCab){
	struct nodoTablaMar *ptrRec=ptrCab->ptrSig;
	while(ptrRec!=NULL){
		printf("El id num marco:%d, pag marco:%d \n",ptrRec->numMarco,ptrRec->pagMarco);
		ptrRec=ptrRec->ptrSig;
	}
}

//Ver si la lista de Tabla de marcos esta vacia
int ListaVaciaMarcos(struct nodoTablaMar *ptrCab){
	if(ptrCab->ptrSig==NULL)
	  return 1;
	else
	  return 0;
}

//Cola de metodo de fallo de pagina FIFO
struct nodoCola {
   int datoPag;
   struct nodoCola *ptrSig;
};

//Crear nodo de cola
struct nodoCola * crearNodoCola(int dato){
	struct nodoCola *ptrNuevo=(struct nodoCola *) malloc(sizeof(struct nodoCola));
	 ptrNuevo->datoPag=dato;
     ptrNuevo->ptrSig=NULL;
     return (ptrNuevo);
}

//Push de nodo de cola
void pushNodoCola(struct nodoCola *ptrEnt,int datoEnt){
	struct nodoCola *ptrNuevo=crearNodoCola(datoEnt);
	if(ptrEnt->ptrSig==NULL)
	   ptrEnt->ptrSig=ptrNuevo;
	else{
	   struct nodoCola *ptrRec=ptrEnt->ptrSig;
	   while(ptrRec->ptrSig!=NULL){
	   	  ptrRec=ptrRec->ptrSig;
	   }
	   ptrRec->ptrSig=ptrNuevo;
	}
}

//Pop de nodo Cola
int popNodoCola(struct nodoCola *ptrEnt){
	struct nodoCola *ptrRef=ptrEnt->ptrSig;
	int datoSal=ptrRef->datoPag;
	ptrEnt->ptrSig=ptrRef->ptrSig;
	free(ptrRef);
	return(datoSal);
}

//checar si la cola esta vacia
int colaVacia(struct nodoCola *ptrEnt){
	if(ptrEnt->ptrSig==NULL)
	  return 1;
	else 
	   return 0;
}

//Recorre cola
void recorrerCola(struct nodoCola *ptrEnt){
	struct nodoCola *ptrRec=ptrEnt->ptrSig;
    while(ptrRec!=NULL){
    	printf("Dato Cola:%d \n",ptrRec->datoPag);
    	ptrRec=ptrRec->ptrSig;
	}
}

//Metodo para insertar en la tabla de paginacion un marco
void meterMarcoEnPag(struct nodoTablaPag *ptrCab,int entradaNumPag, int entradaNumMarco){
    struct nodoTablaPag *ptrRec=ptrCab->ptrSig;
    while(ptrRec!=NULL){
        if(ptrRec->numPag==entradaNumPag){
           ptrRec->marcoPag=entradaNumMarco;
           ptrRec->bitPres=1;
           break;
        }
        ptrRec=ptrRec->ptrSig;
    }
}

//Metodo para sacar en la tabla de paginacion un marco
void sacarMarcoEnPag(struct nodoTablaPag *ptrCab,int entradaNumPag){
    struct nodoTablaPag *ptrRec=ptrCab->ptrSig;
    while(ptrRec!=NULL){
        if(ptrRec->numPag==entradaNumPag){
           ptrRec->marcoPag=-1;
           ptrRec->bitPres=0;
           break;
        }
        ptrRec=ptrRec->ptrSig;
    }
}

//Metodo para insertar en la tabla de marcos una pagina
void meterPagEnMarco(struct nodoTablaMar *ptrCab,int entradaNumMarco, int entradaNumPag){
    struct nodoTablaMar *ptrRec=ptrCab->ptrSig;
    while(ptrRec!=NULL){
        if(ptrRec->numMarco==entradaNumMarco){
           ptrRec->pagMarco=entradaNumPag;
           break;
        }
        ptrRec=ptrRec->ptrSig;
    }
}

//Metodo para sacar en la tabla de marcos una pagina
void sacarPagEnMarco(struct nodoTablaMar *ptrCab,int entradaNumMarco){
    struct nodoTablaMar *ptrRec=ptrCab->ptrSig;
    while(ptrRec!=NULL){
        if(ptrRec->numMarco==entradaNumMarco){
           ptrRec->pagMarco=-1;
           break;
        }
        ptrRec=ptrRec->ptrSig;
    }
}


//Mostrar tabla Paginacion

void mostrarTablaPag(struct nodoTablaPag *ptrCab){
      struct nodoTablaPag *ptrRec=ptrCab->ptrSig;
      printf("\n\n        Tabla de paginacion \n");
      int contador=0;
        while(ptrRec!=NULL){
         if(contador<10){
             if(ptrRec->marcoPag!=-1){
                 printf("    ------------------------------------------------------ \n");
             }else{
               printf("    ------------------------------------------------------- \n");
             }
        }else{
            if(ptrRec->marcoPag!=-1){
                   printf("    ------------------------------------------------------ \n");
            }else{
                 printf("    ------------------------------------------------------- \n");
            }
       
        }
               
                printf("    | ID Pag = %d | marco actual de la pag = %d | bitOcu=%d | \n",ptrRec->numPag,ptrRec->marcoPag,ptrRec->bitPres);
          if(contador<10){
             if(ptrRec->marcoPag!=-1){
                 printf("    ------------------------------------------------------ \n");
             }else{
               printf("    ------------------------------------------------------- \n");
             }
        }else{
            if(ptrRec->marcoPag!=-1){
                   printf("    ------------------------------------------------------ \n");
            }else{
                 printf("    ------------------------------------------------------- \n");
            }
       
        }
               ptrRec=ptrRec->ptrSig;
               contador++;
        }
        
        printf("\n \n \n");

}

//Mostrar tabla de marcos

void mostrarTablaMarcos(struct nodoTablaMar *ptrCab){
      struct nodoTablaMar *ptrRec=ptrCab->ptrSig;
      printf("\n\n        Tabla de marcos \n");
      
        while(ptrRec!=NULL){
      
                if(ptrRec->pagMarco!=-1){
                   printf("    -------------------------------------------\n");
                }else{
                   printf("    --------------------------------------------\n");
                }
                printf("    | ID Marco = %d | pag actual del marco = %d |  \n",ptrRec->numMarco,ptrRec->pagMarco);
          
               if(ptrRec->pagMarco!=-1){
                   printf("    -------------------------------------------\n");
                }else{
                   printf("    --------------------------------------------\n");
                }
               ptrRec=ptrRec->ptrSig;
              
        }
        printf("\n \n \n");

}

//Mostrar tabla general
void mostrarEstadoGeneral(struct nodoTablaPag *ptrCabPag,struct nodoTablaMar *ptrCabMar){
    struct nodoTablaPag *ptrRecPag=ptrCabPag->ptrSig;
    struct nodoTablaMar *ptrRecMac=ptrCabMar->ptrSig;

        printf("         Tabla de paginacion                  Tabla de marcos\n");
        printf("    ----------------------------");
        printf("             ");
        printf("------------------ \n");
        printf("    | Pagina || Marco || bitOc |");
        printf("             ");
        printf("| Marco | Pagina |\n");
        printf("    ----------------------------");
        printf("             ");
        printf("------------------ \n");
         
        while(ptrRecPag!=NULL){
        
         printf("    ----------------------------");
         if(ptrRecMac!=NULL){
             printf("             ");
             printf("------------------");
         }
         printf("\n");
         printf("    |  %s  |",dirDisDur[ptrRecPag->numPag]);
         if(ptrRecPag->marcoPag!=-1){
           printf("|  %s  |",dirMemoriaRAM[ptrRecPag->marcoPag]);
         }else{
           printf("|  xxx  |");
         }
         printf("|   %d   |",ptrRecPag->bitPres);
         if(ptrRecMac!=NULL){
             printf("             ");
             printf("|  %s  |  %s  |",dirMemoriaRAM[ptrRecMac->numMarco],dirDisDur[ptrRecMac->pagMarco]);
         
         } 
         printf("\n");
       printf("    ----------------------------");
         if(ptrRecMac!=NULL){
             printf("             ");
             printf("------------------");
         }
           printf("\n");
           if(ptrRecMac!=NULL){
             ptrRecMac=ptrRecMac->ptrSig;
           }
            ptrRecPag=ptrRecPag->ptrSig;
        
        }
    printf("\n \n");
}

//metodo para checar RAM llena
/*int llenaRAM(struct nodoTablaMar *ptrCab){
  struct nodoTablaMar *ptrRec=ptrCab->ptrSig;
  int llena=0;
  int contadorMarcosTomados=0;
   while(ptrRec!=NULL){
       if(ptrRec->pagMarco!=-1){
          contadorMarcosTomados++;
       }
       ptrRec=ptrRec->ptrSig;
   }
   if(contadorMarcosTomados==8){
      llena=1;
   }
   return llena;
}*/

//MEtod para ver si pagina esta en memoria RAM
int pagEnMemoriaRAM(struct nodoTablaPag *ptrCabPag,int paginaEnt){
     struct nodoTablaPag *ptrRecPag=ptrCabPag->ptrSig;
     int exixtenciaMemoria=0;
     while(ptrRecPag!=NULL){
        if(ptrRecPag->numPag==paginaEnt){
           if(ptrRecPag->bitPres==1){
               exixtenciaMemoria=1;
           }
        }
        ptrRecPag=ptrRecPag->ptrSig;
     }
     return exixtenciaMemoria;
}

//Metodo buscar Marco con una pagina en especial
int  buscarMarco(struct nodoTablaMar *ptrCab,int numPagEntrada){
    struct nodoTablaMar *ptrRec=ptrCab->ptrSig;
    int numeroMarcoSalida=-1;
	while(ptrRec!=NULL){
		if(ptrRec->pagMarco==numPagEntrada){
		   numeroMarcoSalida=ptrRec->numMarco;
		   break;
		}
		ptrRec=ptrRec->ptrSig;
	}
    return numeroMarcoSalida;
}

//Transformacion memoria disco a RAM

void transformacionMemoria(int numeroPagina,int numeroMarco){
   int c,k;
   int contador;
   char numeroBase[13];
   printf("\n \n");
   for (int i=0;i<4096;i++){
       contador=0;
       for(c=11;c >= 0; c--){
          k= i >> c;
          if( k& 1){
             numeroBase[contador]='1';
          }else{
             numeroBase[contador]='0';
          }
          contador++;
       }
       contador++;
       numeroBase[contador]='\0';
       printf("Direccion Disco=%s%s ----->Direccion Ram=%s%s \n",dirDisDur [numeroPagina],numeroBase,dirMemoriaRAM [numeroMarco],numeroBase);
   }
   printf("\n \n");
}

//Metodo para mover una pagina seleccionada por el usuario
void usuarioMoverPagina(struct nodoTablaPag *ptrCabPag,struct nodoTablaMar *ptrCabMar,struct nodoCola *ptrCola,int entraNumPagMover){
  /* if(llenaRAM(ptrCabMar)){
     int pagSalir=popNodoCola(ptrCola);
     int marcoLLenar=buscarMarco(ptrCabMar,pagSalir);
     sacarMarcoEnPag(ptrCabPag,pagSalir);
     sacarMarcoEnPag(ptrCabPag,entraNumPagMover);
     meterPagEnMarco(ptrCabMar,marcoLLenar,entraNumPagMover);
      meterMarcoEnPag(ptrCabPag,entraNumPagMover,marcoLLenar);
      int marcoPosibleVacia=buscarMarco(ptrCabMar,entraNumPagMover);
      sacarPagEnMarco(ptrCabMar,marcoPosibleVacia);
      
     pushNodoCola(ptrCola,entraNumPagMover);
     printf("\n Actualizacion tabla de paginacion \n");
     mostrarTablaPag(ptrCabPag);
     printf("\n Actualizacion tabla de marcos \n");
     mostrarTablaMarcos(ptrCabMar);
   }else{
   
   }*/
     if(pagEnMemoriaRAM(ptrCabPag,entraNumPagMover)==0){
         int pagSalir=popNodoCola(ptrCola);
         int marcoLLenar=buscarMarco(ptrCabMar,pagSalir);
         sacarMarcoEnPag(ptrCabPag,pagSalir);
         meterPagEnMarco(ptrCabMar,marcoLLenar,entraNumPagMover);
         meterMarcoEnPag(ptrCabPag,entraNumPagMover,marcoLLenar);
          pushNodoCola(ptrCola,entraNumPagMover);
          printf("Se mueve la pagina: %d al marco:%d por el metodo de fallo de pagina FIFO\n",entraNumPagMover,marcoLLenar);
          transformacionMemoria(entraNumPagMover,marcoLLenar);
          printf("\nEstado de las memorias actualizado\n\n ");
          mostrarEstadoGeneral(ptrCabPag,ptrCabMar);
         
     }else{
       printf("La pagina ya esta en la RAM \n");
     }
   
  
}

int main(){
 struct nodoTablaPag *ptrCabPaginas=crearNodoTabla(-1);
 struct nodoTablaMar *ptrCabMarcos=crearNodoMarcos(-1);
 struct nodoCola *ptrPrimeroCola=crearNodoCola(-1);
 for(int i=0;i<16;i++){
    pushNodoTabla(ptrCabPaginas,i); 
 } 
 for (int i=0;i<8;i++){
     pushNodoMarco(ptrCabMarcos,i);
 }

 
 for(int i=0;i<8;i++){
     meterMarcoEnPag(ptrCabPaginas,i,marcosIniciales[i]);
     meterPagEnMarco(ptrCabMarcos,marcosIniciales[i],i);
     pushNodoCola(ptrPrimeroCola,i);
 }

printf("Bienvenido al simulador de memoria virtual \n \n");
printf("La RAM es de 32 KB, el disco duro es de 64 KB y las paginas son de 4 kB \n \n");
printf("Este es el estado de tabla de paginacion y de marcos en este momento \n\n");
//mostrarTablaPag(ptrCabPaginas);
//mostrarTablaMarcos(ptrCabMarcos);
mostrarEstadoGeneral(ptrCabPaginas,ptrCabMarcos);
// recorrerListaTabla(ptrCabPaginas);
 //popNodoCola(ptrPrimeroCola);
// recorrerCola(ptrPrimeroCola);
int estadoSalida=0;
int numeroPagUsuario=0;
int opccion=0;
while(estadoSalida==0){
    printf("Escriba que opccion quiere elegir:\n");
    printf("1-Mover una pagina\n");
    printf("2-Salir de programa\n \n");
    scanf("%d",&opccion);
    if(opccion==1){
       printf("\nEscriba una pagina de entre 0 a 15 que quiera mover \n \n ");
       scanf("%d",&numeroPagUsuario);
       if(numeroPagUsuario>=0){
            if(numeroPagUsuario<16){
                usuarioMoverPagina(ptrCabPaginas,ptrCabMarcos,ptrPrimeroCola,numeroPagUsuario);
                //recorrerCola(ptrPrimeroCola);
            }else{
               printf("\nEscriba un numero de pagina valido \n \n");
            }
       }else{
         printf("\nEscriba un numero de pagina valido \n \n");
       }
    }else{
        if(opccion==2){
           printf("Adios\n");
           estadoSalida=1;
        }else{
        
             printf("\nEscriba una opccion valida \n \n");
        }
    
    }
   
}
 return 0;
}
