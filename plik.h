#ifndef PLIK_H
#define PLIK_H

#include "lista.h"
#include "obraz.h"
#include <stdio.h>

#define MAX_FILE_NAME 20

int odczytaj_plik(element *lista);
int odczytaj_rodzaj_obrazka(FILE *plik, obraz *img);
int sprawdz_czy_komentarz(FILE *plik);

#endif // PLIK_H
