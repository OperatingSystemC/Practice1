#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Animal {
  char nombre[32];
  char tipo[32];
  int edad;
  char raza[16];
  int estatura;
  float peso;
  char sexo;
};

char leerSexo() {
  char tipo;
  scanf("%s", &tipo);
  if (strpbrk(&tipo, "hH")) {
    return 'H';
  } else if (strpbrk(&tipo, "mM")) {
    return 'M';
  } else {
    printf("Solo se puede usar H (Hembra)o M (Macho): ");
    return leerSexo();
  }
};

struct Animal leerAnimal(struct Animal *animal_nuevo){
  printf("Nombre: ");
  scanf("%s", &animal_nuevo->nombre);
  printf("Tipo: ");
  scanf("%s", &animal_nuevo->tipo);
  printf("Edad: ");
  scanf("%d", &animal_nuevo->edad);
  printf("Raza: ");
  scanf("%s", &animal_nuevo->raza);
  printf("Estatura: ");
  scanf("%d", &animal_nuevo->estatura);
  printf("Peso: ");
  scanf("%f", &animal_nuevo->peso);
  printf("Sexo: ");
  animal_nuevo->sexo = leerSexo();
};

void ingresarRegistro() {
  struct Animal* animal_nuevo;
  int num = 0;

  animal_nuevo = malloc(sizeof(*animal_nuevo));
  leerAnimal(animal_nuevo);

  FILE* dataFile = fopen("bin/animales.dat", "r+");
  //fscanf(dataFile, "%d", &num);
  fread(&num, sizeof(int), 1, dataFile);
  if(num > 0){
    num++;
  } else {
    num = 1;
  }
  fseek(dataFile, 0, SEEK_SET);
  fwrite(&num, sizeof(int), 1, dataFile);
  //fprintf(dataFile, "%d\n", num);
  fclose(dataFile);
  dataFile = fopen("bin/animales.dat", "a");
  fseek(dataFile, 0, SEEK_END);
  fwrite(animal_nuevo, sizeof(struct Animal), 1, dataFile);
  
  fclose(dataFile); 
  free(animal_nuevo);
};

void verRegistro(){
  int num = 0, cantidad = 0;

  struct Animal *animal_ext;
  animal_ext = malloc(sizeof(*animal_ext));

  FILE* dataFile = fopen("bin/animales.dat", "r");
  fread(&cantidad, sizeof(int), 1, dataFile);

  printf("numero de registros existentes es %d, indique el número de registro correspondiente al animal que desea ver: ",cantidad);
  scanf("%i", &num);
  num--;
  fclose(dataFile);
  if(cantidad >= num){
    dataFile = fopen("bin/animales.dat", "r");
    fseek(dataFile, sizeof(struct Animal) * num+4, SEEK_SET);
    fread(animal_ext, sizeof(struct Animal), 1, dataFile);
    fclose(dataFile);

    FILE* historia_clinica;
    char* direccion = "bin/historia_clinica/" ; 
    char* extension = ".txt";
    char fileSpec[strlen(direccion)+strlen(animal_ext -> nombre)+strlen(animal_ext->tipo)+strlen(animal_ext->raza)+strlen(extension)+3];

    snprintf(fileSpec, sizeof( fileSpec ), "%s%s_%s_%s%s", direccion, animal_ext -> nombre, animal_ext -> tipo, animal_ext -> raza, extension);    

    historia_clinica = fopen(fileSpec, "w");
    fprintf(historia_clinica, " Nombre: %s\n Tipo: %s\n Edad: %d\n Raza: %s\n Estatura: %d\n Peso: %f\n Sexo: %c\n Notas: ", animal_ext -> nombre, animal_ext -> tipo, animal_ext -> edad, animal_ext -> raza, animal_ext -> estatura, animal_ext -> peso, animal_ext -> sexo);

    fclose(historia_clinica);


    char nano[strlen(fileSpec)+6];
    snprintf(nano, sizeof( nano ), "nano %s", fileSpec);
    system(nano);
  } else {
    printf("El registro no existe\n");
  }
  free(animal_ext);
};


int main() {
  int opc;
  do {
    printf("\n==========================");
    printf("\n|\t.:|Menú|:.\t |");
    printf("\n==========================");
    printf("\n| 1. Ingresar registro\t |");
    printf("\n| 2. Ver registro\t |");
    printf("\n| 3. Borrar registro\t |");
    printf("\n| 4. Buscar registro\t |");
    printf("\n| 5. Salir\t\t |");
    printf("\n==========================");
    printf("\nOpcion: ");
    scanf("%i", &opc);
    switch (opc) {
      case 1:
        ingresarRegistro();
        break;
      case 2:
        verRegistro();
        break;
      case 3:
        break;
      case 4:
        break;
    }
  } while (opc != 5);
};
