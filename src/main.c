#include "main.h"

//TODO: Vyčistit zdejší include seznam

Pozorovani* main_prvni_pozorovani = NULL;

int main() {
    
    vykreslovat_seznam_pozorovani(&main_prvni_pozorovani);

    return 0;
}

void ukoncit_program() {
    if(main_prvni_pozorovani == NULL) {
        printf("ZASE NULA\n\n\n");
    }
    smazat_seznam_pozorovani(main_prvni_pozorovani);

    exit(EXIT_SUCCESS);
}