#include "nacitacdat.h"
#include "ptak.h"
#include <string.h>
#include <stdbool.h>

bool overit_ptaka(Ptak ptak, Ptak kontrolni_ptak) {
    if (strcmp(ptak.nazev, kontrolni_ptak.nazev)) {
        perror("PTAK NEMÁ SOUHLASNÝ NÁZEV");
        printf("Ocekavano: \"%s\"\n", kontrolni_ptak.nazev);
        printf("Nalezeno: \"%s\"\n", ptak.nazev);
        return false;
    }

    if (strcmp(ptak.poznamky, kontrolni_ptak.poznamky)) {
        perror("PTAK NEMÁ SOUHLASNOU POZNÁMKU");
        printf("Ocekavano: \"%s\"\n", kontrolni_ptak.poznamky);
        printf("Nalezeno: \"%s\"\n", ptak.poznamky);
        return false;
    }

    if (ptak.pocet_nalezu != kontrolni_ptak.pocet_nalezu) {
        perror("PTAK NEMÁ SOUHLASNÝ POČET NÁLEZŮ");
        printf("Ocekavano: %u\n", kontrolni_ptak.pocet_nalezu);
        printf("Nalezeno: %u\n", ptak.pocet_nalezu);
        return false;
    }
    
    return true;
}

int main() {
    Pozorovani* nactene_pozorovani = nacist_pozorovani("./tests/test_nacteni_pozorovani/pozorovani_cele1.dat");

    if (nactene_pozorovani == NULL) {
        perror("CHYBA PRI PRACI SE SOUBOREM");
        return 1;
    }

    // Kontrola data
    if (nactene_pozorovani->datum_pozorovani->den != 10) {
        perror("NACTENE DATUM NESOUHLASI (OCEKAVANO: DEN=10)");
        printf("NACTENO: DEN=%u\n", nactene_pozorovani->datum_pozorovani->den);
        return 2;
    }

    if (nactene_pozorovani->datum_pozorovani->mesic != 6) {
        perror("NACTENE DATUM NESOUHLASI (OCEKAVANO: MESIC=6)");
        printf("NACTENO: MESIC=%u\n", nactene_pozorovani->datum_pozorovani->mesic);
        return 3;
    }

    if (nactene_pozorovani->datum_pozorovani->rok != 2003) {
        perror("NACTENE DATUM NESOUHLASI (OCEKAVANO: ROK=2003)");
        printf("NACTENO: ROK=%u\n", nactene_pozorovani->datum_pozorovani->rok);
        return 4;
    }

    if (nactene_pozorovani->datum_pozorovani->hodiny != 20) {
        perror("NACTENE DATUM NESOUHLASI (OCEKAVANO: HODINY=20)");
        printf("NACTENO: HODINY=%u\n", nactene_pozorovani->datum_pozorovani->hodiny);
        return 5;
    }

    if (nactene_pozorovani->datum_pozorovani->minuty != 1) {
        perror("NACTENE DATUM NESOUHLASI (OCEKAVANO: MINUTY=1)");
        printf("NACTENO: MINUTY=%u\n", nactene_pozorovani->datum_pozorovani->minuty);
        return 6;
    }

    // Kontrola poznamky
    if (strcmp(nactene_pozorovani->poznamka, "nejaka poznamka")) {
        perror("NACTENA POZNAMKA NESOUHLASI (OCEKAVANO: \"nejaka poznamka\")");
        printf("NACTENO: %s\n", nactene_pozorovani->poznamka);
        return 7;
    }

    // Kontrola polohy
    if (strcmp(nactene_pozorovani->poloha, "Frydek-Mistek, v parku u magistratu")) {
        perror("NACTENA POLOHA NESOUHLASI (OCEKAVANO: \"Frydek-Mistek, v parku u magistratu\")");
        printf("NACTENO: %s\n", nactene_pozorovani->poloha);
        return 8;
    }

    // Nacteni ptaku
    Ptak sykora;
    Ptak strakapoud;
    Ptak vrabec;
    Ptak orel;
    Ptak kos;

    // NASTAVENÍ: Sýkora
    sykora.nazev = "Sykora konadra";
    sykora.pocet_nalezu = 2;
    sykora.poznamky = "Krmili se na krmitku";
    sykora.dalsi_ptak = &strakapoud;

    // NASTAVENÍ: Strakapoud
    strakapoud.nazev = "Strakapoud velky";
    strakapoud.pocet_nalezu = 1;
    strakapoud.poznamky = "";
    strakapoud.dalsi_ptak = &vrabec;

    // NASTAVENÍ: Vrabec
    vrabec.nazev = "Vrabec domaci";
    vrabec.pocet_nalezu = 10;
    vrabec.poznamky = "";
    vrabec.dalsi_ptak = &orel;

    // NASTAVENÍ: Orel
    orel.nazev = "Orel skalni";
    orel.pocet_nalezu = 1;
    orel.poznamky = "Fascinujici, ale nevim, co tady dela";
    orel.dalsi_ptak = &kos;

    // NASTAVENI: Kos
    kos.nazev = "Kos cerny";
    kos.pocet_nalezu = 0;
    kos.poznamky = "";
    kos.dalsi_ptak = NULL;

    

    // OVEROVANI
    Ptak nactena_sykora = *(nactene_pozorovani->prvni_ptak);
    if (!overit_ptaka(nactena_sykora, sykora)) return 9;

    Ptak nacteny_strakapoud = *(nactena_sykora.dalsi_ptak);
    if (!overit_ptaka(nacteny_strakapoud, strakapoud)) return 10;

    Ptak nacteny_vrabec = *(nacteny_strakapoud.dalsi_ptak);
    if (!overit_ptaka(nacteny_vrabec, vrabec)) return 11;

    Ptak nacteny_orel = *(nacteny_vrabec.dalsi_ptak);
    if (!overit_ptaka(nacteny_orel, orel)) return 12;

    Ptak nacteny_kos = *(nacteny_orel.dalsi_ptak);
    if (!overit_ptaka(nacteny_kos, kos)) return 13;

    if (nacteny_kos.dalsi_ptak != NULL) {
        perror("POSLEDNI POLOZKA NEMA NULOVOU HODNOTU");
        return 14;
    }

    return 0;
}