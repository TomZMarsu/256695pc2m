#include "nacitacdat.h"
#include <string.h>

int main() {
    Pozorovani* nactene_pozorovani = nacist_pozorovani("./tests/test_nacteni_pozorovani/pozorovani2.dat");

    if (nactene_pozorovani == NULL) {
        perror("CHYBA PRI PRACI SE SOUBOREM");
        return 1;
    }

    // Kontrola data
    if (nactene_pozorovani->datum_pozorovani->den != 0) {
        perror("NACTENE DATUM NESOUHLASI (OCEKAVANO: DEN=0)");
        printf("NACTENO: DEN=%u\n", nactene_pozorovani->datum_pozorovani->den);
        return 2;
    }

    if (nactene_pozorovani->datum_pozorovani->mesic != 0) {
        perror("NACTENE DATUM NESOUHLASI (OCEKAVANO: MESIC=0)");
        printf("NACTENO: MESIC=%u\n", nactene_pozorovani->datum_pozorovani->mesic);
        return 3;
    }

    if (nactene_pozorovani->datum_pozorovani->rok != 0) {
        perror("NACTENE DATUM NESOUHLASI (OCEKAVANO: ROK=0)");
        printf("NACTENO: ROK=%u\n", nactene_pozorovani->datum_pozorovani->rok);
        return 4;
    }

    if (nactene_pozorovani->datum_pozorovani->hodiny != 0) {
        perror("NACTENE DATUM NESOUHLASI (OCEKAVANO: HODINY=0)");
        printf("NACTENO: HODINY=%u\n", nactene_pozorovani->datum_pozorovani->hodiny);
        return 5;
    }

    if (nactene_pozorovani->datum_pozorovani->minuty != 0) {
        perror("NACTENE DATUM NESOUHLASI (OCEKAVANO: MINUTY=0)");
        printf("NACTENO: MINUTY=%u\n", nactene_pozorovani->datum_pozorovani->minuty);
        return 6;
    }

    // Kontrola poznamky
    if (strcmp(nactene_pozorovani->poznamka, "")) {
        perror("NACTENA POZNAMKA NESOUHLASI (OCEKAVANO: \"\")");
        printf("NACTENO: %s\n", nactene_pozorovani->poznamka);
        return 7;
    }

    // Kontrola polohy
    if (strcmp(nactene_pozorovani->poloha, "")) {
        perror("NACTENA POLOHA NESOUHLASI (OCEKAVANO: \"\")");
        printf("NACTENO: %s\n", nactene_pozorovani->poloha);
        return 8;
    }

    return 0;
}