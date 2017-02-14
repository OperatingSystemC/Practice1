#include <stdio.h>

struct Animal {
  char    nombre[32];
  char    tipo[32];
  int     edad;
  char    raza[16];
  int     estatura;
  float   peso;
  char    sexo;
};

void add_reg(){
  struct Animal nada;

  printf("Ingresa los siguientes datos:\nNombre: ");
  scanf("%s", nada.nombre);
  printf("Tipo: ");
  scanf("%s", nada.tipo);
  printf("Edad: ");
  scanf("%d", &nada.edad);
  printf("Raza: ");
  scanf("%s", nada.raza);
  printf("Estatura: ");
  scanf("%d", &nada.estatura);
  printf("Peso: ");
  scanf("%f", &nada.peso);
  printf("Sexo: ");
  scanf("%c", &nada.sexo);
  
};

int main(){
  while(1){
    int opcion;
    printf("\n1. Ingresar registro\n2. Ver registro\n3. Borrar registro\n4. Buscar registro\n5. Salir\n");
    scanf("%d", &opcion);
    switch(opcion) {
      case 1:
        add_reg();
        break;
      case 2:
        
        break;
      case 3:
        
        break;
      case 4:
        
        break;
      case 5:
        return 1;
    }
  }
};
