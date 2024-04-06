#include "stringutil.h"

// Kopie stringu s dynamickou paměťovou alokaci
void kopirovat_string(char** cil, char* zdroj) {
    unsigned int delka_stringu = strlen(zdroj);
    *cil = (char*) calloc(delka_stringu + 1, sizeof(char));
    strncpy(*cil, zdroj, delka_stringu);
}

// Vymaze z konzole dany pocet radku
void vymazat_okno(int pocet_radku) {
    for (int i = 0; i < pocet_radku; i++) {
        printf("\x1b[1F"); // Move to beginning of previous line
        printf("\x1b[2K"); // Clear entire line
    }
}