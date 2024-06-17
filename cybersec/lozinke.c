#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lozinke.h"

void izbornik() {
    printf("\n*Dobrodosli u simulaciju napada i obrane*\n"); //9.
    printf("1. Unesite tri zaporke\n");
    printf("2. Pokreni simulaciju napada\n");
    printf("3. Pokreni simulaciju obrane\n");
    printf("4. Pretrazivanje i sortiranje\n");
}

lozinka_t lozinke[3];
Lozinka password[3];
Korisnik korisnici[3];
void generiraj_lozinke() {
    FILE* f;  
    int br = 1;
    int shift = 0;
    f = fopen("lozinke.txt", "w");
    fclose(f);

    for (int i = 0; i < 3; i++) {        
        korisnici[i].ime = malloc(MAX_NAME_LENGTH * sizeof(char));
        if (korisnici[i].ime == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        printf("Unesite ime korisnika %d: ", i + 1);
        scanf("%49s", korisnici[i].ime);


        while (1) {
            printf("Unesite ID korisnika %d: ", i + 1);
            if (scanf("%d", &korisnici[i].id) != 1) {
                // Ako unos nije broj
                printf("Neispravan unos! Molimo unesite broj.\n");
                while (getchar() != '\n'); // Očisti unos
            }
            else if (korisnici[i].id%1==0 ) {
                break; // validan unos, izlazi iz petlje
            }
            else {
                printf("Neispravan izbor! Molimo unesite ponovo.\n");
            }
        }
        printf("\nUnesite %d. lozinku: ", i + 1);
        lozinke[i].lozinka = (char*)malloc(50 * sizeof(char));
        if (lozinke[i].lozinka == NULL) {
            printf("Ne mogu alocirati memoriju.\n");
            exit(1);
        }
        scanf("%49s", lozinke[i].lozinka);
        password[i].lozinka_dekript = (char*)malloc((strlen(lozinke[i].lozinka) + 1) * sizeof(char));
        if (password[i].lozinka_dekript == NULL) {
            printf("Ne mogu alocirati memoriju za lozinka_dekript.\n");
            exit(1);
        }
        strcpy(password[i].lozinka_dekript, lozinke[i].lozinka);
        korisnici[i].pass = lozinke[i].lozinka;
        printf("\nOdaberite metodu sifriranja za lozinku %d:\n", i + 1);
        printf("1. Substitucija\n");
        printf("2. Cezar\n");
        printf("3. Vigenereova sifra\n");
        while (1) {
            printf("IZBOR: ");
            if (scanf("%d", &lozinke[i].metoda) != 1) {
                // Ako unos nije broj
                printf("Neispravan unos! Molimo unesite broj.\n");
                while (getchar() != '\n'); // Očisti unos
            }
            else if (lozinke[i].metoda == br) {
                br++;
                break; // validan unos, izlazi iz petlje
            }
            else {
                printf("Neispravan izbor! Molim idete redom!\n");
            }
        }

        if (lozinke[i].metoda == 2) {
            printf("\nUnesite broj pomjeranja za sifriranje: ");
            while (scanf("%d", &shift) != 1) {
                // Ako unos nije broj
                printf("Neispravan unos! Molimo unesite broj.\nBroj pomjeranja: ");
                while (getchar() != '\n'); // Očisti unos
            }
        }

        f = fopen("lozinke.txt", "a");
        if (f == NULL) {
            printf("Greska pri otvaranju datoteke!\n");
            exit(1);
        }

        fprintf(f, "%s\n", lozinke[i].lozinka);
        fclose(f);

        sifriraj_lozinku(&lozinke[i], shift);
    }


    printf("\nLozinke su uspjesno zapisane u datoteku.\n");
}

static int shift2 = 25;
void sifriraj_lozinku(lozinka_t* lozinka, const int shift) {
    char kljuc[50];
    switch (lozinka->metoda) {
    case 1:
        for (int j = 0; j < strlen(lozinka->lozinka); j++) {
            if (lozinka->lozinka[j] >= '0' && lozinka->lozinka[j] <= '9') {
                lozinka->lozinka[j] = '0' + (lozinka->lozinka[j] - '0' + shift2) % 10;
            }
            else if (lozinka->lozinka[j] >= 'a' && lozinka->lozinka[j] <= 'z') {
                lozinka->lozinka[j] = ('a' + (lozinka->lozinka[j] - 'a' + shift2) % 26);
            }
            else if (lozinka->lozinka[j] >= 'A' && lozinka->lozinka[j] <= 'Z') {
                lozinka->lozinka[j] = ('A' + (lozinka->lozinka[j] - 'A' + shift2) % 26);
            }
        }
        FILE* novi_file2 = fopen("substitucija.txt", "w");
        if (novi_file2 == NULL) {
            printf("Greska pri otvaranju datoteke!\n");
            exit(1);
        }
        fprintf(novi_file2, "%s\n", lozinka->lozinka);
        fclose(novi_file2);
        break;
    case 2:
        for (int j = 0; j < strlen(lozinka->lozinka); j++) {
            if (lozinka->lozinka[j] >= '0' && lozinka->lozinka[j] <= '9') {
                lozinka->lozinka[j] = '0' + (lozinka->lozinka[j] - '0' + shift) % 10;
            }
            else if (lozinka->lozinka[j] >= 'a' && lozinka->lozinka[j] <= 'z') {
                lozinka->lozinka[j] = ('a' + (lozinka->lozinka[j] - 'a' + shift) % 26);
            }
            else if (lozinka->lozinka[j] >= 'A' && lozinka->lozinka[j] <= 'Z') {
                lozinka->lozinka[j] = ('A' + (lozinka->lozinka[j] - 'A' + shift) % 26);
            }
        }
        FILE* novi_file = fopen("cezar.txt", "w");
        if (novi_file == NULL) {
            printf("Greska pri otvaranju datoteke!\n");
            exit(1);
        }
        fprintf(novi_file, "%s\n", lozinka->lozinka);
        fclose(novi_file);
        break;
    case 3:
        while (1) {
            printf("Unesite kljuc za Vigenereovu sifru: ");
            scanf("%s", kljuc);

            int validan_kljuc = 1; // pretpostavimo da je ključ validan
            for (int j = 0; j < strlen(kljuc); j++) {
                if (!((kljuc[j] >= 'a' && kljuc[j] <= 'z') || (kljuc[j] >= 'A' && kljuc[j] <= 'Z'))) {
                    validan_kljuc = 0; // ključ sadrži nevalidan karakter
                    break;
                }
            }

            if (validan_kljuc) {
                break; // ključ je validan, izlazimo iz petlje
            }
            else {
                printf("Kljuc moze sadrzavati samo slova! Molimo unesite ponovo.\n");
            }
        }

        int kljuc_duljina = strlen(kljuc);
        int lozinka_duljina = strlen(lozinka->lozinka);

        for (int j = 0; j < lozinka_duljina; j++) {
            if (lozinka->lozinka[j] >= 'a' && lozinka->lozinka[j] <= 'z') {
                lozinka->lozinka[j] = 'a' + (lozinka->lozinka[j] - 'a' + kljuc[j % kljuc_duljina] - 'a') % 26;
            }
            else if (lozinka->lozinka[j] >= 'A' && lozinka->lozinka[j] <= 'Z') {
                lozinka->lozinka[j] = 'A' + (lozinka->lozinka[j] - 'A' + kljuc[j % kljuc_duljina] - 'A') % 26;
            }
        }
        FILE* novi_file3 = fopen("vigenere.txt", "w");
        if (novi_file3 == NULL) {
            printf("Greska pri otvaranju datoteke!\n");
            exit(1);
        }
        fprintf(novi_file3, "%s\n", lozinka->lozinka);
        fclose(novi_file3);
        break;
    default:
        printf("Neispravan izbor!\n");
    }
}
