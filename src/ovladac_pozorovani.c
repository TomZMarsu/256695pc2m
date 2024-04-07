#include "ovladac_pozorovani.h"

Pozorovani* vykreslovat_pozorovani_novy() {
    Pozorovani* pozorovani = pozorovani_init();
    bool vypisovani_bezi = true;

    while(vypisovani_bezi) {
        int pocet_radku = 0;
        // Vykresleni pozorovani
        pocet_radku += vypis_tabulku_z_pozorovani(pozorovani);

        // Vypis moznosti
        printf("\nNABIDKA:\n");
        printf(" (1) Pridat ptaka\n");
        printf(" (2) Upravit ptaka\n");
        printf(" (3) Odstranit ptaka\n");
        printf(" (4) Upravit udaje o pozorovani\n");
        pocet_radku += OPZ_VELIKOST_NABIDKY+1;
        
        // Ziskani vstupu od uzivatele
        bool vstup_ziskan = false;
        while(!vstup_ziskan) {
            switch (nacti_int_od_uzivatele("Vase volba", true))
            {
            case 1:
                vstup_ziskan = true;
                Ptak* novy_ptak = opz_pridat_ptaka();
                Ptak** posledni_ptak = posledni_ptak_v_pozorovani(pozorovani);

                *(posledni_ptak) = novy_ptak;
                pocet_radku -= OPZ_VELIKOST_NABIDKY;
                break;

            case 2:
                vstup_ziskan = opz_upravit_ptaka(&pozorovani);
                pocet_radku -= OPZ_VELIKOST_NABIDKY;
                break;
            
            case 3:
                vstup_ziskan = true;
                break;

            case 4:
                vstup_ziskan = true;
                break;
            
            default:
                break;
            }
        }

        vymazat_radek(pocet_radku);
    }

    return pozorovani;
}

Ptak* opz_pridat_ptaka() {
    Ptak* ptak = ptak_init();

    // Vymazani nabidky
    vymazat_radek(OPZ_VELIKOST_NABIDKY);
    
    // Vyptávaní se na vstup
    printf("Zadejte informace o ptakovi\n");
    printf("============================\n");
    ptak->nazev = nacti_string_od_uzivatele("Druh", false);
    ptak->pocet_nalezu = nacti_int_od_uzivatele("Pocet nalezu", false);
    ptak->poznamky = nacti_string_od_uzivatele("Poznamky", false);

    vymazat_radek(5);
    
    return ptak;
}

bool opz_upravit_ptaka(Pozorovani** pozorovani_ptr) {
    // Vymazani nabidky
    vymazat_radek(OPZ_VELIKOST_NABIDKY);

    Pozorovani* pozorovani = *pozorovani_ptr;

    int id = nacti_int_od_uzivatele("Zadejte ID ptaka, ktereho chcete upravit", true);

    // Najdi ptaka s danym ID
    Ptak** momentalni_ptak = &(pozorovani->prvni_ptak);
    while (*momentalni_ptak != NULL) {
        Ptak* deref = *momentalni_ptak;
        if (deref->ID == id) break;

        momentalni_ptak = &(deref->dalsi_ptak);
    }

    // Pokud je vybrana neplatna polozka, vrat se
    if (*momentalni_ptak == NULL) return false;

    // Pokud je vybrana polozka platna, pokracuj
    Ptak* vybrany_ptak = *momentalni_ptak;

    printf("Zadejte nove hodnoty (ponechejte prazdne, pokud nechcete upravovat)\n");
    printf("===========================\n");

    // Uprava NAZVU
    uprav_string("Druh", &(vybrany_ptak->nazev));
    uprav_int("Pocet", &(vybrany_ptak->pocet_nalezu));
    uprav_string("Poznamka", &(vybrany_ptak->poznamky));

    vymazat_radek(5);
    return true;
}