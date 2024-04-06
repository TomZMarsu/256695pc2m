cmake_minimum_required(VERSION 3.5)

add_executable(test_vypis_tabulky test_vypis_tabulky.c ../vypisovac.c ../datum.c)
target_include_directories(test_vypis_tabulky PUBLIC ../../include/)
add_test(NAME test_vypis_tabulky  COMMAND test_vypis_tabulky)

add_executable(test_vypis_ptaka test_vypis_ptaka.c ../vypisovac.c ../datum.c)
target_include_directories(test_vypis_ptaka PUBLIC ../../include/)
add_test(NAME test_vypis_ptaka  COMMAND test_vypis_ptaka)

add_executable(test_datum_textova_reprezentace test_datum_textova_reprezentace.c ../datum.c)
target_include_directories(test_datum_textova_reprezentace PUBLIC ../../include/)
add_test(NAME test_datum_textova_reprezentace  COMMAND test_datum_textova_reprezentace)

set(test_nacteni_pozorovani_hlavicka_SRC
    test_nacteni_pozorovani_hlavicka.c
    ../nacitacdat.c
    ../datum.c
    ../stringutil.c
    ../ptak.c
    ../pozorovani.c
)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test_nacteni_pozorovani/pozorovani1.dat
     DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests/test_nacteni_pozorovani)
add_executable(test_nacteni_pozorovani_hlavicka ${test_nacteni_pozorovani_hlavicka_SRC})
target_include_directories(test_nacteni_pozorovani_hlavicka PUBLIC ../../include/)
add_test(NAME test_nacteni_pozorovani_hlavicka  COMMAND test_nacteni_pozorovani_hlavicka WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

set(test_nacteni_pozorovani_hlavicka_prazdne_SRC
    test_nacteni_pozorovani_hlavicka_prazdne.c
    ../nacitacdat.c
    ../datum.c
    ../stringutil.c
    ../ptak.c
    ../pozorovani.c
)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test_nacteni_pozorovani/pozorovani2.dat
     DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests/test_nacteni_pozorovani)
add_executable(test_nacteni_pozorovani_hlavicka_prazdne ${test_nacteni_pozorovani_hlavicka_prazdne_SRC})
target_include_directories(test_nacteni_pozorovani_hlavicka_prazdne PUBLIC ../../include/)
add_test(NAME test_nacteni_pozorovani_hlavicka_prazdne  COMMAND test_nacteni_pozorovani_hlavicka_prazdne WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

set(test_nacteni_pozorovani_cele_SRC
    test_nacteni_pozorovani_cele.c
    ../nacitacdat.c
    ../datum.c
    ../stringutil.c
    ../ptak.c
    ../pozorovani.c
)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test_nacteni_pozorovani/pozorovani_cele1.dat
     DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests/test_nacteni_pozorovani)
add_executable(test_nacteni_pozorovani_cele ${test_nacteni_pozorovani_cele_SRC})
target_include_directories(test_nacteni_pozorovani_cele PUBLIC ../../include/)
add_test(NAME test_nacteni_pozorovani_cele  COMMAND test_nacteni_pozorovani_cele WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})