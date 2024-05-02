#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <elf.h>

#include "../include/options.h"

// Nombre d'options disponibles
// TODO: Ajouter un count de options[]
const int NB_OPTIONS = 7;

// Définition du tableau d'options
Option options[] = {
        {"-d", option_d, 1},
        {"-s", option_s, 1},
        {"-a", print_section_name_size, 1},
        {"-e", print_entrypoint_address_program, 1},
        {"-t", option_t, 1},
        {"-l", option_l, 1},
        {"-h", option_h, 0}
};




int main(int argc, char *argv[]) {
    // Vérifier que le nom du fichier ELF a été fourni
    if (argc < 2) {
        printf("Erreur: veuillez fournir un nom de fichier.\n");
        option_h();
        return 1;
    }

    // Stocker le nom du fichier ELF
    char *filename = argv[1];

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
            printf("Erreur : option invalide '%s'\n", argv[i]);
            option_h();
            return 1;
        }
    }

    return 0;
}