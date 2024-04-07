#include "vypisovac.h"

// Vraci pocet radku
int vypis_informace_o_ptakovi(Ptak ptak) {
    printf("INFORMACE O PTAKOVI \"%s\":\n", ptak.nazev);
    printf("===============================\n");
    printf("Popis vzhledu: %s\n", ptak.popis_vzhledu);
    printf("Čas výskytu  : %s\n", ptak.vyskyt);
    printf("-------------------------------\n\n");
    
    return 6;

}

// Vraci pocet radku
int vypis_tabulku_z_pozorovani(Pozorovani *pozorovani) {
    const char SLOUPEC_ID[] = "ID";
    const char SLOUPEC_DRUH[] = "DRUH";
    const char SLOUPEC_POCET[] = "POCET";
    const char SLOUPEC_POZNAMKA[] = "POZNAMKA";

    printf("%3s %-20s %5s %s\n", 
        SLOUPEC_ID,
        SLOUPEC_DRUH, 
        SLOUPEC_POCET, 
        SLOUPEC_POZNAMKA
    );

    int pocet_radku = 1;
    
    // Jestliže není žádný pták v pozorovaní, vypis pouze hlavicky a dal nepokracuj
    if (pozorovani->prvni_ptak == NULL) {
        printf("    -ZADNY PTAK V SEZNAMU-\n");
        return pocet_radku+1;
    }

    Ptak* nacteny_ptak = pozorovani->prvni_ptak;
    unsigned int ID_pro_ptaka = 1;

    bool byl_nacten_posledni_ptak = false;
    while (!byl_nacten_posledni_ptak) {
        nacteny_ptak->ID = ID_pro_ptaka;
        ID_pro_ptaka++;

        printf("%3d %-20s %5d %s\n", 
            nacteny_ptak->ID, 
            nacteny_ptak->nazev, 
            nacteny_ptak->pocet_nalezu, 
            nacteny_ptak->poznamky
        );
        pocet_radku++;

        if (nacteny_ptak->dalsi_ptak == NULL) {
            byl_nacten_posledni_ptak = true;
            break;
        }

        nacteny_ptak = nacteny_ptak->dalsi_ptak;
    }

    return pocet_radku;
}