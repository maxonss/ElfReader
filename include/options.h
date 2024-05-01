#ifndef OPTIONS_H
#define OPTIONS_H

// Définition de la structure pour stocker les informations sur chaque option
typedef struct {
    const char *name;          // Utilisation de const char * pour les chaînes constantes
    void (*function)(char *);  // Type de fonction ajusté
    int required_arg;          // Indique si l'option requiert un argument (1 = oui, 0 = non)
} Option;

// Déclaration des fonctions liées à chaque option
void print_basic_informations(const char *file_to_open);
void option_s(char *filename);
void option_a(char *filename);
void option_e(char *filename);
void option_t(char *filename);
void option_l(char *filename);
void option_c(char *filename);
void option_h();
void print_basic_info(char *filename);
#endif // OPTIONS_H
