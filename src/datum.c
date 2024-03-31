#include "datum.h"

// String musí mít alespoň 18 znaků
void datum_na_string(Datum* datum) {
    sprintf(datum->textova_reprezentace, "%2u.%2u. %4u %2u:%2u", 
        datum->den,
        datum->mesic,
        datum->rok,
        datum->hodiny,
        datum->minuty
    );
}