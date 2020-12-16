#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 25

void gotoxy(int x,int y)
{
    printf("%c[%d;%df",0x1B,y,x);
}
int x,y;
void nuevoEsp (char nombre[], char apellidop[], char apellidom[], char especialidad[], char pw[]);
void registros(char nombre[], char apellidop[], char apellidom[], char especialidad[], char pw[]);
void buscarEsp(char nom[],char pwd[]);
void eliminarEspecialista(char nom[]);
void actualizarEspecialista(char nom[]);

struct especialista{			
	char nombre[N];
	char apellidop[N];
	char apellidom[N];
	char especialidad[N];
	char pw[N];	
};

struct nodo{	
	struct especialista reg;			
	struct nodo *sig;
};

struct nodo *inicio=NULL;
struct nodo *fin=NULL;

void registrarEsp(){
	char salto;
	struct nodo *nuevo;
	nuevo=(struct nodo*)malloc(sizeof(struct nodo));
	
	system("cls");
	gotoxy(30,2);printf("Registrarse como especialista");
	gotoxy(15,3);
	printf("********************************************************");
	y=3;
	for(x=0;x<13;x++){
		gotoxy(15,y++);
		printf("*");
	}
	y=3;
	for(x=0;x<13;x++){
		gotoxy(38,y++);
		printf("*");
	}
	y=3;
	for(x=0;x<13;x++){
		gotoxy(70,y++);
		printf("*");
	}
	gotoxy(15,15);
	printf("********************************************************");
	gotoxy(19,5);printf("Nombre: ");
	gotoxy(19,7);printf("Apellido paterno: ");
	gotoxy(19,9);printf("Apellido materno: ");
	gotoxy(19,11);printf("Especialidad: ");
	gotoxy(19,13);printf("Password: ");	
	
	scanf("%c",&salto);
	gotoxy(41,5);fgets(nuevo->reg.nombre,N,stdin);
	fflush(stdin);
		
	gotoxy(41,7);fgets(nuevo->reg.apellidop,N,stdin);
	fflush(stdin);
	
	gotoxy(41,9);fgets(nuevo->reg.apellidom,N,stdin);
	fflush(stdin);
	
	gotoxy(41,11);fgets(nuevo->reg.especialidad,N,stdin);
	fflush(stdin);

	gotoxy(41,13);fgets(nuevo->reg.pw,N,stdin);
	fflush(stdin);

	
 	nuevoEsp(nuevo->reg.nombre, nuevo->reg.apellidop, nuevo->reg.apellidom, nuevo->reg.especialidad, nuevo->reg.pw);
 	
 	registros(nuevo->reg.nombre, nuevo->reg.apellidop, nuevo->reg.apellidom, nuevo->reg.especialidad, nuevo->reg.pw);
 
	free(nuevo);
}

void nuevoEsp (char nombre[], char apellidop[], char apellidom[], char especialidad[], char pw[]){
	struct nodo *aux;
	struct nodo *insertaEsp;
	insertaEsp=(struct nodo*)malloc(sizeof(struct nodo));
	aux=inicio;
	
	while(aux != NULL) {
			if((strcmp(aux->reg.nombre, nombre)) == 0){
				gotoxy(30,16);printf("Este especialista ya estaba registrado.");
				return;
			}
			else{
				aux=aux->sig;
			}
	}
	if(aux == NULL){
		strcpy(insertaEsp->reg.nombre, nombre);
	} 
	strcpy(insertaEsp->reg.apellidop, apellidop);
	strcpy(insertaEsp->reg.apellidom, apellidom);
	strcpy(insertaEsp->reg.especialidad, especialidad);	
	strcpy(insertaEsp->reg.pw, pw);	
	insertaEsp->sig = NULL;

	if(inicio == NULL){ 
		inicio = insertaEsp;
	}
	else{
        fin->sig = insertaEsp;
	}
 
    fin = insertaEsp;
    gotoxy(30,16);printf("Registro exitoso."); 
 
	
}


void comprobarEsp(){
 
	char nom[N];
	char pwd[N];
	system("cls");
	gotoxy(18,2);printf("Datos acceso especialista");
	gotoxy(10,3);
	printf("+-------------------------------------+");
	y=3;
	for(x=0;x<8;x++){
		gotoxy(10,y++);
		printf("+");
	}
	y=3;
	for(x=0;x<8;x++){
		gotoxy(48,y++);
		printf("+");
	}
	gotoxy(10,11);
	printf("+-------------------------------------+");
	gotoxy(13,5);printf("Usuario: ");
	gotoxy(10,7);printf("---------------------------------------");
	gotoxy(13,9);printf("Password: ");
	gotoxy(25,5);scanf("%s",nom);
	gotoxy(25,9);scanf("%s",pwd);
	gotoxy(1,13);	
	buscarEsp(nom,pwd);
 
}

void buscarEsp(char nom[],char pwd[]){
 
	struct nodo *aux;
	int i;
 
	
 
	printf("Especialista '%s'\n", nom);
 
	aux = inicio;
 
	i = 0;
	while(aux != NULL){
		if(strncasecmp(aux->reg.nombre, nom, strlen(nom)) == 0 && strncasecmp(aux->reg.pw,pwd, strlen(pwd))==0){

			printf("Nombre: %s\n",aux->reg.nombre);
			printf("Apellido paterno: %s\n",aux->reg.apellidop);
			printf("Apellido materno: %s\n",aux->reg.apellidom);
			printf("Padecimiento: %s\n",aux->reg.especialidad);
			printf("Password: %s\n",aux->reg.pw);
			
			aux = aux->sig;
			i++;
		}
		else{
			aux = aux->sig;
		}
	}
 
	if(i == 0){
		
		printf("Usuario y contraseña incorrecto.\n");
		
	}else{
		system("clear");
		printf("Bienvenido: %s",nom);
	}
 
}

void registros(char nombre[], char apellidop[], char apellidom[],  char especialidad[],  char pw[]){

	FILE *archivo;
	
	archivo=fopen("medicadist.txt", "a+");
 
 	if(archivo==NULL){
 	      printf("\nError en la creacion del archivo");
 	}
 	else{
 	      printf("\nGuardado con exito\n\n");
 	}	
 
	fprintf(archivo,"Nombre: %s\n",nombre);
	fprintf(archivo,"Apellido paterno: %s\n",apellidop);
	fprintf(archivo,"Apellido materno: %s\n",apellidom);
	fprintf(archivo,"Especialidad: %s\n",especialidad);
 	fprintf(archivo,"Password: %s\n\n",pw);

	fclose(archivo);	
} 

/***************************************************************************************************************************/

void menu(){  
 	gotoxy(15,4);
	printf("*************************************************");
	y=4;
	for(x=0;x<8;x++){
		gotoxy(15,y++);
		printf("*");
	}
	y=4;
	for(x=0;x<8;x++){
		gotoxy(63,y++);
		printf("*");
	}
	gotoxy(15,12);
	printf("*************************************************");
	
	gotoxy(35,5);printf("Medicadist");
    gotoxy(18,7);printf("1.- Iniciar sesion como especialista");
    gotoxy(18,8);printf("2.- Iniciar sesion como paciente");
    gotoxy(18,9);printf("3.- Registrarse");
	 
}


int main(){
	int solicitud;
	system("cls");
	
	menu();
	gotoxy(18,11);printf("Seleccion: ");
    	scanf("%i",&solicitud);
    	while(solicitud<1 || solicitud>3){
    	gotoxy(35,11);printf("Operacion no existente");
    	gotoxy(27,11);printf("     ");
    	gotoxy(18,11);printf("Seleccion: ");
    	scanf("%i",&solicitud);
	}
		switch (solicitud){
				case 1:
					comprobarEsp();
					break;
				case 2:
					system("cls");
					printf("Bienvenido \n");
					break;
				case 3: 
					registrarEsp();
					break;
	
		}	
}
