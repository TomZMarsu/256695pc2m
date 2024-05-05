#ifndef SPRAVCE_TERMINALU_H
#define SPRAVCE_TERMINALU_H

#include <stdio.h>

// Zdroj: https://stackoverflow.com/questions/46864932/how-to-clear-screen-in-both-windows-and-linux-in-c
#define VYCISTI_OBRAZOVKU() system("clear || cls")

// ZISKANI ROZMERU TERMINALU
// Zdroj: https://stackoverflow.com/questions/23369503/get-size-of-terminal-window-rows-columns
#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>
#elif defined(__linux__)
#include <sys/ioctl.h>
#endif // Windows/Linux

void ziskej_velikost_terminalu(int* height);
// ZISKANI ROZMERU TERMINALU ^^^^^

void vymazat_radek(int pocet_radku);

#endif //SPRAVCE_TERMINALU_H