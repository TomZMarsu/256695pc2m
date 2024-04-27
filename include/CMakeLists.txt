set(skola_HEADER
   datum.h
   ptak.h
   pozorovani.h
   vypisovac.h
   nacitacdat.h
   stringutil.h
   ovladac_pozorovani.h
)

PREPEND(skola_HEADER)

set(skola_HEADER ${skola_HEADER}  PARENT_SCOPE)
