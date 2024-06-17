#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "napad.h"
#include "lozinke.h"
#define MAX_LOZINKI 3 //8
#define LOZINKA_DUZINA 8
static int broj_lozinki = 0; //5.
extern lozinka_t lozinke[3]; //7. 
extern Lozinka password[3];
#define ZBROJ(a, b) ((a) + (b))

void izbornik_napada() {
	printf("\n*Dobrodosli u simulaciju napada*\n"); //9.
	printf("	1. Brute Force Napad\n");
	printf("	2. Phishing\n");
}

void brute_force_napad(lozinka_t* lozinka) {
    int choice;

    printf("Izaberi lozinku koju zelis hakirati:\n");
    printf("1. Lozinka iz substitucija.txt\n");
    printf("2. Lozinka iz cezar.txt\n");
    printf("3. Lozinka iz vigenere.txt\n");

    while (1) {
        printf("Unesite izbor (1 -> 2 -> 3): ");
        if (scanf("%d", &choice) != 1) {
            printf("Pogresan unos! Unesite broj izmedu 1 i 3.\n");
            while (getchar() != '\n'); // Čišćenje buffer-a
            continue;
        }

        if (choice < 1 || choice > 3) {
            printf("Pogresan unos! Unesite broj izmedu 1 i 3.\n");
            continue;
        }
        break;
    }

    FILE* datoteka;
    const char* ime_datoteke;
    char kriptirana_lozinka[LOZINKA_DUZINA + 1];
    char* dekriptirana_lozinka;

    if (choice == 1) {
        ime_datoteke = "substitucija.txt";
        dekriptirana_lozinka = password[0].lozinka_dekript;
    }
    else if (choice == 2) {
        ime_datoteke = "cezar.txt";
        dekriptirana_lozinka = password[1].lozinka_dekript;
    }
    else if (choice == 3) {
        ime_datoteke = "vigenere.txt";
        dekriptirana_lozinka = password[2].lozinka_dekript;
    }
    else {
        printf("Neispravan izbor.\n");
        return;
    }

    datoteka = fopen(ime_datoteke, "r");
    if (!datoteka) {
        printf("Brute force napad nije uspio - datoteka %s nije pronadena.\n", ime_datoteke);
        free(dekriptirana_lozinka);
        return;
    }

    if (fgets(kriptirana_lozinka, sizeof(kriptirana_lozinka), datoteka) == NULL) {
        printf("Greska pri citanju datoteke.\n");
        fclose(datoteka);
        free(dekriptirana_lozinka);
        return;
    }
    fclose(datoteka);
    // Ukloni novi red na kraju lozinke ako postoji
    kriptirana_lozinka[strcspn(kriptirana_lozinka, "\n")] = 0;
    printf("\nKriptirana lozinka: %s\n", kriptirana_lozinka);
    if (dekriptirana_lozinka != NULL) {
    }
    else {
        printf("Lozinka nije inicijalizovana.\n");
        printf("Pokusajte pogoditi originalnu lozinku:\n");
    }
    int br_pokusaja = 0;
        while (1) {
            char pokusaj[LOZINKA_DUZINA + 1];
            printf("Unesite pokusaj: ");
            br_pokusaja++;
            scanf("%s", pokusaj);
            if (strcmp(pokusaj, dekriptirana_lozinka) == 0) {
                printf("Pogodili ste lozinku!\n");
                printf("Broj pokusaja: %d\n", br_pokusaja);
                break;
            }
            else {
                printf("Pogresna lozinka. Pokusajte ponovo.\n");
            }
        }
    }

void extractUsername(const char* email, char* username) {
    // Pronađi poziciju '@' u email adresi
    const char* atPosition = strchr(email, '@');
    if (atPosition != NULL) {
        // Kopiraj dio stringa prije '@' u 'username' buffer
        size_t length = atPosition - email;
        strncpy(username, email, length);
        username[length] = '\0'; // Dodaj null terminator na kraj
    }
    else {
        strcpy(username, email);
    }
}

int usporediLozinke(const char* unesenaLozinka, const char* pohranjenaLozinka) {
    // Inicijalizacija pokazivača za prolazak kroz lozinke
    const char* pUnesena = unesenaLozinka;
    const char* pPohranjena = pohranjenaLozinka;

    // Prolazak kroz obe lozinke
    while (*pUnesena != '\0' && *pPohranjena != '\0') {
        // Ako su karakteri u lozinkama slova, uspoređujemo ih
        if (isalpha(*pUnesena) && isalpha(*pPohranjena)) {
            if (tolower(*pUnesena) != tolower(*pPohranjena)) {
                return 0;  // Karakteri nisu jednaki
            }
            // Pomeramo pokazivače na sljedeće karaktere
            pUnesena++;
            pPohranjena++;
        }
        else {
            // Ako je jedan od karaktera broj ili razmak, preskačemo ga
            if (!isalpha(*pUnesena)) {
                pUnesena++;
            }
            if (!isalpha(*pPohranjena)) {
                pPohranjena++;
            }
        }
    }
}

void Phishing() {
    char email[100]; //13
    char lozinka[50];
    char imePsa[100];

    printf("Dobrodosli! Izgleda da imate sigurnosni problem sa vasim racunom.\n");
    printf("Molimo unesite svoju e-mail adresu da bismo potvrdili vas identitet: ");
    scanf("%99s", email);

    printf("Molimo unesite svoju lozinku za verifikaciju: ");
    scanf("%49s", lozinka);

    printf("SIGURNOSNO PITANJE: Koje je ime vaseg prvog ljubimca: ");
    scanf("%99s", imePsa);

    // Prikaz prikupljenih podataka (u stvarnom phishing napadu, ovi podaci bi bili zloupotrebljeni)
    printf("\nPrikupljeni podaci:\n");
    printf("E-mail: %s\n", email);
    printf("Lozinka: %s\n", lozinka);
    printf("Ime ljubimca: %s\n", imePsa);

    const char* sumnjiveKljučneRječi[] = {
        password[0].lozinka_dekript,
        password[1].lozinka_dekript,
        password[2].lozinka_dekript
    };

    const int brojKljučnihRječi = sizeof(sumnjiveKljučneRječi) / sizeof(sumnjiveKljučneRječi[0]);
    int sumnjiva = 0;


   
    for (int i = 0; i < brojKljučnihRječi; i++) {
        if (strstr(lozinka, sumnjiveKljučneRječi[i]) != NULL) {
            sumnjiva = 1;
            break;
        }
    }

   
    char email_skraceno[50];
    extractUsername(email, email_skraceno);
    for (int i = 0; i < brojKljučnihRječi; i++) {
        if (strstr(email_skraceno, sumnjiveKljučneRječi[i]) != NULL) {
            sumnjiva = 1;
            break;
        }
    }

  
    for (int i = 0; i < brojKljučnihRječi; i++) {
        if (strstr(imePsa, sumnjiveKljučneRječi[i]) != NULL) {
            sumnjiva = 1;
            break;
        }
    }
    if (sumnjiva) {
        printf("\n\n****Upravo ste hakirani! Haker je uspio doci do sve tri lozinke:****\n");
        for (int i = 0; i < MAX_LOZINKI; i++) {
            printf("Lozinka %d: %s\n", i + 1, password[i].lozinka_dekript);
        }
    }
    else {
        printf("\n\nHaker Vas nije uspio hakirati. Lozinke se nece prikazati...\n");       
    }

  
}


void simuliraj_napad() {
    int x = 1;
    int y = 2;
    int rez = ZBROJ(x, y); //8.
    lozinka_t lozinka[3];
	printf("\n\nPokrecem simulaciju napada...\n");
    int choice, br = 1;
	izbornik_napada();
    do {
        printf("\nUnesite svoj izbor: ");
        while (scanf("%d", &choice) != 1) {
            printf("Pogresan unos! Unesite broj izmedu 1 i 2:\nUnesite svoj izbor:");
            while (getchar() != '\n'); // Čišćenje buffer-a
        }

        if (choice < 1 || choice > rez) {
            printf("Pogresan unos! Unesite broj izmedu 1 i 2\n");
            continue;
        }
            if (choice == 1) {
                brute_force_napad(lozinka);
                br++;
            }               
            else if (choice == 2) {
                Phishing();
                br++;
                if (br == 3)
                    break;
            }       
            else {
                printf("Neispravan izbor! Molimo unesite broj izmedu 1 i 2.\n");
                continue;
            }
          
    } while (1);
	 

	printf("Simulacija napada zavrsena.\n");
}



