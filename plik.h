#ifndef PLIK_H
#define PLIK_H

#include "lista.h"
#include "obraz.h"
#include <stdio.h>

#define MAX_FILE_NAME 30

int czy_zapisac();
int odczytaj_dane(FILE *plik, obraz *img);
int odczytaj_maksymalny_kolor(FILE *plik, obraz *img);
element * odczytaj_plik(element *lista);
int odczytaj_rodzaj_obrazka(FILE *plik, obraz *img);
int odczytaj_wielkosc_obrazka(FILE *plik, obraz *img);
element * odczytaj_wszystkie_pliki(element *lista);
int sprawdz_czy_komentarz(FILE *plik);
int wyswietl_pliki();
int zapisz_plik(obraz *img);
int zapisz_wszystkie_pliki(element *lista);

#endif // PLIK_H
