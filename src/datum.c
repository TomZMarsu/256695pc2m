#include "datum.h"
#include <stdlib.h>

// String musí mít alespoň 18 znaků
char* datum_na_string(Datum* datum) {
    sprintf(datum->textova_reprezentace, "%02u.%02u. %04u %02u:%02u", 
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

void smazat_datum(Datum* datum) {
    free(datum->textova_reprezentace);
    free(datum);
}