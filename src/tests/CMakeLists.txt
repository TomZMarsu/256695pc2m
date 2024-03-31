cmake_minimum_required(VERSION 3.5)

add_executable(test_vypis_tabulky test_vypis_tabulky.c ../vypisovac.c ../datum.c)
target_include_directories(test_vypis_tabulky PUBLIC ../../include/)
add_test(NAME test_vypis_tabulky  COMMAND test_vypis_tabulky)

add_executable(test_vypis_ptaka test_vypis_ptaka.c ../vypisovac.c ../datum.c)
target_include_directories(test_vypis_ptaka PUBLIC ../../include/)
add_test(NAME test_vypis_ptaka  COMMAND test_vypis_ptaka)