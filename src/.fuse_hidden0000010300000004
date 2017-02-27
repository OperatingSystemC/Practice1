#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct dogType {
  char nombre[32];
  char tipo[32];
  int edad;
  char raza[16];
  int estatura;
  float peso;
  char sexo;
};

int buscar_numero(float numero, float var){
	int stop=0;
	if(var==numero)
		stop=1;
	return stop;
}

void aleatorio(int *edad, int *estatura, float *peso){
	int min=1, max = 100000, fstop;
	float var, num_aleatorio[3];
	srand(time(NULL)+rand());
	for(int i = 0; i < 3; i++){
		do{
			num_aleatorio[i] = min + rand() % (max-min+1);
		} while(buscar_numero(num_aleatorio[i], var));
		var = num_aleatorio[i];
	}
	*edad = num_aleatorio[0] / 500;
	*estatura = num_aleatorio[1] / 100;
	*peso = num_aleatorio[2] / 100;
}

void randTipo(char* tipo){
	char lettersC[21]="BCDFGHJKLMNPQRSTVWXYZ";
	char vocalsC[5]="AEIOU";
	char letters[21]="bcdfghjklmnpqrstvwxyz";
	char vocals[5]="aeiou";
	int letterOrVocal;
	srand(time(NULL)+rand());
	if(rand() % 2){
		tipo[0] = lettersC[rand() %21];
		letterOrVocal = 0;
	} else {
		tipo[0] = vocalsC[rand() %5];
		letterOrVocal = 1;
	}
	for(int i = 1; i < 32; i++){
		if(letterOrVocal){
			tipo[i] = letters[rand() %21];
			letterOrVocal = 0;
		} else {
			tipo[i] = vocals[rand() %5];
			letterOrVocal = 1;
		}
	}
}

void randRaza(char* raza){
	char lettersC[21]="BCDFGHJKLMNPQRSTVWXYZ";
	char vocalsC[5]="AEIOU";
	char letters[21]="bcdfghjklmnpqrstvwxyz";
	char vocals[5]="aeiou";
	int letterOrVocal;
	srand(time(NULL)+rand());
	if(rand() % 2){
		raza[0] = lettersC[rand() %21];
		letterOrVocal = 0;
	} else {
		raza[0] = vocalsC[rand() %5];
		letterOrVocal = 1;
	}
	for(int i = 1; i < 16; i++){
		if(letterOrVocal){
			raza[i] = letters[rand() %21];
			letterOrVocal = 0;
		} else {
			raza[i] = vocals[rand() %5];
			letterOrVocal = 1;
		}
	}
}

char randSexo(char* sexo){
	if(rand() % 2){
		*sexo = 'H';
	} else {
		*sexo = 'M';
	}
}

int main(){
	FILE* nombres = fopen("src/nombresMascotas.txt", "r+");
	FILE* dataFile = fopen("bin/dataDogs.dat", "w");
	int lines, cantidad = 10000000;
	struct dogType *animal_nuevo;
	animal_nuevo = malloc(sizeof(*animal_nuevo));
	while (fgets(animal_nuevo -> nombre, 32, nombres) != NULL){
		lines ++;
	}
	fseek(nombres, 0, SEEK_SET);
	fwrite(&cantidad, sizeof(int), 1, dataFile);
	printf("Nombre\t\tTipo\t\t\t\tEdad\tRaza\t\tEstatura Peso\t\tSexo\n");
	for ( int i = 0 ; i < cantidad ; i++ ){
		if(fgets(animal_nuevo -> nombre, 32, nombres) == NULL){
			fseek(nombres, 0, SEEK_SET);
		}
		aleatorio(&animal_nuevo -> edad, &animal_nuevo -> estatura, &animal_nuevo -> peso);
		animal_nuevo->nombre[strlen(animal_nuevo->nombre)-1] = '\0';
		randTipo(animal_nuevo -> tipo);
		randRaza(animal_nuevo -> raza);
		randSexo(&animal_nuevo -> sexo);
		animal_nuevo -> tipo[31] = '\0';
		animal_nuevo -> raza[15] = '\0';
		printf("%20s\t%s\t%d\t%s\t%d\t %f\t%c\n", animal_nuevo -> nombre, animal_nuevo -> tipo, animal_nuevo -> edad, animal_nuevo -> raza, animal_nuevo -> estatura, animal_nuevo -> peso, animal_nuevo -> sexo);
		fwrite(animal_nuevo, sizeof(struct dogType), 1, dataFile);
	}
	free(animal_nuevo);
	fclose(dataFile);
	fclose(nombres);
}