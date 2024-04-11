#include "pozorovani.h"

Pozorovani* pozorovani_init() {
    Pozorovani* pozorovani = (Pozorovani*) malloc(sizeof(Pozorovani));
    pozorovani->datum_pozorovani = datum_init();
    pozorovani->poloha = NULL;
    pozorovani->poznamka = NULL;
    pozorovani->prvni_ptak = NULL;

    kopirovat_string(&(pozorovani->poloha), "");
    kopirovat_string(&(pozorovani->poznamka), "");

    return pozorovani;
}

Ptak** posledni_ptak_v_pozorovani(Pozorovani* pozorovani) {
    Ptak** momentalne_posledni_ptak = &(pozorovani->prvni_ptak);

    while (*momentalne_posledni_ptak != NULL) {
        Ptak* deref = *momentalne_posledni_ptak;
        momentalne_posledni_ptak = &(deref->dalsi_ptak);
    }

    return momentalne_posledni_ptak;
}

void smazat_pozorovani(Pozorovani* pozorovani) {
    Ptak* prvni_ptak = pozorovani->prvni_ptak;

    while(prvni_ptak != NULL) {
        Ptak* tmp = prvni_ptak->dalsi_ptak;
        smazat_ptaka(prvni_ptak);
        prvni_ptak = tmp;
    }

    smazat_datum(pozorovani->datum_pozorovani);
    free(pozorovani->poloha);
    free(pozorovani->poznamka);
    free(pozorovani);
}