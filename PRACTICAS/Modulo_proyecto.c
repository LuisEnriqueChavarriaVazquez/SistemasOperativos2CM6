/*Modulo del paciente, permite añadir un nuevo paciente, borrar alguno ya registrado, visualizar los datos almacenados en el sistema, respaldar los registros en un archivo txt, realizar la busqueda en especifico y la actualizacion de datos de algun paciente*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 30
#define m 5

void nuevoPaciente (char nombre[], char apellidopat[], char apellidomat[], char edad[], char peso[], char altura[], char alergia[], char enfermedad[], char descripcion[], char consultas[], char historial[]);
void registros(char nombre[], char apellidopat[], char apellidomat[], char edad[], char peso[], char altura[], char alergia[], char enfermedad[], char descripcion[], char consultas[], char historial[]);
void buscarpaciNombre(char nom[]);
void eliminarPacienteNombre(char nom[]);
void actualizarPaciNombre(char nom[]);

struct persona{			//estructura que contiene los datos
	char nombre[N];
	char apellidopat[N];
	char apellidomat[N];
	char edad[m];
	char peso[m];
	char altura[m];
	char alergia[N];
	char enfermedad[N];
	char descripcion[N];
	char consultas[N];
	char historial[N];
	
};

struct nodo{	
	struct persona reg;			//de esta forma seran los nodo
	struct nodo *ptrsig;
};

struct nodo *ptrC=NULL;
struct nodo *ptrF=NULL;

void imprimirSeparador() { printf("=================================\n"); }

void nuevonodo(){
	char c;
	struct nodo *ptrnuevo;
	ptrnuevo=(struct nodo*)malloc(sizeof(struct nodo));
	
	imprimirSeparador();
 
	printf("Nuevo Paciente\n");
	printf("==============\n");
	
	scanf("%c",&c);
	printf("Ingrese el nombre(s):");
	fgets(ptrnuevo->reg.nombre,N,stdin);
	fflush(stdin);
	
	
	printf("Ingrese el apellido paterno:");
	fgets(ptrnuevo->reg.apellidopat,N,stdin);
	fflush(stdin);
	
	printf("Ingrese el apellido materno:");
	fgets(ptrnuevo->reg.apellidomat,N,stdin);
	fflush(stdin);
	
	printf("Ingrese la edad:");
	fgets(ptrnuevo->reg.edad,m,stdin);
	fflush(stdin);
	
	printf("Ingrese el peso:");
	fgets(ptrnuevo->reg.peso,m,stdin);
	fflush(stdin);
	
	printf("Ingrese la altura:");
	fgets(ptrnuevo->reg.altura,m,stdin);
	fflush(stdin);
	
	scanf("%c",&c);
	printf("Ingrese alergia del paciente:");
	fgets(ptrnuevo->reg.alergia,N,stdin);
	fflush(stdin);
	
	printf("Ingrese el padecimiento:");
	fgets(ptrnuevo->reg.enfermedad,N,stdin);
	fflush(stdin);
	
	printf("Ingrese una descripcion:");
	fgets(ptrnuevo->reg.descripcion,N,stdin);
	fflush(stdin);
	
	printf("Ingrese la periodicidad del tratamiento:");
	fgets(ptrnuevo->reg.consultas,N,stdin);
	fflush(stdin);
	
	printf("Ingrese el historial clinico:");
	fgets(ptrnuevo->reg.historial,N,stdin);
	fflush(stdin);
	
	imprimirSeparador();
	
 	nuevoPaciente(ptrnuevo->reg.nombre, ptrnuevo->reg.apellidopat, ptrnuevo->reg.apellidomat, ptrnuevo->reg.edad, ptrnuevo->reg.peso, ptrnuevo->reg.altura, ptrnuevo->reg.alergia, ptrnuevo->reg.enfermedad, ptrnuevo->reg.descripcion, ptrnuevo->reg.consultas, ptrnuevo->reg.historial);
 	
 	registros(ptrnuevo->reg.nombre, ptrnuevo->reg.apellidopat, ptrnuevo->reg.apellidomat, ptrnuevo->reg.edad, ptrnuevo->reg.peso, ptrnuevo->reg.altura, ptrnuevo->reg.alergia, ptrnuevo->reg.enfermedad, ptrnuevo->reg.descripcion, ptrnuevo->reg.consultas, ptrnuevo->reg.historial);
 
	free(ptrnuevo);
}

void nuevoPaciente (char nombre[], char apellidopat[], char apellidomat[], char edad[], char peso[], char altura[], char alergia[], char enfermedad[], char descripcion[], char consultas[], char historial[]){
	struct nodo *ptraux;
	struct nodo *nuevopaci;
	nuevopaci=(struct nodo*)malloc(sizeof(struct nodo));
	ptraux=ptrC;
	
	while(ptraux != NULL) {
			if((strcmp(ptraux->reg.nombre, nombre)) == 0){
				printf("El nombre de paciente ingresado ya existe.\n");
				return;
			}
			else{
				ptraux=ptraux->ptrsig;
			}
	}
	if(ptraux == NULL){
		strcpy(nuevopaci->reg.nombre, nombre);
	} 
//**********************	
	
	strcpy(nuevopaci->reg.apellidopat, apellidopat);
//**********************	
	
	strcpy(nuevopaci->reg.apellidomat, apellidomat);
//**********************	
	strcpy(nuevopaci->reg.edad, edad);
//**********************	
	strcpy(nuevopaci->reg.peso, peso);
//**********************	
	strcpy(nuevopaci->reg.altura, altura);
//**********************	
	strcpy(nuevopaci->reg.alergia, alergia);
//**********************	
	strcpy(nuevopaci->reg.enfermedad, enfermedad);
//**********************		
	strcpy(nuevopaci->reg.descripcion, descripcion);	
//**********************		
	strcpy(nuevopaci->reg.consultas, consultas);	
//**********************		
	strcpy(nuevopaci->reg.historial, historial);	
	
		
	nuevopaci->ptrsig = NULL;
//**********************************************************************
 
	if(ptrC == NULL){ 
		ptrC = nuevopaci;
	}
	else{
        ptrF->ptrsig = nuevopaci;
	}
 
    ptrF = nuevopaci;
    printf("La informacion del paciente ha sido guardada exitosamente.\n"); 
 
	
}

void imprimir(){ 
 
	struct nodo *ptrAux;
	int TAM;//TAM = cantidad de contactos
 
	imprimirSeparador();
 
/**********************************************************************/
 
	ptrAux = ptrC;
 
	TAM = 0;
	while(ptrAux != NULL) {
		ptrAux = ptrAux->ptrsig;
		TAM++;
	}
 
/**********************************************************************/
	//Ordenamiento de burbuja: ordena alfabéticamente los contactos
	if(ptrC != NULL){
		struct nodo *primero = NULL, *segundo = NULL, *aux = NULL;
 
		primero = ptrC;
		while(primero != ptrF){
			segundo = primero->ptrsig;
			while(segundo != NULL){
				if(strcmp(segundo->reg.nombre, segundo->reg.nombre) > 0){	
					strcpy(aux->reg.nombre, primero->reg.nombre);						
					strcpy(aux->reg.apellidopat, primero->reg.apellidopat);
					strcpy(aux->reg.apellidomat, primero->reg.apellidomat);
					strcpy(aux->reg.edad, primero->reg.edad);
					strcpy(aux->reg.peso, primero->reg.peso);
					strcpy(aux->reg.altura, primero->reg.altura);
					strcpy(aux->reg.alergia, primero->reg.alergia);
					strcpy(aux->reg.enfermedad, primero->reg.enfermedad);
					strcpy(aux->reg.descripcion, primero->reg.descripcion);
					strcpy(aux->reg.consultas, primero->reg.consultas);
					strcpy(aux->reg.historial, primero->reg.historial);
 
					strcpy(primero->reg.nombre, segundo->reg.nombre);						
					strcpy(primero->reg.apellidopat, segundo->reg.apellidopat);
					strcpy(primero->reg.apellidomat, segundo->reg.apellidomat);
					strcpy(primero->reg.edad, segundo->reg.edad);
					strcpy(primero->reg.peso, segundo->reg.peso);
					strcpy(primero->reg.altura, segundo->reg.altura);
					strcpy(primero->reg.alergia, segundo->reg.alergia);
					strcpy(primero->reg.enfermedad, segundo->reg.enfermedad);
					strcpy(primero->reg.descripcion, primero->reg.descripcion);
					strcpy(primero->reg.consultas, segundo->reg.consultas);
					strcpy(primero->reg.historial, segundo->reg.historial);
 
				
 					strcpy(segundo->reg.nombre, aux->reg.nombre);						
					strcpy(segundo->reg.apellidopat, aux->reg.apellidopat);
					strcpy(segundo->reg.apellidomat, aux->reg.apellidomat);
					strcpy(segundo->reg.edad, aux->reg.edad);
					strcpy(segundo->reg.peso, aux->reg.peso);
					strcpy(segundo->reg.altura, aux->reg.altura);
					strcpy(segundo->reg.alergia, aux->reg.alergia);
					strcpy(segundo->reg.enfermedad, aux->reg.enfermedad);
					strcpy(segundo->reg.descripcion, aux->reg.descripcion);
					strcpy(segundo->reg.consultas, aux->reg.consultas);
					strcpy(segundo->reg.historial, aux->reg.historial);
 
				}
 
				segundo = segundo->ptrsig;
			}
 
			primero= primero->ptrsig;
		}
	}
 
/**********************************************************************/
 
	ptrAux = ptrC;
 
	printf("Pacientes\n");
 
	while(ptrAux != NULL) {
		printf("=========\n");
		printf("Nombre: %s\n",ptrAux->reg.nombre);
		printf("Apellido paterno: %s\n",ptrAux->reg.apellidopat);
		printf("Apellido materno: %s\n",ptrAux->reg.apellidomat);
		printf("Edad: %s\n",ptrAux->reg.edad);
		printf("Peso: %s\n",ptrAux->reg.peso);
		printf("Altura: %s\n",ptrAux->reg.altura);
		printf("Alergias: %s\n",ptrAux->reg.alergia);
		printf("Padecimiento: %s\n",ptrAux->reg.enfermedad);
		printf("Descripcion del tratamiento requerido: %s\n",ptrAux->reg.descripcion);
		printf("Periodicidad de visita: %s\n",ptrAux->reg.consultas);
		printf("Historial clinico: %s\n",ptrAux->reg.historial);
		ptrAux = ptrAux->ptrsig;
	}
 
	if(TAM == 0){
		printf("=========\n");
		printf("No hay datos existentes.\n");
	}
 
}

void buscarpacienteNombre(){
 
	char nom[N];
 
	imprimirSeparador();
 
	printf("Ingrese el nombre, o el inicio del mismo, que desea utilizar para la búsqueda del paciente: ");
	scanf("%s",nom);
 
	buscarpaciNombre(nom);
 
}
 
/***************************************************************************************************************************/
 
void buscarpaciNombre(char nom[]){
 
	struct nodo *ptrAux;
	int i;
 
	imprimirSeparador();
 
	printf("Pacientes relacionados con '%s'\n", nom);
 
	ptrAux = ptrC;
 
	i = 0;
	while(ptrAux != NULL){
		if(strncasecmp(ptrAux->reg.nombre, nom, strlen(nom)) == 0){
			printf("=========\n");
			printf("Nombre: %s\n",ptrAux->reg.nombre);
			printf("Apellido paterno: %s\n",ptrAux->reg.apellidopat);
			printf("Apellido materno: %s\n",ptrAux->reg.apellidomat);
			printf("Edad: %s\n",ptrAux->reg.edad);
			printf("Peso: %s\n",ptrAux->reg.peso);
			printf("Altura: %s\n",ptrAux->reg.altura);
			printf("Alergias: %s\n",ptrAux->reg.alergia);
			printf("Padecimiento: %s\n",ptrAux->reg.enfermedad);
			printf("Descripcion del tratamiento requerido: %s\n",ptrAux->reg.descripcion);
			printf("Periodicidad de visita: %s\n",ptrAux->reg.consultas);
			printf("Historial clinico: %s\n",ptrAux->reg.historial);
			
			ptrAux = ptrAux->ptrsig;
			i++;
		}
		else{
			ptrAux = ptrAux->ptrsig;
		}
	}
 
	if(i == 0){
		printf("=========\n");
		printf("No hay resultados.\n");
	}
 
}

/***************************************************************************************************************************/

void actualizarPacienteNombre(){
 
	char nom[N];
 
	imprimirSeparador();
 
	printf("Ingrese el nombre, o el inicio del mismo, que desea utilizar para la búsqueda  y actualizacion de datos del paciente: ");
	scanf("%s",nom);
 
	actualizarPaciNombre(nom);
 
}
/***************************************************************************************************************************/
 
void actualizarPaciNombre(char nom[]){
 
	struct nodo *ptrAux;
	int i;
	char c;
 
	imprimirSeparador();
 
	printf("Pacientes relacionados con '%s'\n", nom);
 
	ptrAux = ptrC;
 
	i = 0;
	while(ptrAux != NULL){
		if(strncasecmp(ptrAux->reg.nombre, nom, strlen(nom)) == 0){
			
			printf("=====Escriba los datos para actualizar====\n");
			
			scanf("%c",&c);
			printf("Ingrese el nombre(s):");
			fgets(ptrAux->reg.nombre,N,stdin);
	
			printf("Ingrese el apellido paterno:");
			fgets(ptrAux->reg.apellidopat,N,stdin);
			fflush(stdin);
	
			printf("Ingrese el apellido materno:");
			fgets(ptrAux->reg.apellidomat,N,stdin);
			fflush(stdin);
	
			printf("Ingrese la edad:");
			fgets(ptrAux->reg.edad,m,stdin);
			fflush(stdin);
	
			printf("Ingrese el peso:");
			fgets(ptrAux->reg.peso,m,stdin);
			fflush(stdin);
			
			scanf("%c",&c);
			printf("Ingrese la altura:");
			fgets(ptrAux->reg.altura,m,stdin);
			fflush(stdin);
	
			printf("Ingrese alergia del paciente:");
			fgets(ptrAux->reg.alergia,N,stdin);
			fflush(stdin);
	
			scanf("%c",&c);
			printf("Ingrese el padecimiento:");
			fgets(ptrAux->reg.enfermedad,N,stdin);
			fflush(stdin);
			
			scanf("%c",&c);
			printf("Ingrese una descripcion:");
			fgets(ptrAux->reg.descripcion,N,stdin);
			fflush(stdin);

			scanf("%c",&c);
			printf("Ingrese la periodicidad del tratamiento:");
			fgets(ptrAux->reg.consultas,N,stdin);
			fflush(stdin);
	
			printf("Ingrese el historial clinico:");
			fgets(ptrAux->reg.historial,N,stdin);
			fflush(stdin);
			
			printf("=====Datos actualizados correctamente====\n");
			
			registros(ptrAux->reg.nombre, ptrAux->reg.apellidopat, ptrAux->reg.apellidomat, ptrAux->reg.edad, ptrAux->reg.peso, ptrAux->reg.altura, ptrAux->reg.alergia, ptrAux->reg.enfermedad, ptrAux->reg.descripcion, ptrAux->reg.consultas, ptrAux->reg.historial);
			
			ptrAux = ptrAux->ptrsig;
			i++;
			
		}
		else{
			ptrAux = ptrAux->ptrsig;
		}
	}
 
	if(i == 0){
		printf("=========\n");
		printf("No hay resultados.\n");
	}
}

/***************************************************************************************************************************/

void eliminarPaciente(){
 
	struct nodo *Ptraux = ptrC;
	int i = 0;
	char nom[N];
	int opc;
 
	imprimirSeparador();
 
	printf("Ingrese el nombre del paciente que desea eliminar: ");
	scanf("%s", nom);
	fflush(stdin);
 
	imprimirSeparador();
 
	while(Ptraux != NULL){
		if(strcmp(Ptraux->reg.nombre, nom) == 0){
			i++;
			printf("¿Esta seguro de querer eliminar a '%s'?\n", nom);
			printf("1. Si\n");
			printf("2. No\n");
 
			imprimirSeparador();
 
			scanf("%d", &opc);
 
			switch(opc) {
 
					case 1:
						eliminarPacienteNombre(nom);
						break;
					case 2:
						return;
						break;
					default:
						break;
			}
			if(opc == 1){
				imprimirSeparador();
				printf("El paciente '%s' ha sido borrado.\n", nom);
			}
			break;
		}	
		else{
			Ptraux = Ptraux->ptrsig;
		}
	}
 
	if(i == 0){
		printf("No existe ningun paciente con el nombre '%s'.\n", nom);
	}
 
}
 
/***************************************************************************************************************************/
 
//recibe un nombre, si existe algún contacto en la lista con ese nombre lo borra 
void eliminarPacienteNombre(char nom[]){ 
 
	 struct nodo *Ptrauxborrar;
	 struct nodo *Ptrant = NULL;
 
	 Ptrauxborrar = ptrC; 
 
	 while(strcmp(Ptrauxborrar->reg.nombre, nom) != 0){ 						//mientras el nombre no coincida con el nombre del alumno
		 Ptrant = Ptrauxborrar;										 		//se pasará al siguiente alumno
		 Ptrauxborrar = Ptrauxborrar->ptrsig;
	 }
 
	 //salir del while significa que se encontró el alumno cuyo nombre coincide con el ingresado
 
	 if(Ptrauxborrar->ptrsig != NULL){										//si el alumno ha ser eliminado NO es el ÚLTIMO
			if(Ptrauxborrar != ptrC){											// si el alumno no es el primero
				Ptrant->ptrsig = Ptrauxborrar->ptrsig;							//su anterior seguirá a su sucesor
				free(Ptrauxborrar);											//y el alumno será eliminado
			}
			else{														//si el alumno ES el PRIMERO
				ptrC = Ptrauxborrar->ptrsig;									//el segundo se convertirá en el primero
				free(Ptrauxborrar);											//y el alumno será eliminado
			}
	}
	else{ //Ptrauxborrar->ptrsig = NULL										//si el alumno ha ser eliminado ES el ÚLTIMO
		if(Ptrauxborrar != ptrC){												//y si no es el primero (hay más alumnos)
			Ptrant->ptrsig = NULL;											//su anterior seguirá a NULL
			free(Ptrauxborrar);												//el alumno será eliminado
			ptrF = Ptrant;												//y el anterior se convertirá en el último
		}
		else{															//si el alumno es el único (ES el PRIMERO y el ÚLTIMO)
			free(Ptrauxborrar);												//será eliminado
			ptrC = NULL;
			ptrF = NULL;
		}
	}
 
}

/***************************************************************************************************************************/

void registros(char nombre[], char apellidopat[], char apellidomat[], char edad[], char peso[], char altura[], char alergia[], char enfermedad[], char descripcion[], char consultas[], char historial[]){

	FILE *Fd;
	
	Fd=fopen("//home//victor//Documentos//Sistemas operativos//Proyecto//RegistroPacientes.txt", "a+");
 
 	if(Fd==NULL){
 	      printf("\nError en la creacion del archivo");
 	}
 	else{
 	      printf("\nReporte creado exitosamente, revise el directorio\n\n");
 	}	
 
	fprintf(Fd,"\t***************Paciente***************\n");
	fprintf(Fd,"\nNombre: %s\n",nombre);
	fprintf(Fd,"\nApellido paterno: %s\n",apellidopat);
	fprintf(Fd,"\nApellido materno: %s\n",apellidomat);
	fprintf(Fd,"\nEdad: %s\n",edad);
	fprintf(Fd,"\nPeso: %s\n",peso);
	fprintf(Fd,"\nAltura: %s\n",altura);
	fprintf(Fd,"\nAlergia: %s\n",alergia);
	fprintf(Fd,"\nPadecimiento: %s\n",enfermedad);
 	fprintf(Fd,"\nDescripcion del tratamiento requerido: %s\n",descripcion);
 	fprintf(Fd,"\nPeriodicidad de visita: %s\n",consultas);
 	fprintf(Fd,"\nHistorial clinico: %s\n\n",historial);

	fclose(Fd);	
} 

/***************************************************************************************************************************/

void imprimirOpciones(){  
 	printf("\n[1]. Llenar datos de nuevo Paciente\n");
 	printf("[2]. Imprimir datos\n");
 	printf("[3]. Buscar Paciente por nombre\n");
	printf("[4]. Eliminar paciente\n");
	printf("[5]. Actualizar datos de paciente\n"); 
	printf("[6]. Salir del programa\n");  
	imprimirSeparador(); 
}


int main(){
	int x=1,resp;
	do{	//Este es el Menu
		imprimirOpciones();
		
		scanf("%d",&resp);
		switch (resp){
				case 1:nuevonodo();
						break;
				case 2:imprimir();
					break;
				case 3: buscarpacienteNombre();
					break;
				case 4: eliminarPaciente();
					break; 
				case 5: actualizarPacienteNombre();
					break;
				case 6: x=2;
					break; 
				default: printf("Ingrese una opcion valida\n");	
		}	
	}while(x!=2);
}

