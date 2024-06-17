#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "napad.h"
#include "obrana.h"
#include "lozinke.h"
#include "datoteke.h"

void remove_file(const char* filename) {
    if (remove(filename) != 0) {
        printf("Greska prilikom brisanja datoteke %s\n", filename);
        perror("remove");
    }
    else {
        printf("Datoteka %s uspjesno izbrisana\n", filename);
    }
}

void rename_file(const char* old_filename, const char* new_filename) {
    if (rename(old_filename, new_filename) != 0) {
        printf("Greska prilikom preimenovanja datoteke iz %s u %s\n", old_filename, new_filename);
        perror("remove");
    }
    else {
        printf("Datoteka uspjesno preimenovana iz %s u %s\n", old_filename, new_filename);
    }
}

void copy_file(const char* source_filename, const char* destination_filename) {
    FILE* source_file = fopen(source_filename, "rb");
    FILE* destination_file = fopen(destination_filename, "wb");
    if (source_file == NULL || destination_file == NULL) {
        printf("Greska prilikom otvaranja datoteke\n");
        perror("remove");
        return;
    }

    rewind(source_file); 

    char buffer[1024];
    int c;
    while ((c = fgetc(source_file)) != EOF) {
        fputc(c, destination_file);
    }

    fclose(source_file);
    fclose(destination_file);
    printf("Datoteka uspjesno kopirana iz %s u %s\n", source_filename, destination_filename);
}

void kopiraj_datoteke() {
    for (int i = 0; i < 3; i++) {
        if (i == 0) {
            char* ime_datoteke = "substitucija.txt";
            char* jaka_datoteke = "jaka_substitucija.txt";
            copy_file(ime_datoteke, jaka_datoteke);
            if (rename(ime_datoteke, "stara_substitucija.txt") == 0) {
                printf("Datoteka preimenovana uspješno!\n");
            }
            else {
            }
        }
        else if (i == 1) {
            char* ime_datoteke = "cezar.txt";
            char* jaka_datoteke = "jaka_cezar.txt";
            copy_file(ime_datoteke, jaka_datoteke);
            if (rename(ime_datoteke, "stara_cezar.txt") == 0) {
                printf("Datoteka preimenovana uspješno!\n");
            }
            else {
            }
        }
        else if (i == 2) {
            char* ime_datoteke = "vigenere.txt";
            char* jaka_datoteke = "jaka_vigenere.txt";
            copy_file(ime_datoteke, jaka_datoteke);
            if (rename(ime_datoteke, "stara_vigenere.txt") == 0) {
                printf("Datoteka preimenovana uspješno!\n");
            }
            else {
            }
        }
    }
}
void obrisi_stare_datoteke() {
    const char* stare_datoteke[] = { "stara_substitucija.txt", "stara_cezar.txt", "stara_vigenere.txt" };
    for (int i = 0; i < 3; i++) {
        if (remove(stare_datoteke[i]) == 0) {
            printf("Datoteka %s obrisana uspješno!\n", stare_datoteke[i]);
        }
        else {
        }
    }
}
Korisnik korisnici[3];
#define NUM_KORISNICI 3


int compare_korisnici(const void* a, const void* b) {
    Korisnik* korisnik1 = (Korisnik*)a;
    Korisnik* korisnik2 = (Korisnik*)b;
    return korisnik1->id - korisnik2->id;
}

void spoji_datoteke(const char* izlazna_datoteka) {
    const char* datoteke_za_citanje[] = { "jaka_cezar.txt", "jaka_vigenere.txt", "jaka_substitucija.txt" };
    FILE* izlaz = fopen(izlazna_datoteka, "w");
    if (izlaz == NULL) {
        printf("Ne mogu otvoriti izlaznu datoteku!\n");
        exit(1);
    }

    for (int i = 0; i < 3; i++) {
        FILE* ulaz = fopen(datoteke_za_citanje[i], "r");
        if (ulaz == NULL) {
            printf("Ne mogu otvoriti ulaznu datoteku %s!\n", datoteke_za_citanje[i]);
            exit(1);
        }

        char buffer[1024];
        while (fgets(buffer, 1024, ulaz) != NULL) {
            fputs(buffer, izlaz);
        }

        fclose(ulaz);
        qsort(korisnici, 3, sizeof(Korisnik), compare_korisnici);
    }
    printf("\n\nSortirani korisnici:\n");
    for (int i = 0; i < NUM_KORISNICI; i++) {
        printf("Ime: %s, ID: %d, Lozinka: %s\n", korisnici[i].ime, korisnici[i].id,korisnici[i].pass);
    }
    fclose(izlaz);
    
}
extern Lozinka password[3];
int compare_korisnici2(const void* a, const void* b) {
    Korisnik* ka = (Korisnik*)a;
    Korisnik* kb = (Korisnik*)b;
    return strcmp(ka->ime, kb->ime);
}
void pretrazi_korisnike(const char* izlazna_datoteka) {
    Korisnik korisnik_za_pretragu;
    printf("Unesite ime korisnika za pretragu: ");
    korisnik_za_pretragu.ime = malloc(50 * sizeof(char));
    scanf("%49s", korisnik_za_pretragu.ime);

    Korisnik* pronadjen_korisnik = bsearch(&korisnik_za_pretragu, korisnici, 3, sizeof(Korisnik), compare_korisnici2);
    if (pronadjen_korisnik != NULL) {
        printf("\nKorisnik pronadjen: Ime: %s, ID: %d, lozinka: %s\n", pronadjen_korisnik->ime, pronadjen_korisnik->id, pronadjen_korisnik->pass);
    }
    else {
        printf("Korisnik nije pronadjen\n");
    }
}