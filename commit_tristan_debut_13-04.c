#include <stdio.h>
#include <elf.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
//variables


//FONCTIONS SECONDAIRES
void check_ELF(const char *contenu_buffer_fichier) {
	if(contenu_buffer_fichier[0] != 0x7F || contenu_buffer_fichier[1] != 'E' || contenu_buffer_fichier[2] != 'L' || contenu_buffer_fichier[3] != 'F'){
		printf("not an elf, gimme an elf please\n");
		exit(EXIT_FAILURE);
	}
	printf("That's OK\n");
	exit(EXIT_SUCCESS);
}

void basic_informations(const char *file_to_open){
	struct stat file_info;
    	if (stat(file_to_open, &file_info) != 0) {
        	perror("Erreur lors de la récupération des informations du fichier");
        	return;
    	}

	printf("Taille du fichier : %ld octets\n", file_info.st_size);

}

char* charger_en_ram(const char *file_to_open){
	FILE *file = fopen(file_to_open, "rb");
	if (!file){
		perror("CANNOT OPEN THE FILE");
		return NULL;
	}
	fseek(file, 0, SEEK_END);
	long taille_fichier = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* buffer = (char*)malloc(taille_fichier + 1);
	if(buffer == NULL){
		perror("Erreur d'allocation mémoire");
		fclose(file);
		return NULL;
	}
	fread(buffer, 1, taille_fichier, file);
	buffer[taille_fichier] = '\0';

	fclose(file);
	return buffer;

}

// FONCTIONS PRINCIPALE
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char* contenu_buffer_fichier = charger_en_ram(argv[1]);
    basic_informations(argv[1]);
    check_ELF(contenu_buffer_fichier);
    free(contenu_buffer_fichier);
    return 0;
}
