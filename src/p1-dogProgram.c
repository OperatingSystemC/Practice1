#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Animal {
  char    nombre[32];
  char    tipo[32];
  int     edad;
  char    raza[16];
  int     estatura;
  float   peso;
  char    sexo;
};

void add_reg( );

char validar_FM(){//Nos aseguramos que sólo se permitan los dos caracteres H y M.
    char tipo;
    scanf( "%c", &tipo);
    if(tipo=='H' || tipo=='h'){
        return 'H';
    }
    else if(tipo=='M' || tipo=='m'){
        return 'M';
    }
    else{
        printf( "Solo se puede usar H (Hembra)o M (Macho): " );
        return validar_FM();
    }
}


void add_reg(){

	struct Animal *new_animal;
	int num=0;
		
	new_animal = malloc(sizeof(*new_animal));

	printf("Nombre: ");
	scanf("%s",&new_animal->nombre);
	printf("Tipo: ");
	scanf("%s",&new_animal->tipo);
	printf("Edad: ");
	scanf("%d",&new_animal->edad);
	printf("Raza: ");
	scanf("%s",&new_animal->raza);
	printf("Estatura: ");
	scanf("%d",&new_animal->estatura);
	printf("Peso: ");
	scanf("%f",&new_animal->peso);	
	printf("Sexo: ");
	new_animal->sexo=(char)validar_FM();
	
	  //abrimos el archivo
	FILE * fileInfo = fopen( "bin/animales.dat", "r+");
	  //leemos el numero de registros
	fscanf( fileInfo, "%d", &num );
	  //lo aumentamos en 1
	num++;
	 // entra al archivo desde el inicio e imprime el numero en el archivo	
	fseek( fileInfo, 0, SEEK_SET );
    	fprintf( fileInfo, "%d\n", num );
    	fclose( fileInfo );

	 //Abrimos el archivo de datos para agregar el nuevo registro.
 	fileInfo = fopen( "bin/animales.dat", "a+");
    	fseek( fileInfo, 0, SEEK_END );
    	fprintf( fileInfo, "%s %s %d %s %d %f %c\n", &new_animal -> nombre, new_animal -> tipo,
  	   &new_animal -> edad, &new_animal -> raza, &new_animal -> estatura, &new_animal -> peso, &new_animal -> sexo);
    	fclose( fileInfo );

  	//Liberamos la memoria reservada para la estructura.
    	free( new_animal );
}


int main(){
	
	
	int opc;
	
	do{
		printf("\n\t.:MENU:.");
		printf("\n1. Ingresar registro");
		printf("\n2. Ver registro");
		printf("\n3. Borrar registro");
		printf("\n4. Buscar registro");
		printf("\n4. Salir");
		printf("\nOpcion: ");
		scanf("%i",&opc);
		
		switch(opc){
			case 1: add_reg();break;
			case 2: break;
			case 3: break;
			case 4: break;
		}
		
	}while(opc != 5);

}
