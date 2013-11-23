#include "plik.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int odczytaj_plik(element *lista)
{
    char *nazwa_pliku = (char *)malloc(sizeof(char) * MAX_FILE_NAME);
    FILE *plik;
    printf("Podaj nazwę pliku (maksymalnie %d znaków:)\n", MAX_FILE_NAME);
    scanf("%s", nazwa_pliku);
    if (_DEBUG) printf ("Nazwa pliku: %s\n", nazwa_pliku);

    printf("Otwieranie pliku... %s ", nazwa_pliku);
    //otwarcie podanego pliku w trybie do odczytu
    if((plik = fopen(nazwa_pliku, "r")) == NULL)
    {
        perror("Nie udało się otworzyć podanego pliku\n");
        return FILE_OPEN_ERR;
    }
    else
        printf("OK\n");

    //zapisywanie elemntu do listy
    element * temp = (element * )malloc(sizeof(element));
    temp->next = NULL;
    temp->img = (obraz *)malloc(sizeof(obraz));
    temp->img->nazwa_pliku = (char *)malloc(sizeof(char) * strlen(nazwa_pliku));
    strcpy(temp->img->nazwa_pliku, nazwa_pliku);

    if((plik = odczytaj_rodzaj_obrazka(plik, temp->img)) == NULL)
    {
        printf("Błąd odczytu z pliku\n");
        fclose(plik);
        free(nazwa_pliku);
        return FILE_READ_ERR;
    }
    if((plik = odczytaj_wielkosc_obrazka(plik, temp->img)) == NULL)
    {
        printf("Błąd odczytu z pliku\n");
        fclose(plik);
        free(nazwa_pliku);
        return FILE_READ_ERR;
    }

    fclose(plik);
    free(nazwa_pliku);
}

FILE * odczytaj_rodzaj_obrazka(FILE *plik, obraz *img)
{
    if ((plik = sprawdz_czy_komentarz(plik)) == NULL)
    {
        if(_DEBUG) printf("Nie udało się sprawdzanie komentarza\n");
        return NULL;
    }
    char c;
    //odczytanie litery 'P'
    c = fgetc(plik);
    if (c != 'P')
    {
        printf("Błędny nagłówek pliku!\n");
        if (_DEBUG) printf("(1) Odczytano: %c\n", c);
        return NULL;
    }
    if (_DEBUG) printf("(1) Odczytano: %c\n", c);
    //odczytanie rodzaju
    fscanf(plik, "%d", &img->rodzaj);
    if (img->rodzaj < 0 || img->rodzaj > 6)
    {
        printf("Błędny nagłówek pliku!\n");
        if (_DEBUG) printf("(2) Odczytano: %d\n", img->rodzaj);
        return NULL;
    }
    if (_DEBUG) printf("(2) Odczytano: %d\n", img->rodzaj);

    while(fgetc(plik) != '\n') {} // konieczne, bo inaczej wywala śmieci
    return plik;
}

FILE * odczytaj_wielkosc_obrazka(FILE *plik, obraz *img)
{
    if ((plik = sprawdz_czy_komentarz(plik)) == NULL)
    {
        if(_DEBUG) printf("Nie udało się sprawdzanie komentarza\n");
        return NULL;
    }
    fscanf(plik,"%d",&img->width);
    if(img->width <= 0)
    {
        printf("Błędny nagłówek pliku!\n");
        if (_DEBUG) printf("(3) Odczytano: %d\n", img->width);
        return NULL;
    }
    if (_DEBUG) printf("(3) Odczytano: %d\n", img->width);
    fscanf(plik, "%d", &img->height);
    if(img->width <= 0)
    {
        printf("Błędny nagłówek pliku!\n");
        if (_DEBUG) printf("(4) Odczytano: %d\n", img->height);
        return NULL;
    }
    if (_DEBUG) printf("(4) Odczytano: %d\n", img->height);
    while(fgetc(plik) != '\n') {}
    return plik;
}

FILE * sprawdz_czy_komentarz(FILE *plik)
{
    char c = fgetc(plik);
    while (c == '#')
    {
        if (_DEBUG) printf("Znaleziono komentarz\n");
        while(fgetc(plik) != '\n') {} // żeby przeszkoczyć całą linię
        c = fgetc(plik);
    }
    if (!fseek(plik, ftell(plik) - 1, SEEK_SET) && c != EOF)
    {
        if (_DEBUG) printf("Nie znaleziono komentarza\n");
        return plik;
    }
    else if (c == EOF)
    {
        if (_DEBUG) printf("EOF\n");
        return NULL;
    }
    else
    {
        printf("Błąd odczytu z pliku\n");
        return NULL;
    }
}
