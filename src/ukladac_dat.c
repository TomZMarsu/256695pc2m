#include "ukladac_dat.h"

void uloz_pozorovani(Pozorovani* pozorovani) {
    char* nazev_souboru = calloc(40, sizeof(char));

    // Formátování názvu souboru (časová známka)
    sprintf(nazev_souboru, "%s.poz", pozorovani->casova_znamka);

    // Kontrola existence souboru a vule zapisovat nove data
    FILE* soubor = fopen(nazev_souboru, "r");

    if (soubor != NULL && !(pozorovani->doslo_k_zmene)) {
        fclose(soubor);
        return;
    }
    if (soubor != NULL) fclose(soubor);
    

    // Zapis hlavicky
    soubor = fopen(nazev_souboru, "w");

    fprintf(soubor, "POZOROVANI STRUKTURA\n\n");
    fprintf(soubor, "datum %02d %02d %04d %02d %02d\n", 
        pozorovani->datum_pozorovani->den,
        pozorovani->datum_pozorovani->mesic,
        pozorovani->datum_pozorovani->rok,
        pozorovani->datum_pozorovani->den,
        pozorovani->datum_pozorovani->minuty
    );
    fprintf(soubor, "poznamka %s\n", pozorovani->poznamka);
    fprintf(soubor, "poloha %s\n\n", pozorovani->poloha);

    fprintf(soubor, "KONEC HLAVICEK\n\n");

    // Vypisovani ptaku
    Ptak* momentalni_ptak = pozorovani->prvni_ptak;
    
    while(momentalni_ptak) {
        fprintf(soubor, "PTAK\n");
        fprintf(soubor, "druh %s\n", momentalni_ptak->nazev);
        fprintf(soubor, "pocet %d\n", momentalni_ptak->pocet_nalezu);
        fprintf(soubor, "poznamka %s\n", momentalni_ptak->poznamky);
        fprintf(soubor, "KONEC PTAKA\n\n");

        momentalni_ptak = momentalni_ptak->dalsi_ptak;
    }

    fclose(soubor);
    free(nazev_souboru);
}