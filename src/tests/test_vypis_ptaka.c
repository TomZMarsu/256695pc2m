#include "datum.h"
#include "ptak.h"
#include "pozorovani.h"
#include "vypisovac.h"

int main() {
    Ptak sykora;
    sykora.nazev = "Sykora konadra";
    sykora.pocet_nalezu = 3;
    sykora.poznamky = "";
    sykora.popis_vzhledu = "Maly ptak. Zlute telo s cernou hlavou a bilimi licy. Modrosede kridla s bilym prouzkem.";
    sykora.vyskyt = "Celorocne";
    sykora.dalsi_ptak = NULL;

    vypis_informace_o_ptakovi(sykora);
    return 0;
}