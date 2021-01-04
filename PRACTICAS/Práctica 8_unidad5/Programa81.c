#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


int nombreArchivoValido(char *nombreEntrada){
    char *ptnMovil=nombreEntrada;
    int tamEntrada=strlen(nombreEntrada);
    char const prefijoTxt[5]=".txt";
    int tamPrefijo=strlen(prefijoTxt);    
    return (tamEntrada > tamPrefijo) && (0==strcmp(nombreEntrada+(tamEntrada-tamPrefijo),prefijoTxt));  
}

int nombreDirArchivoValido(char *nombreEntrada){
    char *ptnMovil=nombreEntrada;
    int tamEntrada=strlen(nombreEntrada);
    char const prefijoTxt[5]="/";
    int tamPrefijo=strlen(prefijoTxt);    
    return (tamEntrada > tamPrefijo) && (0==strcmp(nombreEntrada+(tamEntrada-tamPrefijo),prefijoTxt));  
}

void crearArchivo(char *nombreArchivo){
  FILE *fp1;
  char c;
  fp1=fopen(nombreArchivo,"w");
  printf("\n\t Escriba el nombre de texto y presiona '.' para salvarlo \n\n\t");
  while(1){
    scanf("%c",&c);
    fputc(c,fp1);
   if(c=='.'){
     fclose(fp1);
     break;
   }
  }

}

void modificarArchivo(){
	FILE *fp1;
	char fn[20],c;
	printf("Escriba nombre de archivo\n ");
	scanf("%s",fn);
	fflush(stdin);
	fp1=fopen(fn,"r");
	if(fp1==NULL)
	{
	  printf("\nArchivo no encontrado!\n");
	}else{
		while(!feof(fp1))
		{
			c=getc(fp1);
			printf("%c",c);
		}
		fclose(fp1);
		  printf("\n\t Escriba el nombre de texto y presiona '.' para salvarlo \n\n\t");
		  fp1=fopen(fn,"a");
		  while(1){
		    scanf("%c",&c);
		    fputc(c,fp1);
		   if(c=='.'){
		     fclose(fp1);
		     break;
		   }
		  }
	 }
}

void eliminarArchivo(){
 FILE *fp1;
	char fn[20],c;
	printf("Escriba nombre de archivo\n ");
	scanf("%s",fn);
	fflush(stdin);
	fp1=fopen(fn,"r");
	if(fp1==NULL)
	{
	  printf("\nArchivo no encontrado!\n");
	}else{
          remove(fn);
	}

}

int main(){
   int opcUsu=0;
   int opcDirArc=0;
   int salidaUsu=0;
   char nombreArchivo[40];
   int salidaNomArchivo=0;
   int salidaDirArchivo=0;
   int dirArchivoCorrecto=0;
   char dirArchivo[80];
   char archivoNombreFinal[120];
   while(salidaUsu==0){
          salidaNomArchivo=0;
          salidaDirArchivo=0;
          strcpy(nombreArchivo,"");
          strcpy(dirArchivo,"");
          strcpy(archivoNombreFinal,"");
	   printf("\nBienvenido al editor de texto, escriba la opcción que desea hacer:\n");
	   printf("1-Hacer un nuevo archivo de texto\n");
	   printf("2-Editar un archivo de texto ya creado\n");
	   printf("3-Borrar un archivo de texto\n");
	   printf("4-Salir\n");
	   printf("\n");
	   scanf("%d",&opcUsu);
	   switch(opcUsu){
	   case 1:
	      while(salidaNomArchivo==0){
	          printf("Escriba nombre de archivo que desea crear\n");
		  scanf("%s",nombreArchivo);
		  fflush(stdin);
		  if(nombreArchivoValido(nombreArchivo)==1){
		    salidaNomArchivo=1;
		  }else{
		    printf("Escriba nombre de archivo con teminación .txt\n");
		  }
	      }
	      
	      while(salidaDirArchivo==0){
	         printf("Eliga una de las siguientes opcciones\n");
	         printf("1-Hacer un nuevo archivo de texto en el directorio actual\n");
	         printf("2-Hacer un nuevo archivo de texto en el directorio creado terminado como la siguiente forma 'directorio/' \n");
	         scanf("%d",&opcDirArc);
	         switch(opcDirArc){
	            case 1:
	            salidaDirArchivo=1;
	            break;
	            case 2:
	            salidaDirArchivo=1;
	            while(dirArchivoCorrecto==0){
	               printf("Escriba el nombre del directorio \n");
		       scanf("%s",dirArchivo);
		       fflush(stdin);
		       if(nombreDirArchivoValido(dirArchivo)==1){
		    dirArchivoCorrecto=1;
		         strcat(archivoNombreFinal,dirArchivo);
		         mkdir(dirArchivo,0700);
		 	 }else{
		   	printf("Escriba dirección de archivo valido\n");
		  	}
	            }
	            break;
	            default:
	            printf("Escriba una opcción valida\n");
	            break;
	         }
	         strcat(archivoNombreFinal,nombreArchivo);      
	         crearArchivo(archivoNombreFinal);
	      }
	      
	       
	       break;
	   case 2:
	       modificarArchivo();
	      break;
	   case 3:
	      eliminarArchivo();
	      break;
	   case 4:
	      printf("\nAdios\n");
	      salidaUsu=1;
	      break;
	   default:
	     printf("\nEliga una opcción valida\n");
	 
    }
  }
   return 0;
}
