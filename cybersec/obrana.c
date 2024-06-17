#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "napad.h"
#include "obrana.h"
#include "lozinke.h"

#define MIN_DUZINA 8


// Provjera sadrži li lozinka mala slova
int ima_mala_slova(const char* lozinka) {
    while (*lozinka) {
        if (islower(*lozinka)) return 1;
        lozinka++;
    }
    return 0;
}

// Provjera sadrži li lozinka velika slova
int ima_velika_slova(const char* lozinka) {
    while (*lozinka) {
        if (isupper(*lozinka)) return 1;
        lozinka++;
    }
    return 0;
}

// Provjera sadrži li lozinka brojeve
int ima_brojeve(const char* lozinka) {
    while (*lozinka) {
        if (isdigit(*lozinka)) return 1;
        lozinka++;
    }
    return 0;
}

// Provjera sadrži li lozinka posebne znakove
int ima_posebne_znakove(const char* lozinka) {
    while (*lozinka) {
        if (ispunct(*lozinka)) return 1;
        lozinka++;
    }
    return 0;
}

// Provjera je li lozinka dovoljno jaka
int je_jaka_lozinka(const char* lozinka) {
    return strlen(lozinka) >= MIN_DUZINA &&
        ima_mala_slova(lozinka) &&
        ima_velika_slova(lozinka) &&
        ima_brojeve(lozinka) &&
        ima_posebne_znakove(lozinka);
}

// Procjena lozinke i ispis rezultata
void procijeni_lozinku(const char* lozinka) {
    printf("--Procjena lozinke--\n");
    printf("Duzina: %s\n", strlen(lozinka) >= MIN_DUZINA ? "U redu" : "Prekratka");
    printf("Mala slova: %s\n", ima_mala_slova(lozinka) ? "Da" : "Ne");
    printf("Velika slova: %s\n", ima_velika_slova(lozinka) ? "Da" : "Ne");
    printf("Brojevi: %s\n", ima_brojeve(lozinka) ? "Da" : "Ne");
    printf("Posebni znakovi: %s\n", ima_posebne_znakove(lozinka) ? "Da" : "Ne");
}


void sifriraj_lozinku_substitucija(char* password) {
    int shift2 = 25;
    for (int j = 0; j < strlen(password); j++) {
        if (password[j] >= '0' && password[j] <= '9') {
            password[j] = '0' + (password[j] - '0' + shift2) % 10;
        }
        else if (password[j] >= 'a' && password[j] <= 'z') {
            password[j] = ('a' + (password[j] - 'a' + shift2) % 26);
        }
        else if (password[j] >= 'A' && password[j] <= 'Z') {
            password[j] = ('A' + (password[j] - 'A' + shift2) % 26);
        }
    }
    FILE* novi_file2 = fopen("substitucija.txt", "w");
    if (novi_file2 == NULL) {
        printf("Greska pri otvaranju datoteke!\n");
        exit(1);
    }
    fprintf(novi_file2, "%s\n", password);
    fclose(novi_file2);
}

void sifriraj_lozinku_cezar(char* password) {
    int shift;
    printf("\nUnesite broj pomjeranja za sifriranje: ");
    while (scanf("%d", &shift) != 1) {
        // Ako unos nije broj
        printf("Neispravan unos! Molimo unesite broj.\nBroj pomjeranja: ");
        while (getchar() != '\n'); // Očisti unos
    }
    for (int j = 0; j < strlen(password); j++) {
        if (password[j] >= '0' && password[j] <= '9') {
            password[j] = '0' + (password[j] - '0' + shift) % 10;
        }
        else if (password[j] >= 'a' && password[j] <= 'z') {
            password[j] = ('a' + (password[j] - 'a' + shift) % 26);
        }
        else if (password[j] >= 'A' && password[j] <= 'Z') {
            password[j] = ('A' + (password[j] - 'A' + shift) % 26);
        }
    }
    FILE* novi_file = fopen("cezar.txt", "w");
    if (novi_file == NULL) {
        printf("Greska pri otvaranju datoteke!\n");
        exit(1);
    }
    fprintf(novi_file, "%s\n", password);
    fclose(novi_file);

}


void sifriraj_lozinku_vigener(char* password) {
    char kljuc[50];
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
    int lozinka_duljina = strlen(password);

    for (int j = 0; j < lozinka_duljina; j++) {
        if (password[j] >= 'a' && password[j] <= 'z') {
            password[j] = 'a' + (password[j] - 'a' + kljuc[j % kljuc_duljina] - 'a') % 26;
        }
        else if (password[j] >= 'A' && password[j] <= 'Z') {
            password[j] = 'A' + (password[j] - 'A' + kljuc[j % kljuc_duljina] - 'A') % 26;
        }
    }
    FILE* novi_file3 = fopen("vigenere.txt", "w");
    if (novi_file3 == NULL) {
        printf("Greska pri otvaranju datoteke!\n");
        exit(1);
    }
    fprintf(novi_file3, "%s\n", password);
    fclose(novi_file3);

}

extern Lozinka password[3]; 
lozinka_t lozinke[3];
void simuliraj_obranu() {
    printf("Pokrecem simulaciju obrane...\n");
    FILE* datoteka;
    int shift2=25;
    int shift;
    const char* ime_datoteke;
    for (int i = 0; i < 3; i++) {

        printf("\n\n********************* %d. LOZINKA JE: %s *********************\n",i+1, password[i].lozinka_dekript);
        procijeni_lozinku(password[i].lozinka_dekript);
        if (je_jaka_lozinka(password[i].lozinka_dekript)) {
            printf("----Vasa lozinka je jaka.----\n\n");
            if (i == 0) {
                ime_datoteke = "substitucija.txt";
                strcpy(lozinke[0].lozinka, password[0].lozinka_dekript);
                while (1) {
                    printf("IZBOR: ");
                    if (scanf("%d", &lozinke[i].metoda) != 1) {
                        // Ako unos nije broj
                        printf("Neispravan unos! Molimo unesite broj.\n");
                        while (getchar() != '\n'); // Očisti unos
                    }
                    else if (lozinke[i].metoda == 1 || lozinke[i].metoda == 2 || lozinke[i].metoda == 3) {
                        break; // validan unos, izlazi iz petlje
                    }
                    else {
                        printf("Neispravan izbor! Molimo unesite ponovo.\n");
                    }
                }
                sifriraj_lozinku(&lozinke[i], shift);
                
            }
            else if (i == 1) {
                ime_datoteke = "cezar.txt";
                strcpy(lozinke[i].lozinka, password[i].lozinka_dekript);
                lozinke[i].metoda = 2;
                printf("\nUnesite broj pomjeranja za sifriranje: ");
                while (scanf("%d", &shift) != 1) {
                    // Ako unos nije broj
                    printf("Neispravan unos! Molimo unesite broj.\nBroj pomjeranja: ");
                    while (getchar() != '\n'); // Očisti unos
                }
                sifriraj_lozinku(&password[1], shift);
                
            }
            else if (i == 2) {
                ime_datoteke = "vigenere.txt";
                strcpy(lozinke[i].lozinka, password[i].lozinka_dekript);
                lozinke[i].metoda = 1;
                sifriraj_lozinku(&password[2], shift);
               
            }
        }
        else {
            printf("\n--Vasa lozinka nije dovoljno jaka. Molimo pokusajte ponovo.--\n");
            while (1) {
                printf("\nUnesite novu lozinku: ");
                scanf("%s", password[i].lozinka_dekript);
                procijeni_lozinku(password[i].lozinka_dekript);
                if (je_jaka_lozinka(password[i].lozinka_dekript)) {
                    printf("----Vasa lozinka je jaka.----\n");
                    if (i == 0) {                        
                        sifriraj_lozinku_substitucija(password[i].lozinka_dekript);
                    }
                    else if (i == 1) {
                        sifriraj_lozinku_cezar(password[i].lozinka_dekript);

                    }
                    else if (i == 2) {
                        sifriraj_lozinku_vigener(password[i].lozinka_dekript);
                    }
                    break;
                }
                else {
                    printf("\n--Vasa lozinka nije dovoljno jaka. Molimo pokusajte ponovo.--\n");
                }
            }
        }
    }

    
    printf("\n\n**********Simulacija obrane zavrsena.**********\n\n");
}
