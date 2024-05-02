#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <elf.h>
#include <gelf.h>
#include <libelf.h>

#include "../include/options.h"
/**
 *
 *
 * @param content
 * @authors Maxence Puhetini, Tristant Salé
 */
void check_ELF(const char *content) {
    const char elf_magic[] = {0x7F, 'E', 'L', 'F'};
    if (memcmp(content, elf_magic, sizeof(elf_magic)) != 0) {
        printf("not an elf, gimme an elf please\n");
        exit(EXIT_FAILURE);
    }
    printf("That's and elf\n");
}

// Nombre d'options disponibles
// TODO: Ajouter un count de options[]
const int NB_OPTIONS = 7;

// Définition du tableau d'options
Option options[] = {
        {"-d", (void (*)(const char *)) print_text_section_hex,           1},
        {"-s", (void (*)(const char *)) print_section_count,              1},
        {"-a", (void (*)(const char *)) print_section_name_size,          1},
        {"-e", (void (*)(const char *)) print_entrypoint_address_program, 1},
        {"-t", (void (*)(const char *)) option_t,                         1},
        {"-l", (void (*)(const char *)) option_l,                         1},
        {"-h", option_h,                                            0}
};

char* copy_file_to_memory(const char *file_to_open) {
    FILE *file = fopen(file_to_open, "rb");
    if (!file) {
        perror("Erreur: impossible de lire le fichier");
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

int main(int argc, char *argv[]) {
    // Vérifier que le nom du fichier ELF a été fourni
    if (argc < 2) {
        printf("Erreur: veuillez fournir un nom de fichier.\n");
        option_h();
        return 1;
    }

    // Stocker le nom du fichier ELF
    char *filename = argv[1];

    char* content = copy_file_to_memory(argv[1]);
    // printf("Contenu du fichier :\n%100x\n", content);
    print_basic_info(argv[1]);
    check_ELF(content);

    Elf64_Ehdr *elf_header = malloc(sizeof(200000)); //mettre plutot Elf64_Ehdr mais problème de compilation
    memcpy(elf_header, content, sizeof(200000));  //mettre plutot Elf64_Ehdr mais problème de compilation
    // Si aucun argument autre que le nom du fichier n'est passé, afficher les informations standards du fichier ELF
    if (argc == 2) {
        print_basic_info(filename);
        return 0;
    }

    // Parcourir les arguments passés en ligne de commande
    for (int i = 2; i < argc; i++) {
        // Vérifier si l'argument correspond à une option
        bool option_found = false;

        for (int j = 0; j < NB_OPTIONS; j++) {
            if (strcmp(argv[i], options[j].name) == 0) {
                // Appeler la fonction liée à l'option
                options[j].function(filename);
                option_found = true;
                break;
            }
        }

        if (!option_found) {
            // Si l'argument ne correspond à aucune option, afficher un message d'erreur et quitter le programme
            printf("Erreur: option invalide '%s'\n", argv[i]);
            option_h();
            return 1;
        }
    }
    free(content);
    free(elf_header);
    return 0;
}