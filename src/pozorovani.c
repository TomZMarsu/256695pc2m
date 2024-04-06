#include "pozorovani.h"

Pozorovani* pozorovani_init() {
    Pozorovani* pozorovani = (Pozorovani*) malloc(sizeof(Pozorovani));
    pozorovani->datum_pozorovani = datum_init();
    pozorovani->poloha = "";
    pozorovani->poznamka = "";
    pozorovani->prvni_ptak = NULL;

    return pozorovani;
}