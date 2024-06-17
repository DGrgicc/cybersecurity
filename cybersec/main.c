#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "napad.h"
#include "obrana.h"
#include "lozinke.h"
#include "datoteke.h"
int main() {
    int br = 1; //1. 
    int choice;
    izbornik();
    
    do {      
        printf("\nUnesite svoj izbor: ");
        while (scanf("%d", &choice) != 1) {
            printf("Pogresan unos! Unesite broj izmedu 1 i 4:\nUnesite svoj izbor:");
            while (getchar() != '\n'); // Čišćenje buffer-a
        }

        if (choice < 1 || choice > 4) {
            printf("Pogresan unos! Unesite broj izmedu 1 i 4\n");
            continue;
        }

        if (br == 1) {
            if (choice == 1) {
                generiraj_lozinke();
                br++;
            }
            else {
                printf("Neispravan izbor! Molimo unesite broj 1.\n");
                continue;
            }
        }
        else if (br == 2) {
            if (choice == 2) {
                simuliraj_napad();
                br++;
            }
            else {
                printf("Neispravan izbor! Molimo unesite broj 2.\n");
                continue;
            }
        }
        else if (br == 3) {
            if (choice == 3) {
                simuliraj_obranu();
                br++;
            }
            else {
                printf("Neispravan izbor! Molimo unesite broj 3.\n");
                continue;
            }
        }
        else if (br == 4) {
            if (choice == 4) {
                kopiraj_datoteke();
                spoji_datoteke("zajedno.txt");
                pretrazi_korisnike("zajedno.txt");
                break; // Izlaz iz petlje
            }
            else {
                printf("Neispravan izbor! Molimo unesite broj 4.\n");
                continue;
            }
        }
    } while (1);
    
    return 0;
}