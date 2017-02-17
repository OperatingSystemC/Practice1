#include <stdio.h>
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

struct Animal* add_reg(struct Animal* NuevoAnimal){
  char sexo;
  printf("Ingresa los siguientes datos:\nNombre: ");
  scanf("%s", &NuevoAnimal->nombre);
  printf("Tipo: ");
  scanf("%s", &NuevoAnimal->tipo);
  printf("Edad: ");
  scanf("%d", &NuevoAnimal->edad);
  printf("Raza: ");
  scanf("%s", &NuevoAnimal->raza);
  printf("Estatura: ");
  scanf("%d", &NuevoAnimal->estatura);
  printf("Peso: ");
  scanf("%e", &NuevoAnimal->peso);
  printf("Sexo: ");
  scanf("%s", &sexo);
  if (!strpbrk(&sexo, "mMhH")){
    printf("Sexo inválido");
    struct Animal* Basura;
    return Basura;
  }
  NuevoAnimal->sexo = sexo;
  return NuevoAnimal;
};

void main(){
  while(1){
    FILE *writeable;
    int opcion;
    struct Animal* Animalito;
    printf("\n1. Ingresar registro\n2. Ver registro\n3. Borrar registro\n4. Buscar registro\n5. Salir\n");
    scanf("%d", &opcion);
    switch(opcion) {
      case 1:
        Animalito = add_reg(Animalito);
        /*writeable = fopen("animales.txt", "wb");
        int tam;
        tam = fwrite(&Animalito, 1, sizeof(struct Animal), writeable);
        fclose(writeable);*/
        break;
      case 2:
        
        break;
      case 3:
        
        break;
      case 4:
        
        break;
      case 5:
        return;
    }
  }
};
;