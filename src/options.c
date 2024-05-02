#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include "../include/options.h"

// Définition des fonctions liées à chaque option

// Tristan:
// -a : This option will print the list of section including their name and size
//  -e : This option will print the entrypoint address of the program
// Merieme:
// -d : This option will print in hexadecimal format the .text section of the binary
// -s : This option will print the number of section in the binary

/**
 *
 *
 * @param content
 */
void option_d(const char *content) {
    printf("Option -d appelée\n");
}

void option_s(const char *content) {
    printf("Option -s appelée\n");
}

/**
 * Prints the list of sections including their name and size.
 * This function is called when the user passes the -a argument.
 *
 * @param content
 * @author Tristan Salé
 */
void print_section_name_size(const char *content) {
    printf("Option -a appelée\n");
}

/**
 * Prints the entry point address of the given content.
 * This function is called when the user passes the -e argument.
 *
 * @param content
 * @author Tristan Salé
 */
void print_entrypoint_address_program(const char *content) {
    printf("Option -e appelée\n");
}

void option_t(const char *content) {
    printf("Option -t appelée\n");
}

void option_l(const char *content) {
    printf("Option -l appelée\n");
}

void option_c(const char *content) {
    printf("Option -c appelée\n");
}

void option_h() {
    printf("Usage: ./ElfReader [file_name] [-d hexadecimal .text] [-s sections count]\n [-a sections list] [-e program entry address] [-t chains table content]\n [-l dynamic libraries list]\n [--c-wizard file system specs]");
}

// Fonction pour afficher les informations standardes du fichier ELF
void print_basic_info(const char *file_to_open) {
    struct stat file_info;

    if (stat(file_to_open, &file_info) != 0) {
        perror("Erreur lors de la récupération des informations du fichier");
        exit(EXIT_FAILURE);
    }

    printf("Taille du fichier : %ld octets\n", file_info.st_size);
    printf("UID: %d\n", file_info.st_uid);
    //printf("Propriétaire: %s\n", getpwuid(file_info.st_uid)->pw_name);
    printf("Droits: %o\n", file_info.st_mode);
    printf("Nombre de blocs alloués : %ld\n", file_info.st_blocks);
    printf("Taille des blocs alloués : %ld octets\n", file_info.st_blksize);
    printf("Inode : %ld\n", file_info.st_ino);
}