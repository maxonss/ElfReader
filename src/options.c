#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include "../include/options.h"

// Définition des fonctions liées à chaque option
void option_d(char *filename) {
    printf("Option -d appelée\n");
}

void option_s(char *filename) {
    printf("Option -s appelée\n");
}

void option_a(char *filename) {
    printf("Option -a appelée\n");
}

void option_e(char *filename) {
    printf("Option -e appelée\n");
}

void option_t(char *filename) {
    printf("Option -t appelée\n");
}

void option_l(char *filename) {
    printf("Option -l appelée\n");
}

void option_c(char *filename) {
    printf("Option -c appelée\n");
}

void option_h() {
    printf("Usage: ./ElfReader [file_name] [-d hexadecimal .text] [-s sections count]\n [-a sections list] [-e program entry address] [-t chains table content]\n [-l dynamic libraries list]\n [--c-wizard file system specs]");
}

// Fonction pour afficher les informations standardes du fichier ELF
void print_basic_info(const char *file_to_open) {
    // Ici vous pouvez implémenter la logique pour afficher les informations standardes du fichier ELF
    // Par exemple, vous pouvez utiliser les fonctions stat() ou fstat() pour obtenir des informations sur le fichier
    // N'oubliez pas de vérifier si le fichier est un fichier ELF avant d'afficher ses informations.
    struct stat file_info;

    if (stat(file_to_open, &file_info) != 0) {
        perror("Erreur lors de la récupération des informations du fichier");
        exit(EXIT_FAILURE);
    }

    printf("Taille du fichier : %lld octets\n", file_info.st_size);
}