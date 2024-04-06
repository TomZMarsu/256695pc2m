#include "ptak.h"

Ptak* ptak_init() {
    Ptak* ptak = (Ptak*) malloc(sizeof(Ptak));
    ptak->dalsi_ptak = NULL;
    ptak->ID = 0;
    ptak->nazev = "NEDEFINOVANY PTAK";
    ptak->pocet_nalezu = 0;
    ptak->popis_vzhledu = "";
    ptak->poznamky = "";
    ptak->poznamky = "";
    ptak->vyskyt = "";
    
    return ptak;
}