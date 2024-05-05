#include "main.h"

//TODO: Vyčistit zdejší include seznam

Pozorovani* main_prvni_pozorovani = NULL;

int main() {
    vykreslovat_seznam_pozorovani(&main_prvni_pozorovani);

    return 0;
}

void ukoncit_program() {
    // Ulozeni souboru
    Pozorovani* momentalni_pozorovani = main_prvni_pozorovani;
    while(momentalni_pozorovani) {
        uloz_pozorovani(momentalni_pozorovani);
        momentalni_pozorovani = momentalni_pozorovani->dalsi_pozorovani;
    }

    smazat_seznam_pozorovani(main_prvni_pozorovani);

    exit(EXIT_SUCCESS);
}