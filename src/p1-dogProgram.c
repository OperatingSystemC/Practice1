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

  FILE* dataFile = fopen("animales.dat", "r+");
  fscanf(dataFile, "%d", &num);
  if(num >= 0){
    num++;
  } else {
    num = 1;
  }
  fseek(dataFile, 0, SEEK_SET);
  fprintf(dataFile, "%d\n", num);
  fclose(dataFile);
  dataFile = fopen("animales.dat", "a");
  fseek(dataFile, 0, SEEK_END);
  fprintf(dataFile, "%s %s %d %s %d %f %c\n", &animal_nuevo->nombre, &animal_nuevo->tipo, animal_nuevo->edad, &animal_nuevo->raza, animal_nuevo->estatura, animal_nuevo->peso, animal_nuevo->sexo);
  fclose(dataFile);

  free(animal_nuevo);
};

void verRegistro(){
  //struct Animal* animal_existente;
  int num = 0, cantidad = 0;
  printf("Indique el número de registro correspondiente al animal que desea ver: ");
  scanf("%i", &num);
  char line[150];
  FILE* dataFile = fopen("animales.dat", "r");  
  cantidad = atoi(fgets(line, 150, dataFile));
  if(cantidad >= num){
    while (num>0){
      fgets(line, 150, dataFile);
      num--;
    }
    char *nombre = strtok(line, " ");
    printf("Nombre: %s\n", nombre);
    char *tipo = strtok(NULL, " ");
    printf("Tipo: \t%s\n", tipo);
    char *edad = strtok(NULL, " ");
    printf("Edad: \t%s\n", edad);
    char *raza = strtok(NULL, " ");
    printf("Raza: \t%s\n", raza);
    char *estatura = strtok(NULL, " ");
    printf("Estatura: %s\n", estatura);
    char *peso = strtok(NULL, " ");
    printf("Peso: \t%s\n", peso);
    char *sexo = strtok(NULL, " ");
    printf("Sexo: \t%s", sexo);
  } else {
    printf("El registro no existe");
  }  
  fclose(dataFile);
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
