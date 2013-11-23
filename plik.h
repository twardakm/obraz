#ifndef PLIK_H
#define PLIK_H

#include "lista.h"
#include "obraz.h"
#include <stdio.h>

#define MAX_FILE_NAME 20

int odczytaj_plik(element *lista);
FILE * odczytaj_rodzaj_obrazka(FILE *plik, obraz *img);
FILE * odczytaj_wielkosc_obrazka(FILE *plik, obraz *img);
FILE * sprawdz_czy_komentarz(FILE *plik);

#endif // PLIK_H
