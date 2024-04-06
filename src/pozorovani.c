#include "pozorovani.h"

Pozorovani* pozorovani_init() {
    Pozorovani* pozorovani = (Pozorovani*) malloc(sizeof(Pozorovani));
    pozorovani->datum_pozorovani = datum_init();
    pozorovani->poloha = "";
    pozorovani->poznamka = "";
    pozorovani->prvni_ptak = NULL;

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