#include "pozorovani.h"

Pozorovani* pozorovani_init() {
    Pozorovani* pozorovani = (Pozorovani*) malloc(sizeof(Pozorovani));
    pozorovani->datum_pozorovani = datum_init();
    pozorovani->poloha = NULL;
    pozorovani->poznamka = NULL;
    pozorovani->prvni_ptak = NULL;
    pozorovani->dalsi_pozorovani = NULL;
    pozorovani->ID = 0;

    kopirovat_string(&(pozorovani->poloha), "");
    kopirovat_string(&(pozorovani->poznamka), "");

    return pozorovani;
}

Ptak** posledni_ptak_v_pozorovani(Pozorovani* pozorovani) {
    Ptak** momentalne_posledni_ptak = &(pozorovani->prvni_ptak);

    while (*momentalne_posledni_ptak != NULL) {
        momentalne_posledni_ptak = &((*momentalne_posledni_ptak)->dalsi_ptak);
    }

    return momentalne_posledni_ptak;
}

Pozorovani** posledni_pozorovani_v_seznamu(Pozorovani* prvni_pozorovani) {
    Pozorovani** momentalni_pozorovani = &(prvni_pozorovani);

    while (*momentalni_pozorovani != NULL) {
        momentalni_pozorovani = &((*momentalni_pozorovani)->dalsi_pozorovani);
    }

    return momentalni_pozorovani;
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

void smazat_seznam_pozorovani(Pozorovani* prvni_pozorovani) {
    Pozorovani* momentalni_pozorovani = prvni_pozorovani;

    while (momentalni_pozorovani != NULL) {
        Pozorovani* tmp = momentalni_pozorovani;
        momentalni_pozorovani = momentalni_pozorovani->dalsi_pozorovani;
        smazat_pozorovani(tmp);
        tmp = NULL;
    }
}