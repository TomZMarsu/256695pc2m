#include "ovladac_pozorovani.h"

Pozorovani* vykreslovat_pozorovani(Pozorovani* pozorovani_arg) {
    Pozorovani* pozorovani = pozorovani_arg;

    if (!pozorovani) pozorovani = pozorovani_init();

    bool vypisovani_bezi = true;
    
    // Momentalni stranka pro ucely listovani
    int stranka = 0;
    int max_stranek = 0;

    while(vypisovani_bezi) {
        VYCISTI_OBRAZOVKU();

        // Pocet radku pro system mazani radku. Zacina na sedmi, kvůli nasledně vypsané hlavičce
        int pocet_radku = 6;
        printf("------------------UDAJE O POZOROVANI------------------------\n");
        printf("Datum: %s\n", datum_na_string(pozorovani->datum_pozorovani));
        printf("Misto pozorovani: %s\n", pozorovani->poloha);
        printf("Poznamky: \n%s\n", pozorovani->poznamka);
        printf("------------------------------------------------------------\n");


        // Načtení výšky terminalu
        int vyska_terminalu = 0;
        ziskej_velikost_terminalu(&vyska_terminalu);
        int max_polozek = vyska_terminalu-REZERVACE_RADKU_OPZ;
        int pocet_ptaku_i = pocet_ptaku(pozorovani->prvni_ptak);
        int max_stranek = (pocet_ptaku_i-1) / max_polozek; // -1 je korekce, aby nevznikla prazdna strana

        if (stranka < 0) stranka = 0;
        if (stranka > max_stranek) stranka = max_stranek;

        // Vykresleni pozorovani
        pocet_radku += vypis_tabulku_z_pozorovani(pozorovani, stranka, pocet_ptaku_i) + 1;
        printf("\n");
        
        // Ziskani vstupu od uzivatele
        bool vstup_ziskan = false;
        while(!vstup_ziskan) {
            // Vypis moznosti
            printf("NABIDKA:\n");
            printf(" (1) Pridat ptaka\n");
            printf(" (2) Upravit ptaka\n");
            printf(" (3) Odstranit ptaka\n");
            printf(" (4) Upravit udaje o pozorovani\n");
            printf(" (5) Vratit se zpet do nabidky\n");
            printf(" (6) Seradit\n");
            printf(" (7) Ukoncit program\n");
            printf("\n (11) <-- STRANKA --> (22)\n");
            pocet_radku += OPZ_VELIKOST_NABIDKY;

            switch (nacti_int_od_uzivatele("Vase volba", true))
            {
            case OPZ_PRIDAT_PTAKA:
                vstup_ziskan = true;
                pozorovani->doslo_k_zmene = true;

                Ptak* novy_ptak = opz_pridat_ptaka();
                Ptak** posledni_ptak = posledni_ptak_v_pozorovani(pozorovani);

                *(posledni_ptak) = novy_ptak;
                pocet_radku -= OPZ_VELIKOST_NABIDKY;
                break;

            case OPZ_UPRAVIT_PTAKA:
                pozorovani->doslo_k_zmene = true;
                vstup_ziskan = opz_upravit_ptaka(&pozorovani);
                pocet_radku -= OPZ_VELIKOST_NABIDKY;
                break;
            
            case OPZ_ODSTRANIT_PTAKA:
                pozorovani->doslo_k_zmene = true;
                vstup_ziskan = opz_odstranit_ptaka(&pozorovani);
                pocet_radku -= OPZ_VELIKOST_NABIDKY;
                break;

            case OPZ_UPRAVIT_POZOROVANI:
                pozorovani->doslo_k_zmene = true;
                vstup_ziskan = opz_upravit_udaje_o_pozorovani(pozorovani);
                pocet_radku -= OPZ_VELIKOST_NABIDKY;
                break;

            case OPZ_SERADIT:
                vstup_ziskan = opz_seradit(pozorovani);
                break;

            case OPZ_VRATIT_SE_ZPET:
                vymazat_radek(pocet_radku+1);
                return pozorovani;
                break;
            
            case OPZ_UKONCIT:
                smazat_pozorovani(pozorovani);
                ukoncit_program();
                break;

            case 11:
                if (stranka > 0) stranka--;
                vstup_ziskan = true;
                break;

            case 22:
                if (stranka < max_stranek) stranka++;
                vstup_ziskan = true;
                break;
            
            default:
                vymazat_radek(OPZ_VELIKOST_NABIDKY);
                pocet_radku -= OPZ_VELIKOST_NABIDKY;
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
    nacti_string_od_uzivatele(&(ptak->nazev), "Druh", true);
    ptak->pocet_nalezu = nacti_int_od_uzivatele("Pocet nalezu", true);
    nacti_string_od_uzivatele(&(ptak->poznamky), "Poznamky", true);

    vymazat_radek(3);
    
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

    // Korekce
    vymazat_radek(3);

    return true;
}

bool opz_odstranit_ptaka(Pozorovani** pozorovani_ptr) {
    // Vymazani nabidky
    vymazat_radek(OPZ_VELIKOST_NABIDKY);

    Pozorovani* pozorovani = *pozorovani_ptr;

    int id = nacti_int_od_uzivatele("Zadejte ID ptaka, ktereho chcete odstranit", true);

    // Najdi ptaka s danym ID
    Ptak** momentalni_ptak = &(pozorovani->prvni_ptak);
    Ptak** predchozi_ptak = NULL;
    Ptak** nasledujici_ptak = NULL;
    while (*momentalni_ptak != NULL) {
        if ((*momentalni_ptak)->ID == id-1) predchozi_ptak = momentalni_ptak;
        if ((*momentalni_ptak)->ID == id) break;

        momentalni_ptak = &((*momentalni_ptak)->dalsi_ptak);
    }

    // Pokud je vybrana neplatna polozka, vrat se
    if (*momentalni_ptak == NULL) return false;

    // Nacteni nasledujiciho ptaka
    nasledujici_ptak = &((*momentalni_ptak)->dalsi_ptak);

    // Snímek adresy, která se dealokuje
    Ptak* ptak_na_smazani = *momentalni_ptak;

    // Přelinkovaní seznamu ptáku / vyšoupnutí ptáka z lineárního seznamu
    if (predchozi_ptak == NULL) {
        (*pozorovani_ptr)->prvni_ptak = *nasledujici_ptak;
    } else {
        (*predchozi_ptak)->dalsi_ptak = *nasledujici_ptak;
    }

    // Dealokace v paměti
    smazat_ptaka(ptak_na_smazani);

    // Vymazat radky
    vymazat_radek(1);

    // Odstraneni probehlo zdarne
    return true;
}

bool opz_upravit_udaje_o_pozorovani(Pozorovani* pozorovani) {
    vymazat_radek(OPZ_VELIKOST_NABIDKY);

    printf("\nZadejte nove hodnoty (ponechejte prazdne, pokud nechcete upravovat)\n");
    printf("===========================\n");

    uprav_datum(pozorovani->datum_pozorovani);
    uprav_string("Poloha", &(pozorovani->poloha));
    uprav_string("Poznamky", &(pozorovani->poznamka));

    vymazat_radek(4);

    return true;
}

bool opz_seradit(Pozorovani* pozorovani) {
    // Vypis nabidku tříd
    printf("TRIDIT PODLE:\n");
    printf(" (1) Druh\n");
    printf(" (2) Pocet\n");
    printf(" (3) Poznamka\n");

    Ptak_radici_podminka podminka = nacti_overene_int_od_uzivatele("Vase volba", true, 1, OPZ_VELIKOST_NABIDKY_TRIZENI-1);
    vymazat_radek(OPZ_VELIKOST_NABIDKY_TRIZENI);

    // Vypis smer trizeni
    printf("SMER TRIZENI:\n");
    printf(" (1) Vzestupne (A->Z)\n");
    printf(" (2) Sestupne\n");

    Smer_trizeni smer_trizeni = nacti_overene_int_od_uzivatele("Vase volba", true, 1, OPZ_VELIKOST_NABIDKY_SMERU_TRIZENI-1);
    vymazat_radek(OPZ_VELIKOST_NABIDKY_SMERU_TRIZENI);

    seradit_pozorovani(&(pozorovani->prvni_ptak), podminka, smer_trizeni);

    return true;
}