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
    const char DELIC[] = "============================================================\n";
    printf("%s", DELIC);
    printf("%3s %-20s %5s %s\n", 
        SLOUPEC_ID,
        SLOUPEC_DRUH, 
        SLOUPEC_POCET, 
        SLOUPEC_POZNAMKA
    );

    int pocet_radku = 2;
    
    // Jestliže není žádný pták v pozorovaní, vypis pouze hlavicky a dal nepokracuj
    if (pozorovani->prvni_ptak == NULL) {
        printf("\n        -ZADNY PTAK V SEZNAMU-\n\n");
        printf("%s", DELIC);
        return pocet_radku+3;
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

    printf("%s", DELIC);

    return pocet_radku;
}

int vypis_tabulku_seznamu_pozorovani(Pozorovani* prvni_pozorovani) {
    const char SLOUPEC_ID[] = "ID";
    const char SLOUPEC_DATUM[] = "DATUM";
    const char SLOUPEC_MISTO[] = "MISTO";
    const char SLOUPEC_POZNAMKA[] = "POZNAMKA";
    const char DELIC[] = "============================================================\n";
    printf("%s", DELIC);
    printf("%3s %-18s %-15s %s\n", 
        SLOUPEC_ID,
        SLOUPEC_DATUM, 
        SLOUPEC_MISTO, 
        SLOUPEC_POZNAMKA
    );

    int pocet_radku = 2;
    
    // Jestliže není žádný pták v pozorovaní, vypis pouze hlavicky a dal nepokracuj
    if (prvni_pozorovani == NULL) {
        printf("\n        -ZADNE POZOROVANI V SEZNAMU-\n\n");
        printf("%s", DELIC);
        return pocet_radku+3;
    }

    Pozorovani* momentalni_pozorovani = prvni_pozorovani;
    unsigned int ID_pro_pozorovani = 1;

    while (momentalni_pozorovani) {
        momentalni_pozorovani->ID = ID_pro_pozorovani;
        ID_pro_pozorovani++;

        printf("%3d %-18s %-15s %s\n", 
            momentalni_pozorovani->ID, 
            momentalni_pozorovani->datum_pozorovani->textova_reprezentace, 
            momentalni_pozorovani->poloha, 
            momentalni_pozorovani->poznamka
        );
        pocet_radku++;

        momentalni_pozorovani = momentalni_pozorovani->dalsi_pozorovani;
    }

    printf("%s", DELIC);

    return pocet_radku;
}