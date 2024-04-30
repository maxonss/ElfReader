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
        exit(EXIT_FAILURE);
    }

	printf("Taille du fichier : %ld octets\n", file_info.st_size);
}

char* charger_en_ram(const char *file_to_open){
	FILE *file = fopen(file_to_open, "rb");
	if (!file){
                perror("CANNOT OPEN THE FILE");
                return NULL;
        }

	char *buffer = NULL;
	long file_size;
	fseek(file, 0, SEEK_END);
	file_size = ftell(file);
	rewind(file);
	buffer = (char *)malloc(file_size + 1);
	if (buffer == NULL) {
        	perror("Erreur lors de l'allocation mémoire");
        	fclose(file);
        	return "1";
	}

	if (fread(buffer, 1, file_size, file) != file_size) {
        	perror("Erreur lors de la lecture du fichier");
         	free(buffer);
        	fclose(file);
        	return "1";
	}

	buffer[file_size] = '\0';
     	fclose(file);
	return buffer;

}

Elf64_Ehdr get_elf_header(const char *file_to_open) {
	Elf64_Ehdr *elf_header = malloc(sizeof(Elf64_Ehdr));
    if (elf_header == NULL) {
        // Gestion de l'erreur d'allocation
        return NULL;
    }
    memcpy(elf_header, file_to_open, sizeof(Elf64_Ehdr));
    return elf_header;
}

void list_section_name_size(const char *file_to_open){
	printf("HAHAHAHAHAHAHAHAHAH");
	Elf64_Ehdr elf_header = get_elf_header(file_to_open);
	printf("Heho");
	int i = 0;
	for (i; i < elf_header.e_shnum; i++) {
        	//printf("Section %d: %s\n", i, (char *)(file_data + section_header.sh_name));
    }
	printf("Il y a %d sections dans ce fichier ELF", i);

}



void entrypoint_address_program(const char *file_to_open){


}



// FONCTIONS PRINCIPALE
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char* contenu_buffer_fichier = charger_en_ram(argv[1]);
    //printf("Contenu du fichier :\n%100x\n", contenu_buffer_fichier);
    basic_informations(argv[1]);
    check_ELF(contenu_buffer_fichier);
    list_section_name_size(contenu_buffer_fichier);
    //entrypoint_address_program(contenu_buffer_fichier);

    free(contenu_buffer_fichier);
    return 0;
}