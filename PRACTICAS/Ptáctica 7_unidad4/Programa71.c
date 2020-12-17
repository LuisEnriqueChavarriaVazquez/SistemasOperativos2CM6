#include <stdio.h>
#include <windows.h>
#include <winuser.h>
#include <stdlib.h>

// FUNCIONES PARA EL CURSOR




void main()
{

	int x,y,direccion;
     x=0;
     y=0;
    direccion=1;
    int vueltas=0;
	while (1)
	{
		Sleep(50);
		if(direccion==1){
			x++;
			y++;
		}
		else{
			if(direccion==-1){
				x--;
				y--;
			}
		}
		
		if(x==100){
	       direccion=-1;
	        printf("\r X = %i , Y = %i         ", x , y);
	       Sleep(500);
	      
		}else{
			if(x==0){
			vueltas++;
			   direccion=1;
			   	printf("\r X = %i , Y = %i          ", x , y);
			   Sleep(500);
			   
			}else{
			   printf("\r X = %i , Y = %i           ", x , y);
			}
		}
		
	
         SetCursorPos(x,y);
         
         if(vueltas==2){
		   break;
		 }
		 
	}
 
 
 
}

