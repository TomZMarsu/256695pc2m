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

void smazat_datum(Datum* datum) {
    free(datum->textova_reprezentace);
    free(datum);
}