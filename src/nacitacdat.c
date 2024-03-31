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
            /*
            unsigned int delka_kontextu = strlen(kontext);
            char* kontext_kopie = (char*) calloc(delka_kontextu + 1, sizeof(char));
            strncpy(kontext_kopie, kontext, delka_kontextu);
            */
            kopirovat_string(&(nactene_pozorovani->poloha), kontext);
        } else if (!strcmp(definice, "poznamka")) {
            kopirovat_string(&(nactene_pozorovani->poznamka), kontext);
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

    // Pro případ krátké souborové struktury vrať předčasně
    if (feof(soubor)) {
        fclose(soubor);
        return nactene_pozorovani;
    }

    // Načtení jednotlivých ptáků
    bool priznak_sken_ptaka = false; // Příznak, že při čtení řádků byla nalezena struktura ptáka
    Ptak** ukazatel_posledni_ptak = &(nactene_pozorovani->prvni_ptak);
    Ptak* novy_ptak = NULL;
    
    while(!feof(soubor)) {
        fgets(radek, sizeof(radek), soubor);
        radek[strcspn(radek, "\n")] = 0; //Odstraneni znaku noveho radku
        
        // NALEZ POCATKU STRUKTURY PTAKA
        if (!strcmp(radek, "PTAK")) {
            priznak_sken_ptaka = true;

            // Inicializace ptáka
            novy_ptak = (Ptak*) malloc(sizeof(Ptak));
            novy_ptak->nazev = "";
            novy_ptak->ID = 0;
            novy_ptak->pocet_nalezu = 0;
            novy_ptak->popis_vzhledu = "";
            novy_ptak->poznamky = "";
            novy_ptak->vyskyt = ""; 

            continue;
        }

        // NALEZ PRIZNAKU KONCE STRUKTURY PTÁKA (uložení ptáka na konec lineárního seznamu ptáků)
        if (!strcmp(radek, "KONEC PTAKA")) {
            priznak_sken_ptaka = false;

            *ukazatel_posledni_ptak = novy_ptak;
            ukazatel_posledni_ptak = &(novy_ptak->dalsi_ptak);
            *ukazatel_posledni_ptak = NULL;
            novy_ptak = NULL;

            continue;
        }

        // NACTENI SLOVA
        int delka_radku = strlen(radek);

        // Kopie pro vyhledávání
        char* radek_kopie = (char*) calloc(delka_radku + 1, sizeof(char));
        strncpy(radek_kopie, radek, delka_radku);

        // Pracovni retezec
        char* kontext = NULL;

        // Nactene slova
        // Prvni slovo: definice
        char* definice =  strtok_r (radek_kopie, " ", &kontext);

        if (definice == NULL) {
            continue;
        }

        // DEFINICE: druh <nazev druhu: char*>
        if(!strcmp(definice, "druh") && priznak_sken_ptaka) {
            kopirovat_string(&(novy_ptak->nazev), kontext);
        // DEFINICE: poznamka <poznamka: char*>
        } else if (!strcmp(definice, "poznamka") && priznak_sken_ptaka) {
            kopirovat_string(&(novy_ptak->poznamky), kontext);
        // DEFINICE: pocet <pocet: unsigned short int>
        } else if (!strcmp(definice, "pocet") && priznak_sken_ptaka) {
            sscanf(kontext, "%u %u %u %u %u", &(novy_ptak->pocet_nalezu));
        }

        // Uvolnění místa v paměti pro načtený řádek
        free(radek_kopie);
    }

    // Vycisteni od nenactenych ptaku
    if (novy_ptak != NULL) {
        free(novy_ptak);
    }

    fclose(soubor);
    return nactene_pozorovani;
    

}