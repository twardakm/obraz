#ifndef PLIK_H
#define PLIK_H

#include "lista.h"
#include "obraz.h"
#include <stdio.h>

#define MAX_FILE_NAME 20

int czy_zapisac();
int odczytaj_dane(FILE *plik, obraz *img);
int odczytaj_maksymalny_kolor(FILE *plik, obraz *img);
element *odczytaj_plik(element *lista);
int odczytaj_rodzaj_obrazka(FILE *plik, obraz *img);
int odczytaj_wielkosc_obrazka(FILE *plik, obraz *img);
int sprawdz_czy_komentarz(FILE *plik);
int wyswietl_pliki();
int zapisz_plik(obraz *img);

#endif // PLIK_H
