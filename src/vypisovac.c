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
int vypis_tabulku_z_pozorovani(Pozorovani *pozorovani, int stranka, int pocet_ptaku_i) {
    const char SLOUPEC_ID[] = "ID";
    const char SLOUPEC_DRUH[] = "DRUH";
    const char SLOUPEC_POCET[] = "POCET";
    const char SLOUPEC_POZNAMKA[] = "POZNAMKA";
    const char DELIC[] = "=========================";

    // Načtení výšky terminalu
    int vyska_terminalu = 0;
    ziskej_velikost_terminalu(&vyska_terminalu);
    int max_polozek = vyska_terminalu-REZERVACE_RADKU_OPZ;
    int pocet_stranek = (pocet_ptaku_i-1) / max_polozek + 1; // -1 je korekce, aby nevznikla prazdna strana

    printf("%s%02d/%02d%s\n", 
        DELIC, 
        stranka+1,
        pocet_stranek,
        DELIC
    );

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
        printf("%s=====%s\n", DELIC, DELIC);
        return pocet_radku+3;
    }

    Ptak* nacteny_ptak = pozorovani->prvni_ptak;
    
    // Nalistovani na danou stranku
    for (int i = 0; i < max_polozek*stranka; i++) {
        if (nacteny_ptak) nacteny_ptak->ID = NEVYKRESLENA_POLOZKA_ID; // ZABRANENÍ NECHTENE MANIPULACE

        nacteny_ptak = nacteny_ptak->dalsi_ptak;

        if (nacteny_ptak == NULL) break;
    }

    unsigned int ID_pro_ptaka = 1;

    while (nacteny_ptak && ID_pro_ptaka <= max_polozek) {
        nacteny_ptak->ID = ID_pro_ptaka;
        ID_pro_ptaka++;

        printf("%3d %-20s %5d %s\n", 
            nacteny_ptak->ID, 
            nacteny_ptak->nazev, 
            nacteny_ptak->pocet_nalezu, 
            nacteny_ptak->poznamky
        );
        pocet_radku++;

        nacteny_ptak = nacteny_ptak->dalsi_ptak;
    }

    // Nastavení ochranného ID pro nevykreslene nasledujici stranky
    while (nacteny_ptak) {
        nacteny_ptak->ID = NEVYKRESLENA_POLOZKA_ID;
        nacteny_ptak = nacteny_ptak->dalsi_ptak;
    }

    printf("%s=====%s\n", DELIC, DELIC);

    return pocet_radku;
}

int vypis_tabulku_seznamu_pozorovani(Pozorovani* prvni_pozorovani, int stranka, int pocet_pozorovani_i) {
    const char SLOUPEC_ID[] = "ID";
    const char SLOUPEC_DATUM[] = "DATUM";
    const char SLOUPEC_MISTO[] = "MISTO";
    const char SLOUPEC_POZNAMKA[] = "POZNAMKA";
    const char DELIC[] = "=========================";

     // Načtení výšky terminalu
    int vyska_terminalu = 0;
    ziskej_velikost_terminalu(&vyska_terminalu);
    int max_polozek = vyska_terminalu-REZERVACE_RADKU_OPSZ;
    int pocet_stranek = (pocet_pozorovani_i-1) / max_polozek + 1; // -1 je korekce, aby nevznikla prazdna strana

    printf("%s%02d/%02d%s\n", 
        DELIC, 
        stranka+1,
        pocet_stranek,
        DELIC
    );

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
        printf("%s=====%s\n", DELIC, DELIC);
        return pocet_radku+3;
    }

    Pozorovani* momentalni_pozorovani = prvni_pozorovani;

    // Nalistovani na danou stranku
    for (int i = 0; i < max_polozek*stranka; i++) {
        if (momentalni_pozorovani) momentalni_pozorovani->ID = NEVYKRESLENA_POLOZKA_ID; // ZABRANENÍ NECHTENE MANIPULACE

        momentalni_pozorovani = momentalni_pozorovani->dalsi_pozorovani;

        if (momentalni_pozorovani == NULL) break;
    }

    unsigned int ID_pro_pozorovani = 1;

    while (momentalni_pozorovani && ID_pro_pozorovani <= max_polozek) {
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

    // Nastavení ochranného ID pro nevykreslene nasledujici stranky
    while (momentalni_pozorovani) {
        momentalni_pozorovani->ID = NEVYKRESLENA_POLOZKA_ID;
        momentalni_pozorovani = momentalni_pozorovani->dalsi_pozorovani;
    }

    printf("%s=====%s\n", DELIC, DELIC);

    return pocet_radku;
}