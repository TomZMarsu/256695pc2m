#include "ptak.h"

Ptak* ptak_init() {
    Ptak* ptak = (Ptak*) malloc(sizeof(Ptak));

    ptak->dalsi_ptak = NULL;
    ptak->ID = 0;
    ptak->pocet_nalezu = 0;

    // Stringy se berou jako dynamicky alokované, aby se zabranilo nedefinovanému chování v případě dealokace
    kopirovat_string(&(ptak->nazev), "NEDEFINOVANY PTAK");
    kopirovat_string(&(ptak->popis_vzhledu), "");
    kopirovat_string(&(ptak->poznamky), "");
    kopirovat_string(&(ptak->vyskyt), "");
    
    return ptak;
}