#include "plik.h"
#include "errors.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int odczytaj_dane(FILE *plik, obraz *img)
{
    int i;

    return 1;
}

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
    int err;
    element * temp = (element * )malloc(sizeof(element));
    temp->next = NULL;
    temp->img = (obraz *)malloc(sizeof(obraz));
    temp->img->nazwa_pliku = (char *)malloc(sizeof(char) * strlen(nazwa_pliku));
    strcpy(temp->img->nazwa_pliku, nazwa_pliku);

    if((err = odczytaj_rodzaj_obrazka(plik, temp->img)) != FILE_READ_OK)
    {
        printf("Błąd odczytu z pliku\n");
        fclose(plik);
        free(nazwa_pliku);
        if(_DEBUG) printf("Błąd %d\n", err);
        return err;
    }
    if((err = odczytaj_wielkosc_obrazka(plik, temp->img)) != SIZE_OK)
    {
        printf("Błąd odczytu z pliku\n");
        fclose(plik);
        free(nazwa_pliku);
        if(_DEBUG) printf("Błąd %d\n", err);
        return err;
    }
    if((err = zarezerwuj_pamiec_dane(temp->img)) != MALLOC_OK)
    {
        printf("Błąd odczytu z pliku!\n");
        fclose(plik);
        free(nazwa_pliku);
        if(_DEBUG) printf("Błąd %d\n", err);
        return err;
    }
    /*if((plik = odczytaj_dane(plik, temp->img)) == NULL)
    {
        printf("Błąd odczytu z pliku!\n");
        if(_DEBUG) printf("Błąd %d\n", FILE_READ_ERR);
        return FILE_READ_ERR;
    }*/

    fclose(plik);
    free(nazwa_pliku);
}

int odczytaj_rodzaj_obrazka(FILE *plik, obraz *img)
{
    int err;
    if ((err = sprawdz_czy_komentarz(plik)) != COMMENT_OK)
    {
        if(_DEBUG) printf("Komentarz err: %d\n", err);
        return err;
    }
    char c;
    //odczytanie litery 'P'
    c = fgetc(plik);
    if (c != 'P')
    {
        printf("Błędny nagłówek pliku!\n");
        if (_DEBUG) printf("(1) Odczytano: %c, err: %d\n", c, ART_FIRST);
        return ART_FIRST;
    }
    if (_DEBUG) printf("(1) Odczytano: %c\n", c);
    //odczytanie rodzaju
    fscanf(plik, "%d", &img->rodzaj);
    if (img->rodzaj < 0 || img->rodzaj > 6)
    {
        printf("Błędny nagłówek pliku!\n");
        if (_DEBUG) printf("(2) Odczytano: %d, err: %d\n", img->rodzaj, ART_NUMBER);
        return ART_NUMBER;
    }
    if (_DEBUG) printf("(2) Odczytano: %d\n", img->rodzaj);

    while(fgetc(plik) != '\n') {} // konieczne, bo inaczej wywala śmieci
    return ART_OK;
}

int odczytaj_wielkosc_obrazka(FILE *plik, obraz *img)
{
    int err;
    if ((err = sprawdz_czy_komentarz(plik)) != COMMENT_OK)
    {
        if(_DEBUG) printf("Komentarz err: %d\n", err);
        return err;
    }
    fscanf(plik,"%d",&img->width);
    if(img->width <= 0)
    {
        printf("Błędny nagłówek pliku!\n");
        if (_DEBUG) printf("(3) Odczytano: %d, err: %d\n", img->width, SIZE_WIDTH);
        return SIZE_WIDTH;
    }
    if (_DEBUG) printf("(3) Odczytano: %d\n", img->width);
    fscanf(plik, "%d", &img->height);
    if(img->width <= 0)
    {
        printf("Błędny nagłówek pliku!\n");
        if (_DEBUG) printf("(4) Odczytano: %d, err: %d\n", img->height, SIZE_HEIGHT);
        return SIZE_HEIGHT;
    }
    if (_DEBUG) printf("(4) Odczytano: %d\n", img->height);
    while(fgetc(plik) != '\n') {}
    return SIZE_OK;
}

int sprawdz_czy_komentarz(FILE *plik)
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
        return COMMENT_OK;
    }
    else if (c == EOF)
    {
        if (_DEBUG) printf("EOF\n");
        return COMMENT_EOF;
    }
    else
    {
        printf("Błąd odczytu z pliku\n");
        return COMMENT_OTHER;
    }
}
