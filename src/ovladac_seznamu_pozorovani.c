#include "ovladac_seznamu_pozorovani.h"

Pozorovani* vykreslovat_seznam_pozorovani(Pozorovani** main_prvni_pozorovani_ptr) {
    Pozorovani* pozorovani = *main_prvni_pozorovani_ptr;

    bool vypisovani_bezi = true;

    while(vypisovani_bezi) {
        // Pocet radku pro system mazani radku. Zacina na sedmi, kvůli nasledně vypsané hlavičce
        int pocet_radku = 0;

        // Vykresleni pozorovani
        pocet_radku += vypis_tabulku_seznamu_pozorovani(pozorovani) + 1;
        printf("\n");
        
        // Ziskani vstupu od uzivatele
        bool vstup_ziskan = false;
        while(!vstup_ziskan) {
            // Vypis moznosti
            printf("NABIDKA:\n");
            printf(" (1) Nove pozorovani\n");
            printf(" (2) Prejit do pozorovani\n");
            printf(" (3) Odstranit pozorovani\n");
            printf(" (4) Seradit\n");
            printf(" (5) Ukončit program\n");
            pocet_radku += OPSZ_VELIKOST_NABIDKY;

            switch (nacti_int_od_uzivatele("Vase volba", true))
            {
            case OPSZ_NOVE_POZOROVANI:
                vstup_ziskan = true;
                vymazat_radek(pocet_radku-OPSZ_VELIKOST_NABIDKY);
                Pozorovani* nove_pozorovani = opsz_nove_pozorovani();
                Pozorovani** posledni_pozorovani = posledni_pozorovani_v_seznamu(pozorovani);

                if (pozorovani != NULL) {
                    *posledni_pozorovani = nove_pozorovani;
                } else {
                    *main_prvni_pozorovani_ptr = nove_pozorovani;
                    pozorovani = *main_prvni_pozorovani_ptr;
                }
                
                pocet_radku = 0;
                break;

            case OPSZ_PREJIT_DO_POZOROVANI:
                vstup_ziskan = opsz_prejit_do_pozorovani(pozorovani, pocet_radku);
                pocet_radku = 0;
                break;
            
            case OPSZ_ODSTRANIT_POZOROVANI:
                vstup_ziskan = opsz_odstranit_pozorovani(&pozorovani);
                pocet_radku -= OPSZ_VELIKOST_NABIDKY;
                break;

            case OPSZ_SERADIT:
                vstup_ziskan = opsz_seradit(&pozorovani);
                break;
            
            case OPSZ_UKONCIT:
                ukoncit_program();
                break;
            
            default:
                vymazat_radek(OPSZ_VELIKOST_NABIDKY);
                pocet_radku -= OPSZ_VELIKOST_NABIDKY;
                break;
            }
        }
        vymazat_radek(pocet_radku);
    }

    return pozorovani;
}

Pozorovani* opsz_nove_pozorovani() {
    // Vymazani nabidky
    vymazat_radek(OPSZ_VELIKOST_NABIDKY);

    Pozorovani* pozorovani = pozorovani_init();
    nastavit_datum_na_dnes(pozorovani->datum_pozorovani);
    
    // Vyptávaní se na vstup
    printf("Zadejte informace o pozorovani (nebo ponechte prazdne)\n");
    printf("============================\n");
    uprav_datum(pozorovani->datum_pozorovani);
    nacti_string_od_uzivatele(&(pozorovani->poloha), "Misto", true);
    nacti_string_od_uzivatele(&(pozorovani->poznamka), "Poznamky", true);

    vymazat_radek(3);
    
    vykreslovat_pozorovani(pozorovani);

    return pozorovani;
}

bool opsz_prejit_do_pozorovani(Pozorovani* pozorovani, int pocet_radku) {
    // Vymazani nabidky
    vymazat_radek(OPSZ_VELIKOST_NABIDKY);

    int id = nacti_int_od_uzivatele("Zadejte ID pozorovani, ktereho chcete vstoupit", true);

    // Najdi ptaka s danym ID
    Pozorovani* momentalni_pozorovani = pozorovani;
    while (momentalni_pozorovani != NULL) {
        if (momentalni_pozorovani->ID == id) break;

        momentalni_pozorovani = momentalni_pozorovani->dalsi_pozorovani;
    }

    // Pokud je vybrana neplatna polozka, vrat se
    if (momentalni_pozorovani == NULL) return false;

    vymazat_radek(pocet_radku-OPSZ_VELIKOST_NABIDKY+1);
    vykreslovat_pozorovani(momentalni_pozorovani);

    return true;
}

bool opsz_odstranit_pozorovani(Pozorovani** pozorovani_ptr) {
    // Vymazani nabidky
    vymazat_radek(OPSZ_VELIKOST_NABIDKY);

    Pozorovani* pozorovani = *pozorovani_ptr;
    Pozorovani* predchozi_pozorovani = NULL;

    int id = nacti_int_od_uzivatele("Zadejte ID pozorovani, ktereho chcete odstranit", true);

    // Najdi pozorování s daným ID
    while (pozorovani) {
        if (pozorovani->ID == id) break;
        predchozi_pozorovani = pozorovani;
        pozorovani = pozorovani->dalsi_pozorovani;
    }

    // Pokud je vybrana neplatna polozka, vrat se
    if (pozorovani == NULL) return false;

    // Nacteni nasledujiciho pozorovani
    Pozorovani* nasledujici_pozorovani = pozorovani->dalsi_pozorovani;

    // Přelinkovaní seznamu ptáku / vyšoupnutí ptáka z lineárního seznamu
    if (predchozi_pozorovani == NULL) {
        *pozorovani_ptr = nasledujici_pozorovani;
    } else {
        predchozi_pozorovani->dalsi_pozorovani = nasledujici_pozorovani;
    }

    // Dealokace v paměti
    smazat_pozorovani(pozorovani);
    pozorovani = NULL;

    // Vymazat radky
    vymazat_radek(1);

    // Odstraneni probehlo zdarne
    return true;
}

bool opsz_seradit(Pozorovani** pozorovani) {
    // Vypis nabidku tříd
    printf("TRIDIT PODLE:\n");
    printf(" (1) Datum\n");
    printf(" (2) Misto\n");
    printf(" (3) Poznamka\n");

    Pozorovani_radici_podminka podminka = nacti_overene_int_od_uzivatele("Vase volba", true, 1, OPSZ_VELIKOST_NABIDKY_TRIZENI-1);
    vymazat_radek(OPSZ_VELIKOST_NABIDKY_TRIZENI);

    // Vypis smer trizeni
    printf("SMER TRIZENI:\n");
    printf(" (1) Vzestupne (A->Z)\n");
    printf(" (2) Sestupne\n");

    Smer_trizeni smer_trizeni = nacti_overene_int_od_uzivatele("Vase volba", true, 1, OPSZ_VELIKOST_NABIDKY_SMERU_TRIZENI-1);
    vymazat_radek(OPSZ_VELIKOST_NABIDKY_SMERU_TRIZENI);

    seradit_seznam_pozorovani(pozorovani, podminka, smer_trizeni);

    // Korekce
    vymazat_radek(1);

    return true;
}