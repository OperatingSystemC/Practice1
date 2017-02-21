#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>


/*
 * Método: keypress
 * Retorna el entero que se presione
 * Tomada de: http://michael.dipperstein.com/keypress.html
 * Autor: Michael Dipperstein
 */
int keypress(unsigned char echo){
    struct termios savedState, newState;
    int c;
    if (-1 == tcgetattr(STDIN_FILENO, &savedState)){
        return EOF;     /* error on tcgetattr */
    }
    newState = savedState;
    if ((echo = !echo)){ /* yes i'm doing an assignment in an if clause */
        echo = ECHO;    /* echo bit to disable echo */
    }
    /* disable canonical input and disable echo.  set minimal input to 1. */
    newState.c_lflag &= ~(echo | ICANON);
    newState.c_cc[VMIN] = 1;
    if (-1 == tcsetattr(STDIN_FILENO, TCSANOW, &newState)){
        return EOF;     /* error on tcsetattr */
    }
    c = getchar();      /* block (withot spinning) until we get a keypress */
    /* restore the saved state */
    if (-1 == tcsetattr(STDIN_FILENO, TCSANOW, &savedState)){
        return EOF;     /* error on tcsetattr */
    }
    return c;
}

/*
 * Declaración de estructura dogType
 * Se añaden variables respectivas a la estructura
 */
struct dogType {
  char nombre[32];
  char tipo[32];
  int edad;
  char raza[16];
  int estatura;
  float peso;
  char sexo;
};

/*
 * Método: confimacion
 * Al presionar una tecla retorna el menú
 */
void confirmacion(){
  printf("Para volver al menú presione cualquier tecla... ");
  // Mi PC siempre muestra 10 presionado, si no sirve así usar:
  // keypress(0);
  while(keypress(0) == 10);
}

/*
 * Método: verificarArchivo
 * Verifica si existe el archivo path
 */
int verificarArchivo(char* path){
  FILE* archivo = fopen(path, "r+"); //Verifica archivo
  if(archivo == NULL){
    return 0;
  }
  return 1;
}

/*
 * Método: crearArchivo
 * Crea un archivo en el directorio y con nombre path
 */
void crearArchivo(char* path){
  FILE* archivo = fopen(path, "w");
  fclose(archivo);
}

/*
 * Método: leerSexo
 * Lee el sexo
 * Valida que el sexo sea H o M
 */
void leerSexo(char* sexo) {
  scanf("%c", sexo);
  // Verifica que lo leído sea h o H
  if (strpbrk(sexo, "hH")) {
    *sexo = 'H';
  // Verifica que lo leído sea m o M
  } else if (strpbrk(sexo, "mM")) {
    *sexo = 'M';    
  // Como no encuentra hHmM en lo leído vuelve a leer.
  } else {
    printf("Solo se puede usar H (Hembra) o M (Macho): ");
    leerSexo(sexo);
  }
};

/*
 * Método: leerAnimal
 * Lee los valores de cada variable de la estructura
 */
struct dogType leerAnimal(struct dogType *animal_nuevo){
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
  leerSexo(&animal_nuevo->sexo);
};

/*
 * Método: ingresarRegistro
 * Ingresa a dataDogs.dat un dogType
 */
void ingresarRegistro() {
  //Abrimos archivo
  FILE* dataFile = fopen("bin/dataDogs.dat", "r+");
  //Validamos errores
  if(dataFile == NULL){
    perror("El archivo no ha podido ser abierto. ERROR");
  } else {
    /* Declaramos dogType
     * Le asignamos espacio en memoria
     * Leemos y asignamos los datos del dogType
     */
    struct dogType* animal_nuevo;
    animal_nuevo = malloc(sizeof(*animal_nuevo));
    leerAnimal(animal_nuevo);
    // Leemos el número de registros existentes
    int registros;
    fread(&registros, sizeof(int), 1, dataFile);
    // Si se pudo leer la cantidad de regs le sumamos 1
    // Sino entonces será el primer reg agregado
    if(registros > 0){
      registros++;
    } else {
      registros = 1;
    }
    // Escribimos el # de regs al principio del archivo
    fseek(dataFile, 0, SEEK_SET);
    fwrite(&registros, sizeof(int), 1, dataFile);
    // Cerramos el archivo y lo abrimos en modo append
    fclose(dataFile);
    dataFile = fopen("bin/dataDogs.dat", "a");
    // Vamos al final del archivo y escribimos la estructura
    fseek(dataFile, 0, SEEK_END);
    fwrite(animal_nuevo, sizeof(struct dogType), 1, dataFile);
    //Cerramos el archivo y liberamos la memoria asignada a animal_nuevo
    fclose(dataFile); 
    free(animal_nuevo);
  }
  confirmacion();
};

/*
 * Método: verRegistro
 * Imprime dogType por número de registro en dataDogs.dat
 */
void verRegistro(){
  // Abrimos el archivo en modo lectura
  FILE* dataFile = fopen("bin/dataDogs.dat", "r");
  // Validamos errores
  if(dataFile == NULL){
    perror("El archivo no ha podido ser abierto. ERROR");
  } else {
    int numReg, registros;
    // Leemos el número de registros existentes
    fread(&registros, sizeof(int), 1, dataFile);
    if(registros <= 0){
      printf("El número de registros existentes es 0, primero ingrese un registro.\n");
      fclose(dataFile);
    } else {
      // Leemos el número de registro a consultar
      printf("El número de registros existentes es %d, indique el número de registro correspondiente al animal que desea ver: ", registros);
      scanf("%i", &numReg);
      // Verificamos que sea un registro válido
      if(registros < numReg || numReg <= 0){
        printf("El registro no existe\n");
        // Cerramos el archivo
        fclose(dataFile);
      } else {
        // Disminuimos para hacer fseek correctamente
        numReg--;
        // Declaramos el dogType y le asignamos memoria
        struct dogType* animal_ext;
        animal_ext = malloc(sizeof(*animal_ext));
        // Vamos a la posición del registro (+4 por el número de regs) y leemos la estructura
        fseek(dataFile, sizeof(struct dogType) * numReg+4, SEEK_SET);
        fread(animal_ext, sizeof(struct dogType), 1, dataFile);
        // Cerramos el archivo
        fclose(dataFile);

        /* Formamos con el nombre, el tipo y la raza un nombre para la historia clínica
         * Unimos la ruta, el nombre y la extensión. Verificamos si existe el archivo
         */
        char* direccion = "bin/historia_clinica/" ; 
        char* extension = ".txt";
        char fileName[strlen(direccion)+strlen(animal_ext -> nombre)+strlen(animal_ext->tipo)+strlen(animal_ext->raza)+strlen(extension)+3];
        snprintf(fileName, sizeof( fileName ), "%s%s_%s_%s%s", direccion, animal_ext -> nombre, animal_ext -> tipo, animal_ext -> raza, extension);
        if(!verificarArchivo(fileName)){
          // Si no existe creamos el archivo
          FILE* historia_clinica = fopen(fileName, "w");
          // Si no existe la carpeta la creamos y volvemos a abrir el archivo
          if(historia_clinica == NULL){
            system("mkdir bin/historia_clinica/");
            historia_clinica = fopen(fileName, "w");
          }
          // Guardamos los datos y lo cerramos
          fprintf(historia_clinica, " Nombre: %s\n Tipo: %s\n Edad: %d\n Raza: %s\n Estatura: %d\n Peso: %f\n Sexo: %c\n Notas: ", animal_ext -> nombre, animal_ext -> tipo, animal_ext -> edad, animal_ext -> raza, animal_ext -> estatura, animal_ext -> peso, animal_ext -> sexo);
          fclose(historia_clinica);
        }
        // Liberamos la memoria de animal_ext pues no se usa más
        free(animal_ext);
        // Creamos nano y le asignamos el comando para abrir nano con la historia clínica
        char nano[strlen(fileName)+6];
        snprintf(nano, sizeof( nano ), "nano %s", fileName);
        system(nano);
      }
    }
  }
  confirmacion();
};

/*
 * Método: borrarRegistro
 * Imprime dogType por número de registro en dataDogs.dat
 */
void borrarRegistro(){
  // Abrimos el archivo en modo lectura
  FILE* dataFile = fopen("bin/dataDogs.dat", "r");
  // Validamos errores
  if(dataFile == NULL){
    perror("El archivo no ha podido ser abierto. ERROR");
  } else {
    int numReg, registros;
    // Leemos el número de registros existentes
    fread(&registros, sizeof(int), 1, dataFile);
    if(registros <= 0){
      printf("El número de registros existentes es 0, primero ingrese un registro.\n");
      fclose(dataFile);
    } else {
      // Leemos el número de registro a consultar
      printf("El número de registros existentes es %d, indique el número de registro correspondiente al animal que desea borrar: ", registros);
      scanf("%i", &numReg);
      // Verificamos que sea un registro válido
      if(registros < numReg || numReg <= 0){
        printf("El registro no existe\n");
        // Cerramos el archivo
        fclose(dataFile);
      } else {
          // Declaramos el dogType a borrar y le asignamos memoria
          struct dogType* animal_borr;
          animal_borr = malloc(sizeof(*animal_borr));
          // Creamos un archivo copia para eliminar el animal y escribimos el número de registros
          registros--;
          FILE* dataFileCopy = fopen("bin/dataDogs.temp", "w");
          fwrite(&registros, sizeof(int), 1, dataFileCopy);
          //Lo aumentamos de nuevo para hacer la copia correctamente
          registros++;
          // Declaramos un dogType temporal y le asignamos memoria.
          // Recorremos todo el archivo haciendo copia de todos excepto de ese dato.
          
          struct dogType* animal_temp;
          animal_temp = malloc(sizeof(*animal_temp));
          int i;
          for(i = 1 ; i <= registros ; i++){
            // Excluimos el registro de número numReg y lo guardamos en animal_borr
            if(i == numReg){
              fread(animal_borr, sizeof(struct dogType), 1, dataFile);
            } else {
              // Leemos y escribimos del original a la copia
              fread(animal_temp, sizeof(struct dogType), 1, dataFile);
              fwrite(animal_temp, sizeof(struct dogType), 1, dataFileCopy);
            }
          }
          
          /* Declaramos dos arreglos de dogType
           * animal_tempBefore para todos los dogType hasta el anterior al que se borrará
           * animal_tempAfter para todos los que están después del que se borrará
           */
          /*struct dogType* animal_tempBefore[numReg-1];
          struct dogType* animal_tempAfter[registros-numReg];
          // Leemos todos los dogType del archivo original
          fread(&animal_tempBefore, sizeof(struct dogType), numReg-1, dataFile);
          fread(&animal_borr, sizeof(struct dogType), 1, dataFile);
          fread(&animal_tempAfter, sizeof(struct dogType), registros-numReg, dataFile);
          // Escribimos los dogType restantes
          fwrite(&animal_tempBefore, sizeof(struct dogType), numReg-1, dataFileCopy);
          fwrite(&animal_tempAfter, sizeof(struct dogType), registros-numReg, dataFileCopy);
          // Cerramos los archivos y liberamos memoria
          int i;
          for(i = 0; i < numReg-1; i++){
            printf("%s\n", animal_tempBefore[i]);
          }
          for(i = 0; i < registros-numReg; i++){
            printf("%s\n", animal_tempAfter[i]);
          }*/
          fclose(dataFile);
          fclose(dataFileCopy);

          system("rm bin/dataDogs.dat");
          system("mv bin/dataDogs.temp bin/dataDogs.dat");

          /* Formamos la ruta para eliminar la historia clínica así:
           * ruta, nombre, tipo, raza y extensión
           * Unimos la ruta, el nombre y la extensión. Verificamos si existe el archivo
           */
          char* direccion = "bin/historia_clinica/" ; 
          char* extension = ".txt";
          char fileName[strlen(direccion)+strlen(animal_borr -> nombre)+strlen(animal_borr->tipo)+strlen(animal_borr->raza)+strlen(extension)+3];
          snprintf(fileName, sizeof( fileName ), "%s%s_%s_%s%s", direccion, animal_borr -> nombre, animal_borr -> tipo, animal_borr -> raza, extension);
          // Verificamos si existe el archivo
          if(verificarArchivo(fileName)){
            // Si existe creamos rm para eliminar el archivo
            char rm[strlen(fileName)+4];
            snprintf(rm, sizeof( rm ), "rm %s", fileName);
            system(rm);
          }
          // Liberamos la memoria de animal_borr
          free(animal_borr);
        }
    }
  }
  confirmacion();
};

/*
 * Método: menu
 * Imprime el menú
 */
void menu(){
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
}

/*
 * Método: leerOpcion
 * Lee la opción de menú seleccionada
 */
void leerOpcion(){
  int opc;  
  scanf("%i", &opc);
  switch (opc) {
    case 1:
      ingresarRegistro();
      break;
    case 2:
      verRegistro();
      break;
    case 3:
      borrarRegistro();
      break;
    case 4:
      break;
    case 5:
      exit(-1);
    default:
      printf("Ingrese una opción válida.");
      break;
  }
}

int main() {
  if(!verificarArchivo("bin/dataDogs.dat")){
    crearArchivo("bin/dataDogs.dat");
  }
  do {
    system("clear");
    menu();
    leerOpcion();
  } while (1);
};
