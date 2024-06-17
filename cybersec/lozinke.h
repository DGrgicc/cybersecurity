#ifndef _LOZINKE_H_
#define _LOZINKE_H_

void izbornik();

typedef enum { //3. 
	SIFRIRANJE_SUBSTITUCIJA,
	SIFRIRANJE_CEZAR,
	SIFRIRANJE_VIGENEREOVA
} metoda_sifriranja;

typedef struct {
	char* lozinka; //2. 
	metoda_sifriranja metoda;
} lozinka_t;

typedef struct {
	char* lozinka_dekript;
} Lozinka;

#define MAX_NAME_LENGTH 50
typedef struct {
	char* ime;
	int id;
	char* pass;
} Korisnik;

void sifriraj_lozinku(lozinka_t* lozinka,const int shift); //4. 
void generiraj_lozinke();

#endif