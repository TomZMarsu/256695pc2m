#include "stringutil.h"

// Kopie stringu s dynamickou paměťovou alokaci
void kopirovat_string(char** cil, char* zdroj) {
    unsigned int delka_stringu = strlen(zdroj);
    *cil = (char*) calloc(delka_stringu + 1, sizeof(char));
    strncpy(*cil, zdroj, delka_stringu);
}
    