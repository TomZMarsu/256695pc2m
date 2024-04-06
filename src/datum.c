#include "datum.h"

// String musí mít alespoň 18 znaků
void datum_na_string(Datum* datum) {
    sprintf(datum->textova_reprezentace, "%02u.%02u. %04u %02u:%02u", 
        datum->den,
        datum->mesic,
        datum->rok,
        datum->hodiny,
        datum->minuty
    );
}

Datum* datum_init() {
    Datum* datum = (Datum*) malloc(sizeof(datum));
    datum->den = 0;
    datum->hodiny = 0;
    datum->mesic = 0;
    datum->minuty = 0;
    datum->rok = 0;
    datum->textova_reprezentace = (char*) calloc(DELKA_TEXTOVE_REPREZENTACE, sizeof(char));
    datum_na_string(datum);

    return datum;
}