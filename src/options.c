#include <stdio.h>
#include "../include/options.h"

// Définition des fonctions liées à chaque option
void option_d(char *filename) {
    printf("Option -d appelée pour le fichier %s\n", filename);
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
void print_basic_info(char *filename) {
    // Ici vous pouvez implémenter la logique pour afficher les informations standardes du fichier ELF
    // Par exemple, vous pouvez utiliser les fonctions stat() ou fstat() pour obtenir des informations sur le fichier
    // N'oubliez pas de vérifier si le fichier est un fichier ELF avant d'afficher ses informations.
    printf("Informations standardes pour le fichier ELF : %s\n", filename);
}