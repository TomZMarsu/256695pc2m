#include "nacitacdat.h"

Pozorovani* nacist_pozorovani(char* nazev_souboru) {
    FILE *soubor = fopen(nazev_souboru, "r");
    Pozorovani* nactene_pozorovani = (Pozorovani*) malloc(sizeof(Pozorovani));
    nactene_pozorovani->datum_pozorovani = (Datum*) malloc(sizeof(Datum));

    // Nastavovani nulovych hodnot
    nactene_pozorovani->poloha = "";
    nactene_pozorovani->poznamka = "";
    nactene_pozorovani->prvni_ptak = NULL;
    nactene_pozorovani->datum_pozorovani->den = 0;
    nactene_pozorovani->datum_pozorovani->mesic = 0;
    nactene_pozorovani->datum_pozorovani->rok = 0;
    nactene_pozorovani->datum_pozorovani->hodiny = 0;
    nactene_pozorovani->datum_pozorovani->minuty = 0;


    if (soubor == NULL) {
        printf("CHYBA! SOUBOR \"%s\" NELZE OTEVŘÍT\n", nazev_souboru);

        free(nactene_pozorovani->datum_pozorovani);
        free(nactene_pozorovani);
        return NULL;
    }

    // Proměnné pro čtení řádku
    char radek[256] = {0};

    // Kontrola spravneho typu souboru
    fgets(radek, 256, soubor);
    radek[strcspn(radek, "\n")] = 0; //Odstraneni znaku noveho radku

    if (strcmp(radek,"POZOROVANI STRUKTURA")) {
        printf("CHYBA! SOUBOR \"%s\" NENI PLATNYM SOUBOREM S POZOROVANIM\nPRECTENO \"%s\"", nazev_souboru, radek);

        free(nactene_pozorovani->datum_pozorovani);
        free(nactene_pozorovani);
        fclose(soubor);
        return NULL;
    }

    // Nacteni hlavicek
    fgets(radek, sizeof(radek), soubor);
    radek[strcspn(radek, "\n")] = 0; //Odstraneni znaku noveho radku

    while (strcmp(radek, "KONEC HLAVICEK") != 0) {
        int delka_radku = strlen(radek);
        
        // Kopie pro vyhledávání
        char* radek_kopie = (char*) calloc(delka_radku + 1, sizeof(char));
        strncpy(radek_kopie, radek, delka_radku);

        // Pracovni retezec
        char* kontext = NULL;

        // Nactene slova
        // Prvni slovo: definice
        char* definice =  strtok_r (radek_kopie, " ", &kontext);

        if (definice == NULL || kontext == NULL) {
            fgets(radek, sizeof(radek), soubor);
            radek[strcspn(radek, "\n")] = 0; //Odstraneni znaku noveho radku

            continue;
        }

        // Hlednání patřičné definice
        if (!strcmp(definice, "poloha")) {
            // Zkopirovani retezce pro ulozeni do struktury
            unsigned int delka_kontextu = strlen(kontext);
            char* kontext_kopie = (char*) calloc(delka_kontextu + 1, sizeof(char));
            strncpy(kontext_kopie, kontext, delka_kontextu);

            nactene_pozorovani->poloha = kontext_kopie;
        } else if (!strcmp(definice, "poznamka")) {
            // Zkopirovani retezce pro ulozeni do struktury
            unsigned int delka_kontextu = strlen(kontext);
            char* kontext_kopie = (char*) calloc(delka_kontextu + 1, sizeof(char));
            strncpy(kontext_kopie, kontext, delka_kontextu);

            nactene_pozorovani->poznamka = kontext_kopie;
        } else if (!strcmp(definice, "datum")) {
            sscanf(kontext, "%u %u %u %u %u",
                &(nactene_pozorovani->datum_pozorovani->den),
                &(nactene_pozorovani->datum_pozorovani->mesic),
                &(nactene_pozorovani->datum_pozorovani->rok),
                &(nactene_pozorovani->datum_pozorovani->hodiny),
                &(nactene_pozorovani->datum_pozorovani->minuty)
            );
        }

        free(radek_kopie);
        fgets(radek, sizeof(radek), soubor);
        radek[strcspn(radek, "\n")] = 0; //Odstraneni znaku noveho radku
    }

    return nactene_pozorovani;
    fclose(soubor);

}