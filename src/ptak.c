#include "ptak.h"

Ptak* ptak_init() {
    Ptak* ptak = malloc(sizeof(Ptak));

    ptak->dalsi_ptak = NULL;
    ptak->ID = 0;
    ptak->pocet_nalezu = 0;

    ptak->nazev = NULL;
    ptak->popis_vzhledu = NULL;
    ptak->poznamky = NULL;
    ptak->vyskyt = NULL;

    // Stringy se berou jako dynamicky alokované, aby se zabranilo nedefinovanému chování v případě dealokace
    kopirovat_string(&(ptak->nazev), "NEDEFINOVANY PTAK");
    kopirovat_string(&(ptak->popis_vzhledu), "");
    kopirovat_string(&(ptak->poznamky), "");
    kopirovat_string(&(ptak->vyskyt), "");
    
    return ptak;
}

void smazat_ptaka(Ptak* ptak) {
    free(ptak->nazev);
    ptak->nazev = NULL;
    free(ptak->popis_vzhledu);
    ptak->popis_vzhledu = NULL;
    free(ptak->poznamky);
    ptak->poznamky = NULL;
    free(ptak->vyskyt);
    ptak->vyskyt = NULL;
    free(ptak);
    ptak=NULL;
}