#include "datum.h"
#include "ptak.h"
#include "pozorovani.h"
#include "vypisovac.h"

int main() {
    Ptak sykora;
    sykora.nazev = "Sykora konadra";
    sykora.pocet_nalezu = 3;
    sykora.poznamky = "";
    sykora.dalsi_ptak = NULL;

    Ptak straka;
    straka.nazev = "Straka obecna";
    straka.pocet_nalezu = 1;
    straka.poznamky = "Poletovala okolo";
    straka.dalsi_ptak = &sykora;

    Ptak havran;
    havran.nazev = "Havran polni";
    havran.pocet_nalezu = 24;
    havran.poznamky = "";
    havran.dalsi_ptak = &straka;

    Pozorovani dnes;
    Datum dnesni_datum;
    dnesni_datum.den = 5;
    dnesni_datum.hodiny = 20;
    dnesni_datum.minuty = 5;
    dnesni_datum.rok = 2024;
    dnesni_datum.mesic = 7;

    dnes.datum_pozorovani = &dnesni_datum;
    dnes.poloha = "Bukovec";
    dnes.poznamka = "Vetrno";
    dnes.prvni_ptak = &havran;

    vypis_tabulku_z_pozorovani(&dnes);
    return 0;
}