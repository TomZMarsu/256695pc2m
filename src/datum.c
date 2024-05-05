#include "datum.h"

// String musí mít alespoň 18 znaků
char* datum_na_string(Datum* datum) {
    sprintf(datum->textova_reprezentace, "%02u.%02u.%04u %02u:%02u", 
        datum->den,
        datum->mesic,
        datum->rok,
        datum->hodiny,
        datum->minuty
    );

    return datum->textova_reprezentace;
}

Datum* datum_init() {
    Datum* datum = (Datum*) malloc(sizeof(Datum));
    datum->den = (unsigned short int) 0;
    datum->hodiny =  (unsigned short int) 0;
    datum->mesic = (unsigned short int) 0;
    datum->minuty = (unsigned short int) 0;
    datum->rok = (unsigned short int) 0;
    datum->textova_reprezentace = (char*) calloc(DELKA_TEXTOVE_REPREZENTACE, sizeof(char));
    datum_na_string(datum);

    return datum;
}

void nastavit_datum_na_dnes(Datum* datum) {
    if (datum == NULL) {
        datum = datum_init();
    }

    time_t cas_t = time(NULL);
    struct tm cas = *localtime(&cas_t);
    datum->den = cas.tm_mday;
    datum->mesic = cas.tm_mon + 1;
    datum->rok = cas.tm_year + 1900;
    datum->hodiny = cas.tm_hour;
    datum->minuty = cas.tm_min;

    datum_na_string(datum);
}

bool porovnat_datum(Datum* datum1, Datum* datum2) {
    // Porovnání ROKU
    if (datum1->rok > datum2->rok) {
        return true;
    } else if (datum1->rok < datum2->rok) {
        return false;
    }

    // Porovnání MESICE
    if (datum1->mesic > datum2->mesic) {
        return true;
    } else if (datum1->mesic < datum2->mesic) {
        return false;
    }

    // Porovnání DNE
    if (datum1->den > datum2->den) {
        return true;
    } else if (datum1->den < datum2->den) {
        return false;
    }

    // Porovnání HODIN
    if (datum1->hodiny > datum2->hodiny) {
        return true;
    } else if (datum1->hodiny < datum2->hodiny) {
        return false;
    }

    // Porovnání ROKU
    if (datum1->minuty > datum2->minuty) {
        return true;
    } 

    return false;
}

void smazat_datum(Datum* datum) {
    free(datum->textova_reprezentace);
    free(datum);
}